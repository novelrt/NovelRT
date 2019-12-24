// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include <NovelRT.h>

namespace NovelRT {
  Transform::Transform(const Utilities::CommonArgs& args) {
    setPosition(args.startingPosition);
    setRotation(args.startingRotation);
    setScale(args.startingScale);
  }
}
