// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

namespace NovelRT.Interop
{
    public partial struct NrtAudioEmitterStateComponent
    {
        [NativeTypeName("NrtAudioEmitterState")]
        public int state;

        public float fadeDuration;

        public float fadeExpectedVolume;
    }
}
