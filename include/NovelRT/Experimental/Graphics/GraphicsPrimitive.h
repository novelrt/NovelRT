// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_GRAPHICSPRIMITIVE_H
#define NOVELRT_EXPERIMENTAL_GRAPHICS_GRAPHICSPRIMITIVE_H

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.h instead for the Graphics namespace subset.
#endif

namespace NovelRT::Experimental::Graphics
{
    class GraphicsPrimitive : public GraphicsDeviceObject
    {
    private:
        std::shared_ptr<GraphicsPipeline> _pipeline;
        GraphicsMemoryRegion<GraphicsResource> _vertexBufferRegion;
        GraphicsMemoryRegion<GraphicsResource> _indexBufferRegion;
        std::vector<GraphicsMemoryRegion<GraphicsResource>> _inputResourceRegions;
        uint32_t _vertexBufferStride;
        uint32_t _indexBufferStride;

    public:
        GraphicsPrimitive(const std::shared_ptr<GraphicsDevice>& device,
                          std::shared_ptr<GraphicsPipeline> pipeline,
                          GraphicsMemoryRegion<GraphicsResource> vertexBufferRegion,
                          uint32_t vertexBufferStride,
                          GraphicsMemoryRegion<GraphicsResource> indexBufferRegion,
                          uint32_t indexBufferStride,
                          gsl::span<const GraphicsMemoryRegion<GraphicsResource>> inputResourceRegions)
            : GraphicsDeviceObject(std::weak_ptr<GraphicsDevice>(device)),
              _pipeline(std::move(pipeline)),
              _vertexBufferRegion(std::move(vertexBufferRegion)),
              _indexBufferRegion(std::move(indexBufferRegion)),
              _inputResourceRegions(),
              _vertexBufferStride(vertexBufferStride),
              _indexBufferStride(indexBufferStride)
        {
            if (_pipeline == nullptr)
            {
                throw Exceptions::NullPointerException("Parameter name: pipeline.");
            }

            if (GetVertexBufferRegion().GetCollection() == nullptr)
            {
                throw Exceptions::NullPointerException(
                    "The vertex buffer region's memory resource collection is nullptr.");
            }

            if (GetPipeline()->GetDevice() != GetDevice())
            {
                throw Exceptions::InvalidOperationException(
                    "The supplied graphics devices for the primitive and the pipeline do not match.");
            }

            if (GetVertexBufferRegion().GetDevice() != GetDevice())
            {
                throw Exceptions::InvalidOperationException(
                    "The supplied graphics devices for the primitive and the vertex buffer region do not match.");
            }

            if (GetIndexBufferRegion().GetCollection() != nullptr && GetIndexBufferRegion().GetDevice() != GetDevice())
            {
                throw Exceptions::InvalidOperationException(
                    "The supplied graphics devices for the primitive and the index buffer region do not match.");
            }

            _inputResourceRegions = std::vector<GraphicsMemoryRegion<GraphicsResource>>(inputResourceRegions.begin(),
                                                                                        inputResourceRegions.end());
        }

        [[nodiscard]] inline const GraphicsMemoryRegion<GraphicsResource>& GetIndexBufferRegion() const noexcept
        {
            return _indexBufferRegion;
        }

        [[nodiscard]] inline uint32_t GetIndexBufferStride() const noexcept
        {
            return _indexBufferStride;
        }

        [[nodiscard]] inline gsl::span<const GraphicsMemoryRegion<GraphicsResource>> GetInputResourceRegions()
            const noexcept
        {
            return gsl::span<const GraphicsMemoryRegion<GraphicsResource>>(&(*_inputResourceRegions.begin()),
                                                                           _inputResourceRegions.size());
        }

        [[nodiscard]] inline std::shared_ptr<GraphicsPipeline> GetPipeline() const noexcept
        {
            return _pipeline;
        }

        [[nodiscard]] inline const GraphicsMemoryRegion<GraphicsResource>& GetVertexBufferRegion() const noexcept
        {
            return _vertexBufferRegion;
        }

        [[nodiscard]] inline uint32_t GetVertexBufferStride() const noexcept
        {
            return _vertexBufferStride;
        }

        virtual ~GraphicsPrimitive() = default;
    };
} // namespace NovelRT::Experimental::Graphics

#endif // !NOVELRT_EXPERIMENTAL_GRAPHICS_GRAPHICSPRIMITIVE_H
