#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <memory>

namespace NovelRT::Windowing
{
    template<typename TBackend> struct WindowingBackendTraits;

    template <typename TBackend>
    class WindowProvider
    {
    public:
        using BackendWindowProviderType = WindowingBackendTraits<TBackend>::WindowProviderType;

    private:
        std::unique_ptr<BackendWindowProviderType> _implementation;

    public:
        WindowProvider(std::unique_ptr<BackendWindowProviderType> implementation)
            : _implementation(std::move(implementation))
        { }

        [[nodiscard]] BackendWindowProviderType* GetImplementation() const noexcept
        {
            return _implementation.get();
        }
    };
}
