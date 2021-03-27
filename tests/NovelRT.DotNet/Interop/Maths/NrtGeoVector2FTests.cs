// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

using NUnit.Framework;
using System.Runtime.InteropServices;

namespace NovelRT.Interop.UnitTests
{
    /// <summary>Provides validation of the <see cref="NrtGeoVector2F" /> struct.</summary>
    public static unsafe class NrtGeoVector2FTests
    {
        /// <summary>Validates that the <see cref="NrtGeoVector2F" /> struct is blittable.</summary>
        [Test]
        public static void IsBlittableTest()
        {
            Assert.That(Marshal.SizeOf<NrtGeoVector2F>(), Is.EqualTo(sizeof(NrtGeoVector2F)));
        }

        /// <summary>Validates that the <see cref="NrtGeoVector2F" /> struct has the right <see cref="LayoutKind" />.</summary>
        [Test]
        public static void IsLayoutSequentialTest()
        {
            Assert.That(typeof(NrtGeoVector2F).IsLayoutSequential, Is.True);
        }

        /// <summary>Validates that the <see cref="NrtGeoVector2F" /> struct has the correct size.</summary>
        [Test]
        public static void SizeOfTest()
        {
            Assert.That(sizeof(NrtGeoVector2F), Is.EqualTo(8));
        }
    }
}
