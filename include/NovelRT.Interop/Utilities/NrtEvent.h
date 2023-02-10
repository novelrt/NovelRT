// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.
#ifndef NOVELRT_INTEROP_UTILITIES_NRTEVENT_H
#define NOVELRT_INTEROP_UTILITIES_NRTEVENT_H

#include "../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    // Event<>
    NrtUtilitiesEventHandle Nrt_Event_Create();

    NrtResult Nrt_Event_AddEventHandler(NrtUtilitiesEventHandle event,
                                        void (*handler)(void*),
                                        void* context,
                                        NrtAtom* outputEventHandlerId);

    NrtResult Nrt_Event_RemoveEventHandler(NrtUtilitiesEventHandle event, NrtAtom eventHandlerId);

    NrtResult Nrt_Event_Invoke(NrtUtilitiesEventHandle event);

    NrtResult Nrt_Event_Destroy(NrtUtilitiesEventHandle event);

    // Event<NovelRT::Timing::Timestamp>
    NrtUtilitiesEventWithTimestampHandle Nrt_EventWithTimestamp_Create();

    NrtResult Nrt_EventWithTimestamp_AddEventHandler(NrtUtilitiesEventWithTimestampHandle event,
                                                     void (*handler)(NrtTimestamp, void*),
                                                     void* context,
                                                     NrtAtom* outputEventHandlerId);

    NrtResult Nrt_EventWithTimestamp_RemoveEventHandler(NrtUtilitiesEventWithTimestampHandle event,
                                                        NrtAtom eventHandlerId);

    NrtResult Nrt_EventWithTimestamp_Invoke(NrtUtilitiesEventWithTimestampHandle event, NrtTimestamp timestamp);

    NrtResult Nrt_EventWithTimestamp_Destroy(NrtUtilitiesEventWithTimestampHandle event);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_UTILITIES_NRTEVENT_H
