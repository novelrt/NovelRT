// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

using NUnit.Framework;
using System.Runtime.InteropServices;

namespace NovelRT.Interop.UnitTests
{
    /// <summary>Provides validation of the <see cref="NrtAudioEmitterComponent" /> struct.</summary>
    public static unsafe class NrtAudioEmitterComponentTests
    {
        /// <summary>Validates that the <see cref="NrtAudioEmitterComponent" /> struct is blittable.</summary>
        [Test]
        public static void IsBlittableTest()
        {
            Assert.That(Marshal.SizeOf<NrtAudioEmitterComponent>(), Is.EqualTo(sizeof(NrtAudioEmitterComponent)));
        }

        /// <summary>Validates that the <see cref="NrtAudioEmitterComponent" /> struct has the right <see cref="LayoutKind" />.</summary>
        [Test]
        public static void IsLayoutSequentialTest()
        {
            Assert.That(typeof(NrtAudioEmitterComponent).IsLayoutSequential, Is.True);
        }

        /// <summary>Validates that the <see cref="NrtAudioEmitterComponent" /> struct has the correct size.</summary>
        [Test]
        public static void SizeOfTest()
        {
            Assert.That(sizeof(NrtAudioEmitterComponent), Is.EqualTo(16));
        }
    }
}
