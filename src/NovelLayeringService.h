//
// Created by matth on 23/02/2019.
//

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
  void deleteFromMatrix(const NovelObject* targetObject, bool destroyObject = false);
  ~NovelLayeringService();
private:
  std::map<int, std::vector<NovelObject*>> _layerMatrix;

};
}
#endif //NOVELRT_NOVELLAYERINGSERVICE_H
