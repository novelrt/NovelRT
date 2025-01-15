#include <NovelRT/Graphics/GraphicsAdapter.hpp>

namespace NovelRT::Graphics
{

    template<typename TBackend>
    GraphicsAdapter<TBackend>::GraphicsAdapter(std::shared_ptr<BackendAdapterType> implementation,
                                               std::shared_ptr<GraphicsProvider<TBackend>> provider)
        : _implementation(_implementation), _provider(provider)
    {
        if (_provider.expired())
        {
            throw Exceptions::NullPointerException(
                "The provided GraphicsProvider pointer is nullptr or an invalid pointer.");
        }
    }

    template<typename TBackend> uint32_t GraphicsAdapter<TBackend>::GetDeviceId()
    {
        return _implementation->GetDeviceId();
    }

    template<typename TBackend> const std::string& GraphicsAdapter<TBackend>::GetName()
    {
        return _implementation->GetName();
    }

    template<typename TBackend>
    std::shared_ptr<GraphicsProvider<TBackend>> GraphicsAdapter<TBackend>::GetProvider() const
    {
        return _provider;
    }

    template<typename TBackend> uint32_t GraphicsAdapter<TBackend>::GetVendorId()
    {
        return _implementation->GetVendorId();
    }

    template<typename TBackend>
    std::shared_ptr<GraphicsDevice<TBackend>> GraphicsAdapter<TBackend>::CreateDevice(
        std::shared_ptr<GraphicsSurfaceContext<TBackend>> surfaceContext,
        int32_t contextCount)
    {
        return _implementation->CreateDevice(surfaceContext, contextCount);
    }
}