// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_FUTURERESULT_H
#define NOVELRT_FUTURERESULT_H

#ifndef NOVELRT_EXPERIMENTAL_THREADING_H
#error NovelRT does not support including types explicitly by default. Please include Threading.h instead for the Threading namespace subset.
#endif

namespace NovelRT::Experimental::Threading
{
    template<typename TResultType> class FutureResult
    {
    private:
        ConcurrentSharedPtr<TResultType> _dataContainer;
        TResultType _nullState;

    public:
        FutureResult(ConcurrentSharedPtr<TResultType> dataContainer, TResultType nullState)
            : _dataContainer(std::move(dataContainer)), _nullState(nullState)
        {
            if (_dataContainer == nullptr)
            {
                throw Exceptions::NullPointerException();
            }
        }

        [[nodiscard]] bool IsValueCreated() noexcept
        {
            TResultType dummy;
            return TryGetValue(dummy);
        }

        [[nodiscard]] bool TryGetValue(TResultType& outValue) noexcept
        {
            std::scoped_lock<ConcurrentSharedPtr<TResultType>> ptrLock(_dataContainer);

            if (*_dataContainer == _nullState)
            {
                return false;
            }

            outValue = *_dataContainer;
            return true;
        }

        [[nodiscard]] TResultType& GetValue()
        {
            if (!IsValueCreated())
            {
                throw Exceptions::InvalidOperationException("The value is not set at the time of accessing.");
            }

            return *_dataContainer;
        }

        [[nodiscard]] ConcurrentSharedPtr<TResultType> GetBackingConcurrentSharedPtr() const noexcept
        {
            return _dataContainer;
        }
    };
}

#endif // NOVELRT_FUTURERESULT_H
