// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_INPUT_BASICINTERACTIONRECT_H
#define NOVELRT_INPUT_BASICINTERACTIONRECT_H

namespace NovelRT::Input {

  class BasicInteractionRect : public InteractionObject {
  public:
    BasicInteractionRect(const Transform& transform, const std::function<void(InteractionObject*)> notifyHasBeenDrawnObject);

    bool validateInteractionPerimeter(const Maths::GeoVector<float>& mousePosition) const override;
  };
}
#endif //NOVELRT_INPUT_BASICINTERACTIONRECT_H
