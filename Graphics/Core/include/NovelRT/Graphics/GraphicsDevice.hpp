#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Exceptions/Exceptions.h>
#include <NovelRT/Graphics/GraphicsPipelineBlendFactor.hpp>
#include <NovelRT/Graphics/GraphicsPushConstantRange.hpp>
#include <NovelRT/Graphics/GraphicsSurfaceContext.hpp>
#include <NovelRT/Graphics/IGraphicsSurface.hpp>
#include <NovelRT/Graphics/ShaderProgramKind.hpp>
#include <NovelRT/Utilities/Misc.h>
#include <memory>
#include <stdexcept>

namespace NovelRT::Graphics
{
    template<typename TBackend> class GraphicsAdapter;
    template<typename TBackend> class GraphicsFence;
    template<typename TBackend> class GraphicsSurfaceContext;
    template<typename TBackend> class GraphicsContext;
    template<typename TBackend> class GraphicsPipeline;
    template<typename TBackend> class GraphicsDevice;
    template<typename TBackend> class GraphicsRenderPass;
    class GraphicsPipelineInput;
    class GraphicsPipelineResource;
    template<typename TBackend> class GraphicsPipelineSignature;
    template<typename TBackend> class ShaderProgram;

    template<typename TBackend> struct GraphicsBackendTraits;
}

namespace NovelRT::Graphics::Details
{
    template<typename TBackend> struct GraphicsContextIterator
    {
    private:
        using BackendDeviceType = typename GraphicsBackendTraits<TBackend>::DeviceType;
        using BackendIteratorType = decltype(std::declval<BackendDeviceType>().begin());

        BackendIteratorType _iterator;
        std::shared_ptr<GraphicsDevice<TBackend>> _provider;

    public:
        GraphicsContextIterator(BackendIteratorType const& it, std::shared_ptr<GraphicsDevice<TBackend>> provider)
            : _iterator(it), _provider(provider)
        {
        }

        using difference_type = typename std::iterator_traits<BackendIteratorType>::difference_type;
        using value_type = std::shared_ptr<GraphicsContext<TBackend>>;
        using pointer = void;
        using reference = void;
        using iterator_category = std::input_iterator_tag;

        inline bool operator==(GraphicsContextIterator<TBackend> const& other)
        {
            return _provider == other._provider && _iterator == other._iterator;
        }

        inline bool operator!=(GraphicsContextIterator<TBackend> const& other)
        {
            return _provider != other._provider || _iterator != other._iterator;
        }

        inline auto operator*() const
        {
            return std::make_shared<GraphicsContext<TBackend>>(*_iterator, _provider, _iterator->GetIndex());
        }

        inline auto operator++()
        {
            ++_iterator;
            return *this;
        }

        inline auto operator++(int)
        {
            auto prev = *this;
            ++_iterator;
            return prev;
        }
    };
}

