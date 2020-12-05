
// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#include <gtest/gtest.h>
#include <NovelRT.h>
#include <atomic>

using namespace NovelRT;
using namespace NovelRT::Ecs;

class SparseSetViewTest : public testing::Test
{
    public:
    std::unique_ptr<SparseSetView<Atom, int32_t, AtomHashFunction>> testView = nullptr;
    std::shared_ptr<std::vector<int32_t>> testVector;
    std::shared_ptr<std::unordered_map<Atom, size_t, AtomHashFunction>> testMap;

    protected:
    void SetUp() override
    {
        testVector = std::make_shared<std::vector<int32_t>>();
        testVector->emplace_back(1);
        testVector->emplace_back(1);
        testVector->emplace_back(1);

        testMap = std::make_shared<std::unordered_map<Atom, size_t, AtomHashFunction>>();
        testMap->emplace(Atom(0), 0);
        testMap->emplace(Atom(1), 1);
        testMap->emplace(Atom(2), 2);
        auto vecWeakPtr = std::weak_ptr<const std::vector<int32_t>>(testVector);
        auto mapWeakPtr = std::weak_ptr<const std::unordered_map<Atom, size_t, AtomHashFunction>>(testMap);

        testView = std::make_unique<SparseSetView<Atom, int32_t, AtomHashFunction>>(vecWeakPtr, mapWeakPtr);
    }
};

TEST_F(SparseSetViewTest, CanIterateCorrectly)
{
    for (auto &&i : *testView)
    {
        EXPECT_EQ(i, 1);
    }
}

TEST_F(SparseSetViewTest, CanReturnByIndex)
{
    EXPECT_EQ((*testView)[Atom(0)], 1);
}

TEST_F(SparseSetViewTest, ViewReflectsChangesInUnderlyingSet)
{
    testVector->at(0) = 5;
    EXPECT_EQ((*testView)[Atom(0)], 5);
}