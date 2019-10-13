// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See License.md in the repository root for more information.

#ifndef NOVELRT_NOVELLAYERINGSERVICE_H
#define NOVELRT_NOVELLAYERINGSERVICE_H

#include <map>
#include <vector>
#include <string_view>
#include "NovelWorldObject.h"

namespace NovelRT {
class NovelWorldObject;
class NovelLayeringService {
public:
  void updateLayerInfo(int layer, NovelWorldObject* targetObject, bool migrate = true);
  void sortLayerOrder(int layer);
  void executeAllObjectBehaviours();

  ~NovelLayeringService();
private:
  std::map<int, std::vector<NovelWorldObject*>> _layerMatrix;
};
}
#endif //NOVELRT_NOVELLAYERINGSERVICE_H
