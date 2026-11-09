// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/SparseSetMemoryContainer.hpp>
#include <NovelRT/Exceptions/DuplicateKeyException.hpp>
#include <NovelRT/Exceptions/InvalidOperationException.hpp>
#include <NovelRT/Exceptions/KeyNotFoundException.hpp>
#include <gtest/gtest.h>
#include <limits>

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

TEST(SparseSetMemoryContainerTest, InsertAndLookupPreserveValuesAcrossPageBoundaries)
{
    SparseSetMemoryContainer container(sizeof(int32_t));
    constexpr size_t entryCount = 700000;

    for (size_t key = 0; key < entryCount; ++key)
    {
        auto value = static_cast<int32_t>(key);
        container.Insert(key, &value);
    }

    ASSERT_EQ(container.Length(), entryCount);

    const SparseSetMemoryContainer& constContainer = container;

    for (size_t key = 0; key < entryCount; ++key)
    {
        ASSERT_TRUE(container.ContainsKey(key)) << "Key: " << key;
        ASSERT_EQ(container.GetDenseIndex(key), key) << "Key: " << key;

        int32_t mutableResult = -1;
        int32_t constResult = -1;

        container[key].CopyFromLocation(&mutableResult);
        constContainer[key].CopyFromLocation(&constResult);

        ASSERT_EQ(mutableResult, static_cast<int32_t>(key)) << "Key: " << key;
        ASSERT_EQ(constResult, static_cast<int32_t>(key)) << "Key: " << key;
    }
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

    ASSERT_EQ(container.TryInsert(0, &testValue), SparseSetInsertResult::Inserted);

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

    ASSERT_EQ(container.TryInsert(0, &testValueOne), SparseSetInsertResult::Inserted);
    ASSERT_EQ(container.TryInsert(1, &testValueTwo), SparseSetInsertResult::Inserted);
    ASSERT_EQ(container.TryInsert(2, &testValueThree), SparseSetInsertResult::Inserted);

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

TEST(SparseSetMemoryContainerTest, TryInsertReturnsAlreadyExistsWhenDuplicateKeyEntered)
{
    SparseSetMemoryContainer container(sizeof(int32_t));
    int32_t testValue = 10;

    ASSERT_EQ(container.TryInsert(0, &testValue), SparseSetInsertResult::Inserted);

    testValue = 20;

    EXPECT_EQ(container.TryInsert(0, &testValue), SparseSetInsertResult::AlreadyExists);

    EXPECT_EQ(container.Length(), 1);
    EXPECT_EQ(*static_cast<const int32_t*>(container[0].GetDataHandle()), 10);
}

TEST(SparseSetMemoryContainerTest, TryInsertSupportsMaximumKeyAndPreservesExistingEntries)
{
    SparseSetMemoryContainer container(sizeof(int32_t));
    int32_t value = 10;

    ASSERT_EQ(container.TryInsert(0, &value), SparseSetInsertResult::Inserted);

    constexpr size_t maximumKey = std::numeric_limits<size_t>::max();
    static_assert(noexcept(container.TryInsert(maximumKey, &value)));

    EXPECT_EQ(container.TryInsert(maximumKey, &value), SparseSetInsertResult::Inserted);

    ASSERT_EQ(container.Length(), 2);
    ASSERT_TRUE(container.ContainsKey(0));
    ASSERT_TRUE(container.ContainsKey(maximumKey));
    EXPECT_EQ(*static_cast<const int32_t*>(container[0].GetDataHandle()), 10);
    EXPECT_EQ(*static_cast<const int32_t*>(container[maximumKey].GetDataHandle()), 10);

    EXPECT_EQ(container.TryInsert(1, &value), SparseSetInsertResult::Inserted);
}

TEST(SparseSetMemoryContainerTest, ResetAndRemovePreserveMappingsAcrossPageBoundaries)
{
    SparseSetMemoryContainer container(sizeof(int32_t));
    const size_t ids[] = {0, 1, 1023, 1024, 1025, std::numeric_limits<size_t>::max()};
    const int32_t values[] = {10, 20, 30, 40, 50, 60};
    int32_t oldValue = -1;

    container.Insert(2048, &oldValue);
    container.ResetAndWriteDenseData(ids, 6, reinterpret_cast<const std::byte*>(values));

    ASSERT_EQ(container.Length(), 6);
    EXPECT_FALSE(container.ContainsKey(2048));
    EXPECT_FALSE(container.ContainsKey(2));

    for (size_t i = 0; i < 6; ++i)
    {
        ASSERT_TRUE(container.ContainsKey(ids[i]));
        EXPECT_EQ(container.GetDenseIndex(ids[i]), i);
        EXPECT_EQ(*static_cast<const int32_t*>(container[ids[i]].GetDataHandle()), values[i]);
    }

    container.Remove(0);
    container.Remove(1024);
    container.Remove(std::numeric_limits<size_t>::max());

    const size_t remainingIds[] = {1, 1023, 1025};
    const int32_t remainingValues[] = {20, 30, 50};

    ASSERT_EQ(container.Length(), 3);
    EXPECT_FALSE(container.ContainsKey(0));
    EXPECT_FALSE(container.ContainsKey(1024));
    EXPECT_FALSE(container.ContainsKey(std::numeric_limits<size_t>::max()));

    size_t denseIndex = 0;

    for (auto [id, dataView] : container)
    {
        ASSERT_LT(denseIndex, size_t{3});
        EXPECT_EQ(id, remainingIds[denseIndex]);
        EXPECT_EQ(container.GetDenseIndex(id), denseIndex);
        EXPECT_EQ(*static_cast<const int32_t*>(dataView.GetDataHandle()), remainingValues[denseIndex]);
        ++denseIndex;
    }

    EXPECT_EQ(denseIndex, 3);

    container.Insert(0, &values[0]);
    container.Insert(std::numeric_limits<size_t>::max(), &values[5]);

    EXPECT_EQ(*static_cast<const int32_t*>(container[0].GetDataHandle()), 10);
    EXPECT_EQ(*static_cast<const int32_t*>(container[std::numeric_limits<size_t>::max()].GetDataHandle()), 60);
}

TEST(SparseSetMemoryContainerTest, TryInsertRejectsOversizedPayloadWithoutAddingEntry)
{
    SparseSetMemoryContainer container(std::numeric_limits<size_t>::max());
    std::byte value{};

    EXPECT_EQ(container.TryInsert(0, &value), SparseSetInsertResult::UnknownFailure);

    EXPECT_EQ(container.Length(), 0);
    EXPECT_FALSE(container.ContainsKey(0));
}

TEST(SparseSetMemoryContainerTest, CopyValidationFailurePreservesEntriesForBothInsertionApis)
{
    for (bool useTryInsert : {false, true})
    {
        SCOPED_TRACE(useTryInsert);

        SparseSetMemoryContainer container(sizeof(int32_t));
        int32_t value = 10;

        for (size_t key = 0; key < 3; ++key)
        {
            container.Insert(key, &value);
        }

        // Deliberately anger our memcopy failsafes. We don't support overlapped memory copies. It's crazy.
        const auto* overlappingSource = static_cast<const std::byte*>(container[2].GetDataHandle()) + 1;

        if (useTryInsert)
        {
            EXPECT_EQ(container.TryInsert(3, overlappingSource), SparseSetInsertResult::CopyValidationFailed);
        }
        else
        {
            EXPECT_THROW(container.Insert(3, overlappingSource), Exceptions::InvalidOperationException);
        }

        ASSERT_EQ(container.Length(), 3);
        EXPECT_FALSE(container.ContainsKey(3));

        for (size_t key = 0; key < 3; ++key)
        {
            ASSERT_TRUE(container.ContainsKey(key));
            EXPECT_EQ(*static_cast<const int32_t*>(container[key].GetDataHandle()), value);
        }

        EXPECT_EQ(container.TryInsert(3, &value), SparseSetInsertResult::Inserted);
    }
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

TEST(SparseSetMemoryContainerTest, RemoveThrowsKeyNotFoundExceptionWhenDuplicateKeyRemoved)
{
    SparseSetMemoryContainer container(sizeof(int32_t));
    int32_t testValue = 10;

    container.Insert(0, &testValue);
    container.Remove(0);

    EXPECT_THROW(container.Remove(0), Exceptions::KeyNotFoundException);
}

TEST(SparseSetMemoryContainerTest, TryRemoveRemovesTheKeyCorrectly)
{
    SparseSetMemoryContainer container(sizeof(int32_t));
    int32_t testValue = 10;

    container.Insert(0, &testValue);

    ASSERT_TRUE(container.TryRemove(0));
    EXPECT_FALSE(container.ContainsKey(0));
}

TEST(SparseSetMemoryContainerTest, TryRemoveRemovesTheKeyCorrectlyWhenMultipleValuesExist)
{
    SparseSetMemoryContainer container(sizeof(int32_t));
    int32_t testValue = 10;

    container.Insert(0, &testValue);
    container.Insert(1, &testValue);
    container.Insert(2, &testValue);

    ASSERT_TRUE(container.TryRemove(1));

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

TEST(SparseSetMemoryContainerTest, TryRemoveReturnsFalseWhenDuplicateKeyRemoved)
{
    SparseSetMemoryContainer container(sizeof(int32_t));
    int32_t testValue = 10;

    container.Insert(0, &testValue);

    ASSERT_TRUE(container.TryRemove(0));
    EXPECT_FALSE(container.TryRemove(0));
}

TEST(SparseSetMemoryContainerTest, ClearRemovesAllEntries)
{
    SparseSetMemoryContainer container(sizeof(int32_t));
    int32_t testValue = 10;

    container.Insert(0, &testValue);
    container.Clear();

    EXPECT_EQ(container.Length(), 0);
}

TEST(SparseSetMemoryContainerTest, CopyKeyBasedOnDenseIndexReturnsCorrectKey)
{
    SparseSetMemoryContainer container(sizeof(int32_t));
    int32_t testValue = 10;

    container.Insert(3, &testValue);

    EXPECT_EQ(container.CopyKeyBasedOnDenseIndex(0), 3);
}

TEST(SparseSetMemoryContainerTest, CopyKeyBasedOnDenseIndexThrowsOutOfRangeWhenKeyDoesNotExist)
{
    SparseSetMemoryContainer container(sizeof(int32_t));

    EXPECT_THROW((void)container.CopyKeyBasedOnDenseIndex(0), std::out_of_range);
}

TEST(SparseSetMemoryContainerTest, CopyKeyBasedOnDenseIndexUnsafeReturnsCorrectKey)
{
    SparseSetMemoryContainer container(sizeof(int32_t));
    int32_t testValue = 10;

    container.Insert(3, &testValue);

    EXPECT_EQ(container.CopyKeyBasedOnDenseIndexUnsafe(0), 3);
}

TEST(SparseSetMemoryContainerTest, LengthReturnsCorrectValue)
{
    SparseSetMemoryContainer container(sizeof(int32_t));
    int32_t testValue = 10;

    container.Insert(0, &testValue);
    container.Insert(1, &testValue);
    container.Insert(2, &testValue);

    ASSERT_EQ(container.Length(), 3);
}

TEST(SparseSetMemoryContainerTest, IndexingOperatorReturnsCorrectMutableByteIteratorView)
{
    SparseSetMemoryContainer container(sizeof(int32_t));

    int32_t testValueOne = 10;
    int32_t testValueTwo = 20;
    int32_t testValueThree = 30;

    container.Insert(0, &testValueOne);
    container.Insert(1, &testValueTwo);
    container.Insert(2, &testValueThree);

    int32_t result = 0;

    container[1].CopyFromLocation(&result);

    EXPECT_EQ(result, testValueTwo);
}

TEST(SparseSetMemoryContainerTest, IndexingOperatorReturnsCorrectConstByteIteratorView)
{
    SparseSetMemoryContainer container(sizeof(int32_t));

    int32_t testValueOne = 10;
    int32_t testValueTwo = 20;
    int32_t testValueThree = 30;

    container.Insert(0, &testValueOne);
    container.Insert(1, &testValueTwo);
    container.Insert(2, &testValueThree);

    int32_t result = 0;
    auto view = static_cast<const SparseSetMemoryContainer&>(container)[1];

    view.CopyFromLocation(&result);

    EXPECT_EQ(result, testValueTwo);
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

    for (auto [id, dataView] : container)
    {
        int32_t value = 0;
        dataView.CopyFromLocation(&value);

        EXPECT_EQ(10, value);
    }

    for (auto [id, dataView] : static_cast<const SparseSetMemoryContainer&>(container))
    {
        int32_t value = 0;
        dataView.CopyFromLocation(&value);

        EXPECT_EQ(10, value);
    }
}
