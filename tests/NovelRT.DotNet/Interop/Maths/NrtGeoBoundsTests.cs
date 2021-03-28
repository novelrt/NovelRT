// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

using NUnit.Framework;
using System.Runtime.InteropServices;

namespace NovelRT.Interop.UnitTests
{
    /// <summary>Provides validation of the <see cref="NrtGeoBounds" /> struct.</summary>
    public static unsafe class NrtGeoBoundsTests
    {
        /// <summary>Validates that the <see cref="NrtGeoBounds" /> struct is blittable.</summary>
        [Test]
        public static void IsBlittableTest()
        {
            Assert.That(Marshal.SizeOf<NrtGeoBounds>(), Is.EqualTo(sizeof(NrtGeoBounds)));
        }

        /// <summary>Validates that the <see cref="NrtGeoBounds" /> struct has the right <see cref="LayoutKind" />.</summary>
        [Test]
        public static void IsLayoutSequentialTest()
        {
            Assert.That(typeof(NrtGeoBounds).IsLayoutSequential, Is.True);
        }

        /// <summary>Validates that the <see cref="NrtGeoBounds" /> struct has the correct size.</summary>
        [Test]
        public static void SizeOfTest()
        {
            Assert.That(sizeof(NrtGeoBounds), Is.EqualTo(20));
        }
    }
}
