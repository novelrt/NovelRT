// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

using NUnit.Framework;
using System.Runtime.InteropServices;

namespace NovelRT.Interop.UnitTests
{
    /// <summary>Provides validation of the <see cref="NrtGeoMatrix4x4F" /> struct.</summary>
    public static unsafe class NrtGeoMatrix4x4FTests
    {
        /// <summary>Validates that the <see cref="NrtGeoMatrix4x4F" /> struct is blittable.</summary>
        [Test]
        public static void IsBlittableTest()
        {
            Assert.That(Marshal.SizeOf<NrtGeoMatrix4x4F>(), Is.EqualTo(sizeof(NrtGeoMatrix4x4F)));
        }

        /// <summary>Validates that the <see cref="NrtGeoMatrix4x4F" /> struct has the right <see cref="LayoutKind" />.</summary>
        [Test]
        public static void IsLayoutSequentialTest()
        {
            Assert.That(typeof(NrtGeoMatrix4x4F).IsLayoutSequential, Is.True);
        }

        /// <summary>Validates that the <see cref="NrtGeoMatrix4x4F" /> struct has the correct size.</summary>
        [Test]
        public static void SizeOfTest()
        {
            Assert.That(sizeof(NrtGeoMatrix4x4F), Is.EqualTo(64));
        }
    }
}
