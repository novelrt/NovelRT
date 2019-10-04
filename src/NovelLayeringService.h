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
public:
  void updateLayerInfo(const int layer, NovelObject* targetObject, const bool migrate = true);
  void sortLayerOrder(const int layer);
  void executeAllObjectBehaviours();

  ~NovelLayeringService();
private:
  std::map<int, std::vector<NovelObject*>> _layerMatrix;
};
}
#endif //NOVELRT_NOVELLAYERINGSERVICE_H
