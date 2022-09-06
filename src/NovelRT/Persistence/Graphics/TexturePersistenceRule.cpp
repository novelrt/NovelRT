// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Persistence/Persistence.h>

namespace NovelRT::Persistence::Graphics
{
    TexturePersistenceRule::TexturePersistenceRule(
        std::shared_ptr<Ecs::Graphics::DefaultRenderingSystem> renderingSystem) noexcept
        : _renderingSystem(std::move(renderingSystem))
    {
    }

    std::vector<uint8_t> TexturePersistenceRule::ExecuteSerialiseModification(
        gsl::span<const uint8_t> component) const noexcept
    {
        const Ecs::Graphics::RenderComponent* ptr =
            reinterpret_cast<const Ecs::Graphics::RenderComponent*>(component.data());

        uuids::uuid vertexShaderId = _renderingSystem->GetVertexShaderGuidForPrimitiveInfo(ptr->primitiveInfoId);
        uuids::uuid pixelShaderId = _renderingSystem->GetPixelShaderGuidForPrimitiveInfo(ptr->primitiveInfoId);

        std::vector<uint8_t> packedData(GetSerialisedSize());

        uuids::uuid* uuidPtr = reinterpret_cast<const uuids::uuid*>(packedData.data());

       uuidPtr[0] = _renderingSystem->GetGuidForTexture(ptr->textureId);
       uuidPtr[1] = vertexShaderId;
       uuidPtr[2] = pixelShaderId;

        return packedData;
    }

    std::vector<uint8_t> TexturePersistenceRule::ExecuteDeserialiseModification(
        gsl::span<const uint8_t> component) const noexcept
    {
        const uuids::uuid* guids = reinterpret_cast<const uuids::uuid*>(component.data());

        std::vector<uint8_t> unpackedData(sizeof(Ecs::Graphics::RenderComponent));
        Ecs::Graphics::RenderComponent* ptr = reinterpret_cast<Ecs::Graphics::RenderComponent*>(unpackedData.data());
        ptr->vertexDataId = _renderingSystem->GetDefaultVertexDataId();
        ptr->textureId = _renderingSystem->GetTextureIdFromGuid(guids[0]);
        ptr->primitiveInfoId = _renderingSystem->GetPrimitiveInfoFromAssetGuids(guids[0], guids[1], guids[2]);
        ptr->pipelineId = _renderingSystem->GetPipelineFromAssetGuids(guids[0], guids[1], guids[2]);

        return unpackedData;
    }
}