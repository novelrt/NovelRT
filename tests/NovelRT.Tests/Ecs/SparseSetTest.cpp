// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/NovelRT.h>
#include <atomic>
#include <gtest/gtest.h>

using namespace NovelRT;
using namespace NovelRT::Ecs;

TEST(SparseSetTest, InsertDoesNotThrowWhenAddingValidItemToCollection)
{
    SparseSet<NovelRT::Core::Atom, int32_t> testSet;
    EXPECT_NO_THROW(testSet.Insert(NovelRT::Core::Atom(0), 1));
}

TEST(SparseSetTest, InsertThrowsWhenDuplicateKeyIsAddedToCollection)
{
    SparseSet<NovelRT::Core::Atom, int32_t> testSet;
    ASSERT_NO_THROW(testSet.Insert(NovelRT::Core::Atom(0), 1));
    EXPECT_THROW(testSet.Insert(NovelRT::Core::Atom(0), 1), std::exception);
}

TEST(SparseSetTest, RemoveDoesNotThrowWhenRemovingValidItemFromCollection)
{
    SparseSet<NovelRT::Core::Atom, int32_t> testSet;
    ASSERT_NO_THROW(testSet.Insert(NovelRT::Core::Atom(0), 1));
    EXPECT_NO_THROW(testSet.Remove(NovelRT::Core::Atom(0)));
}

TEST(SparseSetTest, RemoveDoesThrowWhenRemovingNonexistentKeyFromCollection)
{
    SparseSet<NovelRT::Core::Atom, int32_t> testSet;
    ASSERT_NO_THROW(testSet.Insert(NovelRT::Core::Atom(0), 1));
    ASSERT_NO_THROW(testSet.Remove(NovelRT::Core::Atom(0)));
    EXPECT_THROW(testSet.Remove(NovelRT::Core::Atom(0)), std::exception);
}

TEST(SparseSetTest, InsertInsertsValidItemCorrectly)
{
    SparseSet<NovelRT::Core::Atom, int32_t> testSet;
    ASSERT_NO_THROW(testSet.Insert(NovelRT::Core::Atom(0), 1));
    EXPECT_EQ(testSet[NovelRT::Core::Atom(0)], 1);
}

TEST(SparseSetTest, RemoveUpdatesSetCorrectlyAfterRemovingElement)
{
    SparseSet<NovelRT::Core::Atom, int32_t> testSet;
    ASSERT_NO_THROW(testSet.Insert(NovelRT::Core::Atom(0), 1));
    ASSERT_NO_THROW(testSet.Insert(NovelRT::Core::Atom(1), 1));
    ASSERT_NO_THROW(testSet.Remove(NovelRT::Core::Atom(0)));
    EXPECT_EQ(testSet[NovelRT::Core::Atom(1)], 1);
}

TEST(SparseSetTest, CanIterateAndModifyDenseData)
{
    SparseSet<NovelRT::Core::Atom, int32_t> testSet;
    ASSERT_NO_THROW(testSet.Insert(NovelRT::Core::Atom(0), 1));
    ASSERT_NO_THROW(testSet.Insert(NovelRT::Core::Atom(1), 1));
    ASSERT_NO_THROW(testSet.Insert(NovelRT::Core::Atom(2), 1));
    ASSERT_NO_THROW(testSet.Insert(NovelRT::Core::Atom(3), 1));

    for (auto [i, j] : testSet)
    {
        j = 10;
    }

    for (auto&& [i, j] : testSet)
    {
        EXPECT_EQ(j, 10);
    }
}

TEST(SparseSetTest, CanUseStruct)
{
    struct MyAwesomeStruct
    {
        int32_t fieldOne = 1;
        void* fieldTwo = nullptr;
        bool fieldThree = false;
        Maths::GeoVector3F fieldFour = Maths::GeoVector3F::One();
    };

    SparseSet<EntityId, MyAwesomeStruct> testSet{};
    testSet.Insert(0, MyAwesomeStruct{});
    EXPECT_EQ(testSet[0].fieldOne, 1);
    EXPECT_EQ(testSet[0].fieldFour, Maths::GeoVector3F::One());

    for (auto [entity, component] : testSet)
    {
        EXPECT_EQ(component.fieldOne, 1);
        EXPECT_EQ(component.fieldFour, Maths::GeoVector3F::One());
    }
}
