// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

module;

#include <stdexcept>
#include <string>

export module NovelRT.Exceptions:DuplicateKeyException;

export namespace NovelRT::Exceptions
{
    class DuplicateKeyException final : public std::runtime_error
    {
    public:
        DuplicateKeyException()
            : std::runtime_error("A duplicate key was added into a collection when duplicate keys are not permitted.")
        {
        }
    };
}
