// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <algorithm>
#include "../include/NovelLayeringService.h"
#include "../include/NovelObjectSortComparison.h"

namespace NovelRT {
void NovelLayeringService::updateLayerInfo(int layer, NovelWorldObject* targetObject, bool migrate) {
  if (migrate) {
    auto vec = _layerMatrix[targetObject->getLayer()];
    vec.erase(std::remove_if(vec.begin(), vec.end(), [targetObject](const NovelWorldObject* x) {
      auto result = x == targetObject;
      return result;
    }), vec.end());
  }
  auto it = _layerMatrix.find(layer);
  if (it == _layerMatrix.end()) {
    _layerMatrix.insert({layer, std::vector<NovelWorldObject*>()});
  }
  _layerMatrix[layer].push_back(targetObject);
  sortLayerOrder(layer);
}

void NovelLayeringService::sortLayerOrder(int layer) {
  sort(_layerMatrix[layer].begin(), _layerMatrix[layer].end(), NovelWorldObjectSortComparison());
}

void NovelLayeringService::executeAllObjectBehaviours() {

  for (const auto& value : _layerMatrix) {
    for (const auto& renderObj : value.second) {
      renderObj->executeObjectBehaviour();
    }
  }
}
NovelLayeringService::~NovelLayeringService() {
  for (const auto& value : _layerMatrix) {
    for (const auto& renderObj : value.second) {
      delete renderObj;
    }
  }
}
}
