#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/EngineConfig.h>
#include <memory>
#include <vector>

namespace NovelRT::Graphics
{
    template<typename TBackend> class GraphicsAdapter;
    template<typename TBackend> struct GraphicsBackendTraits;
    template<typename TBackend> class GraphicsProvider;
}

namespace NovelRT::Graphics::Details
{
    template <typename TBackend> struct GraphicsAdapterIterator
    {
        private:
            using BackendProviderType = typename GraphicsBackendTraits<TBackend>::ProviderType;
            using BackendIteratorType = decltype(std::declval<BackendProviderType>().begin());

            BackendIteratorType _iterator;
            std::shared_ptr<GraphicsProvider<TBackend>> _provider;

        public:
            GraphicsAdapterIterator(BackendIteratorType const& it, std::shared_ptr<GraphicsProvider<TBackend>> provider)
                : _iterator(it), _provider(provider)
            { }

            using difference_type = typename std::iterator_traits<BackendIteratorType>::difference_type;
            using value_type = std::shared_ptr<GraphicsAdapter<TBackend>>;
            using pointer = void;
            using reference = void;
            using iterator_category = std::input_iterator_tag;

            inline bool operator==(GraphicsAdapterIterator<TBackend> const& other)
            {
                return _provider == other._provider
                    && _iterator == other._iterator;
            }

            inline bool operator!=(GraphicsAdapterIterator<TBackend> const& other)
            {
                return _provider != other._provider
                    || _iterator != other._iterator;
            }

            inline auto operator*() const
            {
                return std::make_shared<GraphicsAdapter<TBackend>>(*_iterator, _provider);
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
    template<typename TBackend> class GraphicsProvider : public std::enable_shared_from_this<GraphicsProvider<TBackend>>
    {
    public:
        using BackendProviderType = typename GraphicsBackendTraits<TBackend>::ProviderType;

        using iterator = typename Details::GraphicsAdapterIterator<TBackend>;

    private:
        std::shared_ptr<BackendProviderType> _implementation;
        bool _debugModeEnabled;

    public:
        static inline const std::string EnableDebugModeSwitchName =
            "NovelRT::Graphics::GraphicsProvider::EnableDebugMode";

        GraphicsProvider(std::shared_ptr<BackendProviderType> implementation) noexcept
            : _implementation(implementation), _debugModeEnabled(EngineConfig::EnableDebugOutputFromEngineInternals())
        {
        }

        virtual ~GraphicsProvider() = default;

        [[nodiscard]] std::shared_ptr<BackendProviderType> GetImplementation() const noexcept
        {
            return _implementation;
        }

        [[nodiscard]] bool GetDebugModeEnabled() const noexcept
        {
            return _debugModeEnabled;
        }

        [[nodiscard]] iterator begin() noexcept
        {
            return iterator{_implementation->begin(), this->shared_from_this()};
        }

        [[nodiscard]] iterator end() noexcept
        {
            return iterator{_implementation->end(), this->shared_from_this()};
        }

        [[nodiscard]] uint32_t GetApiVersion() const noexcept
        {
            return _implementation->GetApiVersion();
        }
    };
}
