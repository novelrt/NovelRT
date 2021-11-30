// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

namespace NovelRT.Interop
{
    public enum NrtAudioEmitterStateKind
    {
        NRT_EMITTER_STATE_DONE = 0,
        NRT_EMITTER_STATE_TO_PLAY = 1,
        NRT_EMITTER_STATE_PLAYING = 2,
        NRT_EMITTER_STATE_TO_STOP = 3,
        NRT_EMITTER_STATE_STOPPED = 4,
        NRT_EMITTER_STATE_TO_PAUSE = 5,
        NRT_EMITTER_STATE_PAUSED = 6,
        NRT_EMITTER_STATE_TO_RESUME = 7,
        NRT_EMITTER_STATE_TO_FADE_IN = 8,
        NRT_EMITTER_STATE_FADING_IN = 9,
        NRT_EMITTER_STATE_TO_FADE_OUT = 10,
        NRT_EMITTER_STATE_FADING_OUT = 11,
    }
}
