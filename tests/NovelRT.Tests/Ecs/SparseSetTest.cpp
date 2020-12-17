// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#include <gtest/gtest.h>
#include <NovelRT.h>
#include <atomic>

using namespace NovelRT;
using namespace NovelRT::Ecs;

TEST(SparseSetTest, InsertDoesNotThrowWhenAddingValidItemToCollection)
{
    SparseSet<Atom, int32_t, AtomHashFunction> testSet;
    EXPECT_NO_THROW(testSet.Insert(Atom(0), 1));
}

TEST(SparseSetTest, InsertThrowsWhenDuplicateKeyIsAddedToCollection)
{
    SparseSet<Atom, int32_t, AtomHashFunction> testSet;
    ASSERT_NO_THROW(testSet.Insert(Atom(0), 1));
    EXPECT_THROW(testSet.Insert(Atom(0), 1), std::exception);
}

TEST(SparseSetTest, RemoveDoesNotThrowWhenRemovingValidItemFromCollection)
{
    SparseSet<Atom, int32_t, AtomHashFunction> testSet;
    ASSERT_NO_THROW(testSet.Insert(Atom(0), 1));
    EXPECT_NO_THROW(testSet.Remove(Atom(0)));
}

TEST(SparseSetTest, RemoveDoesThrowWhenRemovingNonexistentKeyFromCollection)
{
    SparseSet<Atom, int32_t, AtomHashFunction> testSet;
    ASSERT_NO_THROW(testSet.Insert(Atom(0), 1));
    ASSERT_NO_THROW(testSet.Remove(Atom(0)));
    EXPECT_THROW(testSet.Remove(Atom(0)), std::exception);
}

TEST(SparseSetTest, InsertInsertsValidItemCorrectly)
{
    SparseSet<Atom, int32_t, AtomHashFunction> testSet;
    ASSERT_NO_THROW(testSet.Insert(Atom(0), 1));
    EXPECT_EQ(testSet[Atom(0)], 1);
}

TEST(SparseSetTest, RemoveUpdatesSetCorrectlyAfterRemovingElement)
{
    SparseSet<Atom, int32_t, AtomHashFunction> testSet;
    ASSERT_NO_THROW(testSet.Insert(Atom(0), 1));
    ASSERT_NO_THROW(testSet.Insert(Atom(1), 1));
    ASSERT_NO_THROW(testSet.Remove(Atom(0)));
    EXPECT_EQ(testSet[Atom(1)], 1);
}

TEST(SparseSetTest, CanIterateAndModifyDenseData)
{
    SparseSet<Atom, int32_t, AtomHashFunction> testSet;
    ASSERT_NO_THROW(testSet.Insert(Atom(0), 1));
    ASSERT_NO_THROW(testSet.Insert(Atom(1), 1));
    ASSERT_NO_THROW(testSet.Insert(Atom(2), 1));
    ASSERT_NO_THROW(testSet.Insert(Atom(3), 1));

    for (auto&& [i, j] : testSet)
    {
        j = 10;
    }
    
    for (auto&& [i, j] : testSet)
    {
        EXPECT_EQ(j, 10);
    }
}

//TEST(SparseSetTest, ReturnsSparseSetViewWithCorrectData)
//{
//    SparseSet<Atom, int32_t, AtomHashFunction> testSet;
//    ASSERT_NO_THROW(testSet.Insert(Atom(0), 1));
//    ASSERT_NO_THROW(testSet.Insert(Atom(1), 1));
//    ASSERT_NO_THROW(testSet.Insert(Atom(2), 1));
//    ASSERT_NO_THROW(testSet.Insert(Atom(3), 1));
//
//    auto view = testSet.GetImmutableView();
//
//    for (auto&& [i, j] : view)
//    {
//        EXPECT_EQ(j, 1);
//    }
//}

