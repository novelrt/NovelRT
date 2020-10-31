// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include "../NovelRTInteropErrorHandlingInternal.h"
#include <stddef.h>
#include "NovelRT.Interop/NovelRTInteropUtils.h"
#include "NovelRT.Interop/Animation/NovelRTSpriteAnimatorFrame.h"
#include "NovelRT.Interop/Animation/NovelRTSpriteAnimatorState.h"
#include <NovelRT.h>

#ifdef __cplusplus
using namespace NovelRT;
extern "C" {
#endif
/*
typedef struct BoolFunctionVectorHandle* NovelRTSpriteAnimatorStateConditionFunctions;
typedef struct BoolFunctionHandle* NovelRTSpriteAnimatorStateBooleanFunction;   //Not known if this is needed yet.
typedef struct SpriteAnimatorFrameVectorHandle* NovelRTSpriteAnimatorFrameVector;
*/

NovelRTSpriteAnimatorState NovelRT_SpriteAnimatorState_create() {
    Animation::SpriteAnimatorState* state = new Animation::SpriteAnimatorState();
    return reinterpret_cast<NovelRTSpriteAnimatorState>(state);    
}

int32_t NovelRT_SpriteAnimatorState_insertNewState(NovelRTSpriteAnimatorState state, NovelRTSpriteAnimatorState stateTarget, NovelRTSpriteAnimatorStateConditionFunctions vector) {
    if (state == nullptr || stateTarget == nullptr || vector == nullptr) {
        NovelRT_setErrMsgIsNullptrInternal();
        return NOVELRT_FAILURE;
    }

    Animation::SpriteAnimatorState* cppState = reinterpret_cast<Animation::SpriteAnimatorState*>(state);
    std::shared_ptr<Animation::SpriteAnimatorState> cppStateTarget = std::shared_ptr<Animation::SpriteAnimatorState>(reinterpret_cast<Animation::SpriteAnimatorState*>(stateTarget));
    std::vector<std::function<bool()>> conditions = *reinterpret_cast<std::vector<std::function<bool()>>*>(vector);
    
    cppState->insertNewState(cppStateTarget, conditions);
    return NOVELRT_SUCCESS;
}

int32_t NovelRT_SpriteAnimatorState_removeStateAtIndex(NovelRTSpriteAnimatorState state, size_t index) {
    if (state == nullptr) {
        NovelRT_setErrMsgIsNullptrInternal();
        return NOVELRT_FAILURE;
    }

    Animation::SpriteAnimatorState* cppState = reinterpret_cast<Animation::SpriteAnimatorState*>(state);
    
    cppState->removeStateAtIndex(index);
    
    return NOVELRT_SUCCESS;
}

int32_t NovelRT_SpriteAnimatorState_getShouldLoop(NovelRTSpriteAnimatorState state, int32_t* outputLoop) {
    if (state == nullptr || outputLoop == nullptr) {
        NovelRT_setErrMsgIsNullptrInternal();
        return NOVELRT_FAILURE;
    }

    Animation::SpriteAnimatorState* cppState = reinterpret_cast<Animation::SpriteAnimatorState*>(state);
    
    *outputLoop = static_cast<int32_t>(cppState->shouldLoop());
    
    return NOVELRT_SUCCESS;
}

int32_t NovelRT_SpriteAnimatorState_setShouldLoop(NovelRTSpriteAnimatorState state, int32_t loop) {
    if (state == nullptr) {
        NovelRT_setErrMsgIsNullptrInternal();
        return NOVELRT_FAILURE;
    }

    Animation::SpriteAnimatorState* cppState = reinterpret_cast<Animation::SpriteAnimatorState*>(state);
    
    cppState->shouldLoop() = static_cast<bool>(loop);
    
    return NOVELRT_SUCCESS;
}

int32_t NovelRT_SpriteAnimatorState_getFrames(NovelRTSpriteAnimatorState state, NovelRTSpriteAnimatorFrameVector* outputFrames) {
    if (state == nullptr || outputFrames == nullptr) {
        NovelRT_setErrMsgIsNullptrInternal();
        return NOVELRT_FAILURE;
    }

    Animation::SpriteAnimatorState* cppState = reinterpret_cast<Animation::SpriteAnimatorState*>(state);
    std::vector<Animation::SpriteAnimatorFrame>* frames = new std::vector<Animation::SpriteAnimatorFrame>();
    *frames = cppState->frames();

    *outputFrames = reinterpret_cast<NovelRTSpriteAnimatorFrameVector>(&frames);
    return NOVELRT_SUCCESS;
}

int32_t NovelRT_SpriteAnimatorState_setFrames(NovelRTSpriteAnimatorState state, NovelRTSpriteAnimatorFrameVector frames) {
    if (state == nullptr || frames == nullptr) {
        NovelRT_setErrMsgIsNullptrInternal();
        return NOVELRT_FAILURE;
    }

    Animation::SpriteAnimatorState* cppState = reinterpret_cast<Animation::SpriteAnimatorState*>(state);
    std::vector<Animation::SpriteAnimatorFrame>* cppFrames = reinterpret_cast<std::vector<Animation::SpriteAnimatorFrame>*>(frames);//new std::vector<Animation::SpriteAnimatorFrame>();
    cppState->frames() = *cppFrames;
    return NOVELRT_SUCCESS;
}

int32_t NovelRT_SpriteAnimatorState_tryFindValidTransition(NovelRTSpriteAnimatorState state, NovelRTSpriteAnimatorState* outputTransitionState) {
    if (state == nullptr || outputTransitionState == nullptr) {
        NovelRT_setErrMsgIsNullptrInternal();
        return NOVELRT_FAILURE;
    }

    Animation::SpriteAnimatorState* cppState = reinterpret_cast<Animation::SpriteAnimatorState*>(state);
    
    try {
        *outputTransitionState = reinterpret_cast<NovelRTSpriteAnimatorState>(cppState->tryFindValidTransition().get());
    }
    catch (const std::exception& ex) {
        const char* message = ex.what();
        char* target = new char[strlen(message) + 1];
        strcpy(target, message);
        NovelRT_setErrMsgCustomInternal(target);
        return NOVELRT_FAILURE;
    }
    
    return NOVELRT_SUCCESS;    
}

NovelRTSpriteAnimatorFrameVector NovelRT_SpriteAnimatorFrameVector_create() {
    std::vector<Animation::SpriteAnimatorFrame>* vector = new std::vector<Animation::SpriteAnimatorFrame>();
    return reinterpret_cast<NovelRTSpriteAnimatorFrameVector>(vector);
}

int32_t NovelRT_SpriteAnimatorFrameVector_addFrame(NovelRTSpriteAnimatorFrameVector vector, NovelRTSpriteAnimatorFrame frame) {
    if (vector == nullptr || frame == nullptr) {
        NovelRT_setErrMsgIsNullptrInternal();
        return NOVELRT_FAILURE;
    }

    std::vector<Animation::SpriteAnimatorFrame> cppVector = *reinterpret_cast<std::vector<Animation::SpriteAnimatorFrame>*>(vector);
    Animation::SpriteAnimatorFrame cppFrame = *reinterpret_cast<Animation::SpriteAnimatorFrame*>(frame);
    cppVector.push_back(cppFrame);
    return NOVELRT_SUCCESS;
}

int32_t NovelRT_SpriteAnimatorFrameVector_getFrameAtIndex(NovelRTSpriteAnimatorFrameVector vector, int32_t index, NovelRTSpriteAnimatorFrame* outputFrame) {
    if (vector == nullptr || outputFrame == nullptr) {
        NovelRT_setErrMsgIsNullptrInternal();
        return NOVELRT_FAILURE;
    }

    std::vector<Animation::SpriteAnimatorFrame> cppVector = *reinterpret_cast<std::vector<Animation::SpriteAnimatorFrame>*>(vector);
    Animation::SpriteAnimatorFrame* cppFrame = new Animation::SpriteAnimatorFrame();
    *cppFrame = cppVector.at(index);
    return NOVELRT_SUCCESS;
}

int32_t NovelRT_SpriteAnimatorFrameVector_removeFrameAtIndex(NovelRTSpriteAnimatorFrameVector vector, int32_t index) {
    if (vector == nullptr) {
        NovelRT_setErrMsgIsNullptrInternal();
        return NOVELRT_FAILURE;
    }

    std::vector<Animation::SpriteAnimatorFrame> cppVector = *reinterpret_cast<std::vector<Animation::SpriteAnimatorFrame>*>(vector);
    cppVector.erase(cppVector.begin() + index);
    return NOVELRT_SUCCESS;
}

int32_t NovelRT_SpriteAnimatorFrameVector_delete(NovelRTSpriteAnimatorFrameVector vector) {
    if (vector == nullptr) {
        NovelRT_setErrMsgIsNullptrInternal();
        return NOVELRT_FAILURE;
    }

    std::vector<Animation::SpriteAnimatorFrame>* cppVector = reinterpret_cast<std::vector<Animation::SpriteAnimatorFrame>*>(vector);
    cppVector->clear();
    delete cppVector;
    return NOVELRT_SUCCESS;
}

#ifdef __cplusplus
}
#endif
