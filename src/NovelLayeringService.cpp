//
// Created by matth on 23/02/2019.
//

#include <algorithm>
#include "NovelLayeringService.h"
#include "NovelObjectSortComparison.h"


namespace NovelRT {
void NovelLayeringService::updateLayerInfo(const int layer, NovelObject* targetObject, const bool migrate) {
  auto it = _layerMatrix.find(layer);
  if (migrate && it != _layerMatrix.end()) {
    deleteFromMatrix(targetObject);
  }
  if (it == _layerMatrix.end()) {
    _layerMatrix.insert({layer, std::vector<NovelObject*>()});
  }
  _layerMatrix[layer].push_back(targetObject);
  sortLayerOrder(layer);
}

void NovelLayeringService::deleteFromMatrix(const NovelObject* targetObject, bool destroyObject) {
  auto& vec = _layerMatrix.at(targetObject->getLayer());
  vec.erase(std::remove_if(vec.begin(), vec.end(), [targetObject](const NovelObject* x) {
    auto result = x == targetObject;
    return result;
  }), vec.end());

  if(destroyObject) delete targetObject;
}

void NovelLayeringService::sortLayerOrder(const int layer) {
  sort(_layerMatrix.at(layer).begin(), _layerMatrix.at(layer).end(), NovelObjectSortComparison());
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
    for (const auto& targetObj : value.second) {
      delete targetObj;
    }
  }
}
}