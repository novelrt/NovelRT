// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/NrtErrorHandling.h>
#include <NovelRT.Interop/Utilities/NrtEvent.h>
#include <NovelRT/Timing/Timestamp.h>
#include <NovelRT/Utilities/Event.h>

using namespace NovelRT::Utilities;

template<typename T> struct EventImplementationDetails;

// Example:
//
// template <>
// struct EventImplementationDetails<Event<int>> {
//     using Function = void(int, void*);
//     using NrtHandle = NrtUtilitiesEventWithIntHandle;
//
//     static auto MakeEventHandler(FunctionType func, void* context) {
//         return EventHandler<int>([func, context](int val){ func(val, context); });
//     }
//     static void Invoke(const Event<int>& event, int value)
//     {
//         event(value);
//     }
// };

template<typename Event, typename Details = EventImplementationDetails<Event>>
typename Details::NrtHandle GenericEvent_Create()
{
    return reinterpret_cast<typename Details::NrtHandle>(new Event());
}

template<typename Event, typename Details = EventImplementationDetails<Event>>
NrtResult GenericEvent_AddEventHandler(typename Details::NrtHandle event,
                                       typename Details::Function handler,
                                       void* context,
                                       NrtAtom* outputEventHandlerId)
{
    if (event == nullptr)
    {
        Nrt_setErrIsNullInstanceProvidedInternal();
        return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
    }

    if (handler == nullptr)
    {
        Nrt_setErrIsNullArgProvidedInternal();
        return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
    }

    auto* novelEvent = reinterpret_cast<Event*>(event);
    auto&& eventHandler = Details::MakeEventHandler(handler, context);
    *novelEvent += eventHandler;
    if (outputEventHandlerId != nullptr)
    {
        *outputEventHandlerId = eventHandler.getId();
    }

    return NRT_SUCCESS;
}

template<typename Event, typename Details = EventImplementationDetails<Event>>
NrtResult GenericEvent_RemoveEventHandler(typename Details::NrtHandle event, NrtAtom eventHandlerId)
{
    if (event == nullptr)
    {
        Nrt_setErrIsNullInstanceProvidedInternal();
        return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
    }

    auto* novelEvent = reinterpret_cast<Event*>(event);
    novelEvent -= eventHandlerId;
    return NRT_SUCCESS;
}

template<typename Event, typename... Args, typename Details = EventImplementationDetails<Event>>
NrtResult GenericEvent_Invoke(typename Details::NrtHandle event, Args&&... args)
{
    if (event == nullptr)
    {
        Nrt_setErrIsNullInstanceProvidedInternal();
        return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
    }

    auto* novelEvent = reinterpret_cast<Event*>(event);
    Details::Invoke(*novelEvent, std::forward<Args>(args)...);
    return NRT_SUCCESS;
}

template<typename Event, typename Details = EventImplementationDetails<Event>>
NrtResult GenericEvent_Destroy(typename Details::NrtHandle event)
{
    if (event == nullptr)
    {
        Nrt_setErrIsNullInstanceProvidedInternal();
        return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
    }

    delete reinterpret_cast<Event*>(event);
    return NRT_SUCCESS;
}

// Event<>

template<> struct EventImplementationDetails<Event<>>
{
    using Function = void(void*);
    using NrtHandle = NrtUtilitiesEventHandle;

    static auto MakeEventHandler(Function func, void* context)
    {
        return EventHandler<>([func, context]() { func(context); });
    }
    static void Invoke(const Event<>& event)
    {
        event();
    }
};

NrtUtilitiesEventHandle Nrt_Event_Create()
{
    return GenericEvent_Create<Event<>>();
}

NrtResult Nrt_Event_AddEventHandler(NrtUtilitiesEventHandle event,
                                    void (*handler)(void*),
                                    void* context,
                                    NrtAtom* outputEventHandlerId)
{
    return GenericEvent_AddEventHandler<Event<>>(event, handler, context, outputEventHandlerId);
}

NrtResult Nrt_Event_RemoveEventHandler(NrtUtilitiesEventHandle event, NrtAtom eventHandlerId)
{
    return GenericEvent_RemoveEventHandler<Event<>>(event, eventHandlerId);
}

NrtResult Nrt_Event_Invoke(NrtUtilitiesEventHandle event)
{
    return GenericEvent_Invoke<Event<>>(event);
}

NrtResult Nrt_Event_Destroy(NrtUtilitiesEventHandle event)
{
    return GenericEvent_Destroy<Event<>>(event);
}

// Event<NovelRT::Timing::Timestamp>

template<> struct EventImplementationDetails<Event<NovelRT::Timing::Timestamp>>
{
    using Function = void(NrtTimestamp, void*);
    using NrtHandle = NrtUtilitiesEventWithTimestampHandle;

    static auto MakeEventHandler(Function func, void* context)
    {
        return EventHandler<NovelRT::Timing::Timestamp>([func, context](auto time)
                                                        { func(reinterpret_cast<NrtTimestamp&>(time), context); });
    }
    static void Invoke(const Event<NovelRT::Timing::Timestamp>& event, NrtTimestamp timestamp)
    {
        event(NovelRT::Timing::Timestamp(timestamp));
    }
};

NrtUtilitiesEventWithTimestampHandle Nrt_EventWithTimestamp_Create()
{
    return GenericEvent_Create<Event<NovelRT::Timing::Timestamp>>();
}
NrtResult Nrt_EventWithTimestamp_AddEventHandler(NrtUtilitiesEventWithTimestampHandle event,
                                                 void (*handler)(NrtTimestamp, void*),
                                                 void* context,
                                                 NrtAtom* outputEventHandlerId)
{
    return GenericEvent_AddEventHandler<Event<NovelRT::Timing::Timestamp>>(event, handler, context,
                                                                           outputEventHandlerId);
}
NrtResult Nrt_EventWithTimestamp_RemoveEventHandler(NrtUtilitiesEventWithTimestampHandle event, NrtAtom eventHandlerId)
{
    return GenericEvent_RemoveEventHandler<Event<NovelRT::Timing::Timestamp>>(event, eventHandlerId);
}
NrtResult Nrt_EventWithTimestamp_Invoke(NrtUtilitiesEventWithTimestampHandle event, NrtTimestamp timestamp)
{
    return GenericEvent_Invoke<Event<NovelRT::Timing::Timestamp>>(event, timestamp);
}
NrtResult Nrt_EventWithTimestamp_Destroy(NrtUtilitiesEventWithTimestampHandle event)
{
    return GenericEvent_Destroy<Event<NovelRT::Timing::Timestamp>>(event);
}