namespace NovelRT::Graphics
{
    template<typename TBackend> class GraphicsDevice : public std::enable_shared_from_this<GraphicsDevice<TBackend>>
    {
    public:
        using BackendDeviceType = typename GraphicsBackendTraits<TBackend>::DeviceType;

        using iterator = typename Details::GraphicsContextIterator<TBackend>;

    private:
        std::shared_ptr<BackendDeviceType> _implementation;
        std::weak_ptr<GraphicsAdapter<TBackend>> _adapter;
        std::shared_ptr<GraphicsSurfaceContext<TBackend>> _surfaceContext;

    public:
        GraphicsDevice(std::shared_ptr<BackendDeviceType> implementation,
                       std::weak_ptr<GraphicsAdapter<TBackend>> adapter,
                       std::shared_ptr<GraphicsSurfaceContext<TBackend>> surfaceContext)
            : _implementation(implementation), _adapter(adapter), _surfaceContext(surfaceContext)
        {
            if (_adapter.expired())
            {
                throw Exceptions::NullPointerException("The supplied GraphicsAdapter is nullptr.");
            }

            if (_surfaceContext == nullptr)
            {
                throw Exceptions::NullPointerException("The supplied GraphicsSurfaceContext is nullptr.");
            }
        }

        [[nodiscard]] std::shared_ptr<BackendDeviceType> GetImplementation() const noexcept
        {
            return _implementation;
        }

        void TearDown()
        {
            _implementation->TearDown();
        }

        [[nodiscard]] std::shared_ptr<GraphicsAdapter<TBackend>> GetAdapter() const
        {
            if (_adapter.expired())
            {
                throw std::runtime_error("Adapter has expired!");
            }

            return _adapter.lock();
        }

        [[nodiscard]] size_t GetContextIndex() const noexcept
        {
            return _implementation->GetContextIndex();
        }

        [[nodiscard]] iterator begin() noexcept
        {
            return iterator{_implementation->begin(), this->shared_from_this()};
        }

        [[nodiscard]] iterator end() noexcept
        {
            return iterator{_implementation->end(), this->shared_from_this()};
        }

        [[nodiscard]] std::shared_ptr<GraphicsContext<TBackend>> GetCurrentContext()
        {
            return std::make_shared<GraphicsContext<TBackend>>(_implementation->GetCurrentContext(),
                                                               this->shared_from_this(), GetContextIndex());
        }

        [[nodiscard]] inline std::shared_ptr<IGraphicsSurface> GetSurface() const noexcept
        {
            return _surfaceContext->GetSurface();
        }

        [[nodiscard]] inline std::shared_ptr<GraphicsSurfaceContext<TBackend>> GetSurfaceContext() const noexcept
        {
            return _surfaceContext;
        }

        [[nodiscard]] std::shared_ptr<GraphicsPipeline<TBackend>> CreatePipeline(
            std::shared_ptr<GraphicsPipelineSignature<TBackend>> signature,
            std::shared_ptr<ShaderProgram<TBackend>> vertexShader,
            std::shared_ptr<ShaderProgram<TBackend>> pixelShader)
        {
            return std::make_shared<GraphicsPipeline<TBackend>>(
                _implementation->CreatePipeline(signature->GetImplementation(), vertexShader->GetImplementation(),
                                                pixelShader->GetImplementation()),
                this->shared_from_this(), signature, vertexShader, pixelShader);
        }

        [[nodiscard]] std::shared_ptr<GraphicsPipelineSignature<TBackend>> CreatePipelineSignature(
            GraphicsPipelineBlendFactor srcBlendFactor,
            GraphicsPipelineBlendFactor dstBlendFactor,
            NovelRT::Utilities::Misc::Span<GraphicsPipelineInput> inputs,
            NovelRT::Utilities::Misc::Span<GraphicsPipelineResource> resources,
            NovelRT::Utilities::Misc::Span<GraphicsPushConstantRange> pushConstantRanges)
        {
            return std::make_shared<GraphicsPipelineSignature<TBackend>>(
                _implementation->CreatePipelineSignature(srcBlendFactor, dstBlendFactor, inputs, resources, pushConstantRanges),
                this->shared_from_this(), srcBlendFactor, dstBlendFactor, inputs, resources, pushConstantRanges);
        }

        [[nodiscard]] std::shared_ptr<GraphicsRenderPass<TBackend>> GetRenderPass()
        {
            return std::make_shared<GraphicsRenderPass<TBackend>>(_implementation->GetRenderPass());
        }

        [[nodiscard]] std::shared_ptr<ShaderProgram<TBackend>> CreateShaderProgram(
            std::string entryPointName,
            ShaderProgramKind kind,
            NovelRT::Utilities::Misc::Span<uint8_t> byteData)
        {
            return std::make_shared<ShaderProgram<TBackend>>(
                _implementation->CreateShaderProgram(entryPointName, kind, byteData), this->shared_from_this(),
                entryPointName, kind);
        }

        void PresentFrame()
        {
            _implementation->PresentFrame();
        }

        void Signal(std::shared_ptr<GraphicsFence<TBackend>> fence)
        {
            _implementation->Signal(fence->GetImplementation());
        }

        void WaitForIdle()
        {
            _implementation->WaitForIdle();
        }
    };
}
