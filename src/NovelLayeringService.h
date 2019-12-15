// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_NOVELLAYERINGSERVICE_H
#define NOVELRT_NOVELLAYERINGSERVICE_H

#include <map>
#include <vector>
#include <string_view>
#include "NovelWorldObject.h"

namespace NovelRT {
  class NovelWorldObject;
  class NovelLayeringService {
  private:
    std::map<int, std::vector<NovelWorldObject*>> _layerMatrix;

  public:
    void updateLayerInfo(int layer, NovelWorldObject* targetObject, bool migrate = true);
    void sortLayerOrder(int layer);
    void executeAllObjectBehaviours();

    ~NovelLayeringService();
  };
}
#endif //NOVELRT_NOVELLAYERINGSERVICE_H
