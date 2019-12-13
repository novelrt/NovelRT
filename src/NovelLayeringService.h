// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_NOVELLAYERINGSERVICE_H
#define NOVELRT_NOVELLAYERINGSERVICE_H

#include <map>
#include <vector>
#include <string_view>
#include "NovelObject.h"

namespace NovelRT {
  class NovelObject;
  class NovelLayeringService {

  private:
    std::map<int, std::vector<NovelObject*>> _layerMatrix;

  public:
    ~NovelLayeringService();

    void updateLayerInfo(int layer, NovelObject* targetObject, bool migrate = true);
    void sortLayerOrder(int layer);
    void executeAllObjectBehaviours();
  };
}
#endif //NOVELRT_NOVELLAYERINGSERVICE_H
