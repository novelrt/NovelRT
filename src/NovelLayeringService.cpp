// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <algorithm>
#include <NovelRT.h>

namespace NovelRT {
void LayeringService::updateLayerInfo(int layer, Transform* targetObject, bool migrate) {
  if (migrate) {
    auto vec = _layerMatrix[targetObject->getLayer()];
    vec.erase(std::remove_if(vec.begin(), vec.end(), [targetObject](const Transform* x) {
      auto result = x == targetObject;
      return result;
    }), vec.end());
  }
  auto it = _layerMatrix.find(layer);
  if (it == _layerMatrix.end()) {
    _layerMatrix.insert({layer, std::vector<Transform*>()});
  }
  _layerMatrix[layer].push_back(targetObject);
  sortLayerOrder(layer);
}

void LayeringService::sortLayerOrder(int layer) {
  std::sort(_layerMatrix[layer].begin(), _layerMatrix[layer].end(), TransformSortComparison());
}

void LayeringService::executeAllObjectBehaviours() {

  for (const auto& value : _layerMatrix) {
    for (const auto& renderObj : value.second) {
      renderObj->executeObjectBehaviour();
    }
  }
}
LayeringService::~LayeringService() {
  for (const auto& value : _layerMatrix) {
    for (const auto& renderObj : value.second) {
      delete renderObj;
    }
  }
}
}
