// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

using NUnit.Framework;
using System.Runtime.InteropServices;

namespace NovelRT.Interop.UnitTests
{
    /// <summary>Provides validation of the <see cref="NrtTransform" /> struct.</summary>
    public static unsafe class NrtTransformTests
    {
        /// <summary>Validates that the <see cref="NrtTransform" /> struct is blittable.</summary>
        [Test]
        public static void IsBlittableTest()
        {
            Assert.That(Marshal.SizeOf<NrtTransform>(), Is.EqualTo(sizeof(NrtTransform)));
        }

        /// <summary>Validates that the <see cref="NrtTransform" /> struct has the right <see cref="LayoutKind" />.</summary>
        [Test]
        public static void IsLayoutSequentialTest()
        {
            Assert.That(typeof(NrtTransform).IsLayoutSequential, Is.True);
        }

        /// <summary>Validates that the <see cref="NrtTransform" /> struct has the correct size.</summary>
        [Test]
        public static void SizeOfTest()
        {
            Assert.That(sizeof(NrtTransform), Is.EqualTo(20));
        }
    }
}
