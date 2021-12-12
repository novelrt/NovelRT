// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

namespace NovelRT.Interop
{
    public partial struct NrtAudioEmitterComponent
    {
        [NativeTypeName("uint32_t")]
        public uint handle;

        [NativeTypeName("int32_t")]
        public int isMusic;

        [NativeTypeName("int32_t")]
        public int numberOfLoops;

        public float volume;
    }
}
