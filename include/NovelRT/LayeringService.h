// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_NOVELLAYERINGSERVICE_H
#define NOVELRT_NOVELLAYERINGSERVICE_H

#include <map>
#include <vector>
#include <string_view>

namespace NovelRT {
  class Transform;
  class LayeringService {
  private:
    std::map<int, std::vector<Transform*>> _layerMatrix;

  public:
    void updateLayerInfo(int layer, Transform* targetObject, bool migrate = true);
    void sortLayerOrder(int layer);
    void executeAllObjectBehaviours();

    ~LayeringService();
  };
}
#endif //NOVELRT_NOVELLAYERINGSERVICE_H
