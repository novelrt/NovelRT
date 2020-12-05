
// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#include <gtest/gtest.h>
#include <NovelRT.h>
#include <atomic>

using namespace NovelRT;
using namespace NovelRT::Ecs;

TEST(SparseSetViewTest, CanIterateCorrectly)
{
    
    auto vec = std::vector<int32_t>{1, 1, 1};
    auto map = std::unordered_map<Atom, size_t, AtomHashFunction>{{Atom(0), 0}, {Atom(1), 1}, {Atom(2), 2}};
    auto testView = SparseSetView<Atom, int32_t, AtomHashFunction>(&vec, &map);

    for (auto &&i : testView)
    {
        EXPECT_EQ(i, 1);
    }
}

TEST(SparseViewTest, CanReturnByIndex)
{
    auto vec = std::vector<int32_t>{1, 1, 1};
    auto map = std::unordered_map<Atom, size_t, AtomHashFunction>{{Atom(0), 0}, {Atom(1), 1}, {Atom(2), 2}};
    auto testView = SparseSetView<Atom, int32_t, AtomHashFunction>(&vec, &map);
    EXPECT_EQ(testView[Atom(0)], 1);
}