// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/Ecs/NrtDefaultComponentTypes.h>
#include <NovelRT/Ecs/Ecs.h>

#ifdef __cplusplus
extern "C"
{
#endif

    // struct TransformComponent

    NrtBool Nrt_TransformComponent_PlusEquals_Operator(NrtTransformComponent* lhs, NrtTransformComponent rhs);

    // struct EntityGraphComponent

    NrtBool Nrt_EntityGraphComponent_PlusEquals_Operator(NrtEntityGraphComponent* lhs, NrtEntityGraphComponent rhs);
    NrtBool Nrt_EntityGraphComponent_Equals_Operator(NrtEntityGraphComponent lhs, NrtEntityGraphComponent rhs);
    NrtBool Nrt_EntityGraphComponent_NotEquals_Operator(NrtEntityGraphComponent lhs, NrtEntityGraphComponent rhs);

    // struct LinkedEntityListNodeComponent

    NrtBool Nrt_LinkedEntityListNodeComponent_PlusEquals_Operator(NrtLinkedEntityListNodeComponent* lhs, NrtLinkedEntityListNodeComponent rhs);
    NrtBool Nrt_LinkedEntityListNodeComponent_Equals_Operator(NrtLinkedEntityListNodeComponent lhs, NrtLinkedEntityListNodeComponent rhs);
    NrtBool Nrt_LinkedEntityListNodeComponent_NotEquals_Operator(NrtLinkedEntityListNodeComponent lhs, NrtLinkedEntityListNodeComponent rhs);

#ifdef __cplusplus
}
#endif
