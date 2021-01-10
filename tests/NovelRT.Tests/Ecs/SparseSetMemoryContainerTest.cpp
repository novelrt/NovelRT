// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <gtest/gtest.h>
#include <NovelRT.h>
#include <atomic>

using namespace NovelRT;
using namespace NovelRT::Ecs;

TEST(SparseSetMemoryContainerTest, InsertCopiesBytesProperly)
{
    SparseSetMemoryContainer container(sizeof(int32_t));
    int32_t testValue = 10;
    container.Insert(0, &testValue);
    auto dataView = container[0];
    int32_t result = 0;
    dataView.CopyFromLocation(&result);

    EXPECT_EQ(result, testValue);
}

TEST(SparseSetMemoryContainerTest, InsertCopiesBytesProperlyMultipleTimes)
{
    SparseSetMemoryContainer container(sizeof(int32_t));

    int32_t testValueOne = 10;
    int32_t testValueTwo = 20;
    int32_t testValueThree = 30;

    container.Insert(0, &testValueOne);
    container.Insert(1, &testValueTwo);
    container.Insert(2, &testValueThree);

    int32_t resultOne = 0;
    int32_t resultTwo = 0;
    int32_t resultThree = 0;

    container[0].CopyFromLocation(&resultOne);
    container[1].CopyFromLocation(&resultTwo);
    container[2].CopyFromLocation(&resultThree);

    EXPECT_EQ(resultOne, testValueOne);
    EXPECT_EQ(resultTwo, testValueTwo);
    EXPECT_EQ(resultThree, testValueThree);
}

TEST(SparseSetMemoryContainerTest, InsertThrowsWhenDuplicateKeyEntered)
{
    SparseSetMemoryContainer container(sizeof(int32_t));
    int32_t testValue = 10;

    container.Insert(0, &testValue);
    EXPECT_THROW(container.Insert(0, &testValue), Exceptions::DuplicateKeyException);
}

TEST(SparseSetMemoryContainerTest, TryInsertCopiesBytesProperly)
{
    SparseSetMemoryContainer container(sizeof(int32_t));
    int32_t testValue = 10;
    ASSERT_TRUE(container.TryInsert(0, &testValue));
    auto dataView = container[0];
    int32_t result = 0;
    dataView.CopyFromLocation(&result);

    EXPECT_EQ(result, testValue);
}

TEST(SparseSetMemoryContainerTest, TryInsertCopiesBytesProperlyMultipleTimes)
{
    SparseSetMemoryContainer container(sizeof(int32_t));

    int32_t testValueOne = 10;
    int32_t testValueTwo = 20;
    int32_t testValueThree = 30;

    ASSERT_TRUE(container.TryInsert(0, &testValueOne));
    ASSERT_TRUE(container.TryInsert(1, &testValueTwo));
    ASSERT_TRUE(container.TryInsert(2, &testValueThree));

    int32_t resultOne = 0;
    int32_t resultTwo = 0;
    int32_t resultThree = 0;

    container[0].CopyFromLocation(&resultOne);
    container[1].CopyFromLocation(&resultTwo);
    container[2].CopyFromLocation(&resultThree);

    EXPECT_EQ(resultOne, testValueOne);
    EXPECT_EQ(resultTwo, testValueTwo);
    EXPECT_EQ(resultThree, testValueThree);
}

TEST(SparseSetMemoryContainerTest, TryInsertReturnsFalseWhenDuplicateKeyEntered)
{
    SparseSetMemoryContainer container(sizeof(int32_t));
    int32_t testValue = 10;

    container.TryInsert(0, &testValue);
    EXPECT_FALSE(container.TryInsert(0, &testValue));
}

TEST(SparseSetMemoryContainerTest, RemoveRemovesTheKeyCorrectly)
{
    SparseSetMemoryContainer container(sizeof(int32_t));
    int32_t testValue = 10;

    container.Insert(0, &testValue);
    container.Remove(0);
    EXPECT_FALSE(container.ContainsKey(0));
}

TEST(SparseSetMemoryContainerTest, RemoveRemovesTheKeyCorrectlyWhenMultipleValuesExist)
{
    SparseSetMemoryContainer container(sizeof(int32_t));
    int32_t testValue = 10;

    container.Insert(0, &testValue);
    container.Insert(1, &testValue);
    container.Insert(2, &testValue);
    container.Remove(1);
    EXPECT_FALSE(container.ContainsKey(1));
    EXPECT_EQ(container.Length(), 2);

    for (auto [id, dataView] : container)
    {
        ASSERT_TRUE(id == 0 || id == 2);
        int32_t value = 0;
        dataView.CopyFromLocation(&value);
        EXPECT_EQ(value, testValue);
    }
}

TEST(SparseSetMemoryContainerTest, RemoveThrowsKeyNotFoundException)
{
    SparseSetMemoryContainer container(sizeof(int32_t));
    int32_t testValue = 10;

    container.Insert(0, &testValue);
    container.Remove(0);
    EXPECT_THROW(container.Remove(0), Exceptions::KeyNotFoundException);
}

TEST(SparseSetMemoryContainerTest, IteratingTheMutableCollectionReturnsCorrectValues)
{
    SparseSetMemoryContainer container(sizeof(int32_t));

    int32_t testValueOne = 10;
    int32_t testValueTwo = 10;
    int32_t testValueThree = 10;

    container.Insert(0, &testValueOne);
    container.Insert(1, &testValueTwo);
    container.Insert(2, &testValueThree);

    for (auto [id, dataView] : container)
    {
        int32_t value = 0;
        dataView.CopyFromLocation(&value);
        EXPECT_EQ(10, value);
    }
}

TEST(SparseSetMemoryContainerTest, IteratingTheConstCollectionReturnsCorrectValues)
{
    SparseSetMemoryContainer container(sizeof(int32_t));

    int32_t testValueOne = 10;
    int32_t testValueTwo = 10;
    int32_t testValueThree = 10;

    container.Insert(0, &testValueOne);
    container.Insert(1, &testValueTwo);
    container.Insert(2, &testValueThree);

    for (auto it = container.cbegin(); it != container.cend(); it++)
    {
        auto [id, dataView] = *it;
        int32_t value = 0;
        dataView.CopyFromLocation(&value);
        EXPECT_EQ(10, value);
    }
}

