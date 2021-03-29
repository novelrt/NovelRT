// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

using NUnit.Framework;
using System.Runtime.InteropServices;

namespace NovelRT.Interop.UnitTests
{
    /// <summary>Provides validation of the <see cref="NrtGeoVector4F" /> struct.</summary>
    public static unsafe class NrtGeoVector4FTests
    {
        /// <summary>Validates that the <see cref="NrtGeoVector4F" /> struct is blittable.</summary>
        [Test]
        public static void IsBlittableTest()
        {
            Assert.That(Marshal.SizeOf<NrtGeoVector4F>(), Is.EqualTo(sizeof(NrtGeoVector4F)));
        }

        /// <summary>Validates that the <see cref="NrtGeoVector4F" /> struct has the right <see cref="LayoutKind" />.</summary>
        [Test]
        public static void IsLayoutSequentialTest()
        {
            Assert.That(typeof(NrtGeoVector4F).IsLayoutSequential, Is.True);
        }

        /// <summary>Validates that the <see cref="NrtGeoVector4F" /> struct has the correct size.</summary>
        [Test]
        public static void SizeOfTest()
        {
            Assert.That(sizeof(NrtGeoVector4F), Is.EqualTo(16));
        }
    }
}
