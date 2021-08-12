// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.h>

namespace NovelRT
{
    WorldObject::WorldObject(Transform transform, int32_t layer) noexcept
        : _transform(transform), _layer(layer), _active(true)
    {
    }

    bool WorldObject::getActive() const noexcept
    {
        return _active;
    }

    void WorldObject::setActive(bool value) noexcept
    {
        _active = value;
    }
} // namespace NovelRT
