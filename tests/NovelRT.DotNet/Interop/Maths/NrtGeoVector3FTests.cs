// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

using NUnit.Framework;
using System.Runtime.InteropServices;

namespace NovelRT.Interop.UnitTests
{
    /// <summary>Provides validation of the <see cref="NrtGeoVector3F" /> struct.</summary>
    public static unsafe class NrtGeoVector3FTests
    {
        /// <summary>Validates that the <see cref="NrtGeoVector3F" /> struct is blittable.</summary>
        [Test]
        public static void IsBlittableTest()
        {
            Assert.That(Marshal.SizeOf<NrtGeoVector3F>(), Is.EqualTo(sizeof(NrtGeoVector3F)));
        }

        /// <summary>Validates that the <see cref="NrtGeoVector3F" /> struct has the right <see cref="LayoutKind" />.</summary>
        [Test]
        public static void IsLayoutSequentialTest()
        {
            Assert.That(typeof(NrtGeoVector3F).IsLayoutSequential, Is.True);
        }

        /// <summary>Validates that the <see cref="NrtGeoVector3F" /> struct has the correct size.</summary>
        [Test]
        public static void SizeOfTest()
        {
            Assert.That(sizeof(NrtGeoVector3F), Is.EqualTo(12));
        }
    }
}
