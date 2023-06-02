// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/NrtErrorHandling.h>
#include <NovelRT.Interop/Utilities/NrtEvent.h>
#include <NovelRT/Timing/Timestamp.h>
#include <NovelRT/Utilities/Event.h>

using namespace NovelRT::Utilities;

/**
 * Generic events
 * ------
 *
 * Events in the C API are implemented in a generic manner to save time,
 * to be less redundant, and keep logic consistent.
 *
 * Due to limitations in the C language, each C++ event type needs a
 * distinct representation in the C API. This representation is composed of:
 *     - An opaque NrtEvent type
 *       (examples: NrtUtilitiesEventHandle, NrtUtilitiesEventWithTimestampHandle)
 *
 *     - A C function pointer type, returning void, and with a void* parameter at the end.
 *       This function pointer indicates what parameter types should be used in C.
 *       (examples: void(void*), void(NrtTimestamp, void*))
 *
 *     - An EventHandler<Args> calling the C function pointer, used to create event handlers
 *       from C function pointers.
 *       This EventHandler converts incoming C++ arguments to their C equivalents.
 *       Example, with func the C function pointer and context the given void* context:
 *          EventHandler<NovelRT::Timing::Timestamp>(
 *              [func, context](auto time) { func(reinterpret_cast<NrtTimestamp&>(time), context); }
 *          )
 *
 *     - An Invoke function, which invokes a C++ event using C parameters.
 *       This function converts incoming C arguments to their C++ equivalents.
 *       Example:
 *          void Invoke(const Event<NovelRT::Timing::Timestamp>& event, NrtTimestamp timestamp)
 *          {
 *              event(NovelRT::Timing::Timestamp(timestamp));
 *          }
 *
 * Those definitions are contained inside specialized instances of the EventImplementationDetails class.
 * For example:
 *      template<> struct EventImplementationDetails<Event<NovelRT::Timing::Timestamp>>
 *      {
 *         using Function = void(NrtTimestamp, void*);
 *         using NrtHandle = NrtUtilitiesEventWithTimestampHandle;
 *
 *         static auto MakeEventHandler(Function func, void* context)
 *         {
 *            return EventHandler<NovelRT::Timing::Timestamp>(
 *                [func, context](auto time) { func(reinterpret_cast<NrtTimestamp&>(time), context); });
 *         }
 *         static void Invoke(const Event<NovelRT::Timing::Timestamp>& event, NrtTimestamp timestamp)
 *         {
 *            event(NovelRT::Timing::Timestamp(timestamp));
 *         }
 *      };
 *
 * Once you have created an EventImplementationDetails class and added all of its required
 * members (see the documentation for it below), you can use the Event<> type inside the
 * generic methods.
 *
 * Those generic methods correspond one-to-one to the exposed C API:
 *     - GenericEvent_Create, creates an event
 *     - GenericEvent_AddEventHandler, adds an event handler using a C function pointer and context
 *     - GenericEvent_RemoveEventHandler, removes an event handler by id
 *     - GenericEvent_Invoke, invokes the event with the given parameters,
 *     - GenericEvent_Destroy, destroys an event
 *
 * You can then declare all C API methods for the event: replace "GenericEvent" with
 * the full event name, such as "Nrt_EventWithTimestamp".
 * And then proceed to define them there by simply calling the GenericEvent methods,
 * with the C++ event type as the template parameter. That's it, that's lit.
 */

/**
 * Defines how a NovelRT::Utilities::Event type should interop with the C API,
 * i.e. how C function pointers are called by C++ and vice-versa.
 *
 * This class must be specialized by the targeted NovelRT::Utilities::Event type.
 *
 * Specializations of this class must be implemented with the following members
 * in order to be make GenericEvent_* methods available:
 *
 * <ul>
 *  <li>A Function type alias, equivalent to the C function pointer used in the C API.
 *      The function pointer is required to take a void* parameter at the end.
 *
 *  <li>A NrtHandle type alias, equivalent to the opaque type handle used in C for this event.
 *
 *  <li>A MakeEventHandler function, with the following signature:
 *          EventHandler<Args> MakeEventHandler(Function func, void* context)
 *      This function should return a C++ NovelRT::Utilities::EventHandler (parameterized with
 *      the right types) calling the C function pointer.
 *
 *  <li>An Invoke function, with the following signature:
 *          void Invoke(const Event<Args>& event, ...)
 *      Where Event should be parameterized with the C++ event parameters types, and
 *      the three dots should be filled with the C function pointer parameters types.
 *      This function should invoke the C++ event using the arguments provided
 *      by the C caller.
 * </ul>
 *
 * @example
 * Here's an example with a C++ event using taking an int.
 * @code
 *
 * struct EventImplementationDetails<Event<int>> {
 *     using Function = void(int, void*);
 *     using NrtHandle = NrtUtilitiesEventWithIntHandle;
 *     static auto MakeEventHandler(Function func, void* context)
 *     {
 *         return EventHandler<int>([func, context](int val){ func(val, context); });
 *     }
 *     static void Invoke(const Event<int>& event, int value)
 *     {
 *         event(value);
 *     }
 * };
 *
 * @endcode
 *
 * @tparam T the parameterized type of NovelRT::Utilities::Event
 */
template<typename T> struct EventImplementationDetails;

template<typename Event, typename Details = EventImplementationDetails<Event>>
typename Details::NrtHandle GenericEvent_Create()
{
    return reinterpret_cast<typename Details::NrtHandle>(new Event());
}

template<typename Event, typename Details = EventImplementationDetails<Event>>
NrtResult GenericEvent_AddEventHandler(typename Details::NrtHandle event,
                                       typename Details::Function handler,
                                       void* context,
                                       NrtCoreAtom* outputEventHandlerId)
{
    if (event == nullptr)
    {
        Nrt_setErrMsgIsNullArgumentProvidedInternal();
        return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
    }

    if (handler == nullptr)
    {
        Nrt_setErrMsgIsNullArgumentProvidedInternal();
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
NrtResult GenericEvent_RemoveEventHandler(typename Details::NrtHandle event, NrtCoreAtom eventHandlerId)
{
    if (event == nullptr)
    {
        Nrt_setErrMsgIsNullArgumentProvidedInternal();
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
        Nrt_setErrMsgIsNullArgumentProvidedInternal();
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
        Nrt_setErrMsgIsNullInstanceProvidedInternal();
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
                                    NrtCoreAtom* outputEventHandlerId)
{
    return GenericEvent_AddEventHandler<Event<>>(event, handler, context, outputEventHandlerId);
}

NrtResult Nrt_Event_RemoveEventHandler(NrtUtilitiesEventHandle event, NrtCoreAtom eventHandlerId)
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
        return EventHandler<NovelRT::Timing::Timestamp>(
            [func, context](auto time) { func(reinterpret_cast<NrtTimestamp&>(time), context); });
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
                                                 NrtCoreAtom* outputEventHandlerId)
{
    return GenericEvent_AddEventHandler<Event<NovelRT::Timing::Timestamp>>(event, handler, context,
                                                                           outputEventHandlerId);
}
NrtResult Nrt_EventWithTimestamp_RemoveEventHandler(NrtUtilitiesEventWithTimestampHandle event, NrtCoreAtom eventHandlerId)
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
