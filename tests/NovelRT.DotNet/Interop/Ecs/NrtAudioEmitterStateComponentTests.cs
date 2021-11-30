// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

using NUnit.Framework;
using System.Runtime.InteropServices;

namespace NovelRT.Interop.UnitTests
{
    /// <summary>Provides validation of the <see cref="NrtAudioEmitterStateComponent" /> struct.</summary>
    public static unsafe class NrtAudioEmitterStateComponentTests
    {
        /// <summary>Validates that the <see cref="NrtAudioEmitterStateComponent" /> struct is blittable.</summary>
        [Test]
        public static void IsBlittableTest()
        {
            Assert.That(Marshal.SizeOf<NrtAudioEmitterStateComponent>(), Is.EqualTo(sizeof(NrtAudioEmitterStateComponent)));
        }

        /// <summary>Validates that the <see cref="NrtAudioEmitterStateComponent" /> struct has the right <see cref="LayoutKind" />.</summary>
        [Test]
        public static void IsLayoutSequentialTest()
        {
            Assert.That(typeof(NrtAudioEmitterStateComponent).IsLayoutSequential, Is.True);
        }

        /// <summary>Validates that the <see cref="NrtAudioEmitterStateComponent" /> struct has the correct size.</summary>
        [Test]
        public static void SizeOfTest()
        {
            Assert.That(sizeof(NrtAudioEmitterStateComponent), Is.EqualTo(12));
        }
    }
}
