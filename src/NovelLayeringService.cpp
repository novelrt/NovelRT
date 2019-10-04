// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#include <algorithm>
#include "NovelLayeringService.h"
#include "NovelObjectSortComparison.h"

namespace NovelRT {
void NovelLayeringService::updateLayerInfo(const int layer, NovelObject* targetObject, const bool migrate) {
  if (migrate) {
    auto vec = _layerMatrix[targetObject->getLayer()];
    vec.erase(std::remove_if(vec.begin(), vec.end(), [targetObject](const NovelObject* x) {
      auto result = x == targetObject;
      return result;
    }), vec.end());
  }
  auto it = _layerMatrix.find(layer);
  if (it == _layerMatrix.end()) {
    _layerMatrix.insert({layer, std::vector<NovelObject*>()});
  }
  _layerMatrix[layer].push_back(targetObject);
  sortLayerOrder(layer);
}

void NovelLayeringService::sortLayerOrder(const int layer) {
  sort(_layerMatrix[layer].begin(), _layerMatrix[layer].end(), NovelObjectSortComparison());
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