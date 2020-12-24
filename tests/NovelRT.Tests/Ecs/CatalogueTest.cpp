// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#include <gtest/gtest.h>
#include <NovelRT.h>
#include <atomic>

using namespace NovelRT;
using namespace NovelRT::Ecs;

class CatalogueTest : public testing::Test
{
    private:
    ComponentCache _cache = ComponentCache(8);
    EntityCache _entityCache = EntityCache(8);

    protected:
    void SetUp() override
    {
        Catalogue catalogue(2, _cache, _entityCache);
        auto [theInt, theSizeT, theBool] = catalogue.GetComponentViews<int, size_t, bool>();

        for (auto&& [entity, component] : theInt)
        {
            std::cout << "meme" << std::endl;
        }
        
    }
};