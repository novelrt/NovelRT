//
// Created by matth on 23/02/2019.
//

#ifndef NOVELRT_NOVELLAYERINGSERVICE_H
#define NOVELRT_NOVELLAYERINGSERVICE_H

namespace NovelRT {
class NovelObject;
class NovelLayeringService {
public:
  void updateLayerInfo(const int layer, NovelObject* targetObject, const bool migrate = true);
  void sortLayerOrder(const int layer);
  void executeAllObjectBehaviours();
private:
  std::map<int, std::vector<std::unique_ptr<NovelObject>>> _layerMatrix;
};
}
#endif //NOVELRT_NOVELLAYERINGSERVICE_H
