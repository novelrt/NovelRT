// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include "../NrtInteropErrorHandlingInternal.h"
#include <stddef.h>
#include "NovelRT.Interop/NrtInteropUtils.h"
#include "NovelRT.Interop/Animation/NrtSpriteAnimatorFrame.h"
#include "NovelRT.Interop/Animation/NrtSpriteAnimatorState.h"
#include <NovelRT.h>

#ifdef __cplusplus
using namespace NovelRT;
extern "C" {
#endif
/*
typedef struct BoolFunctionVectorHandle* NrtSpriteAnimatorStateConditionFunctions;
typedef struct BoolFunctionHandle* NrtSpriteAnimatorStateBooleanFunction;   //Not known if this is needed yet.
typedef struct SpriteAnimatorFrameVectorHandle* NrtSpriteAnimatorFrameVector;
*/

NrtSpriteAnimatorState Nrt_SpriteAnimatorState_create() {
    Animation::SpriteAnimatorState* state = new Animation::SpriteAnimatorState();
    return reinterpret_cast<NrtSpriteAnimatorState>(state);    
}

int32_t Nrt_SpriteAnimatorState_insertNewState(NrtSpriteAnimatorState state, NrtSpriteAnimatorState stateTarget, NrtSpriteAnimatorStateConditionFunctions vector) {
    if (state == nullptr || stateTarget == nullptr || vector == nullptr) {
        Nrt_setErrMsgIsNullptrInternal();
        return NRT_FAILURE_UNKOWN;
    }

    Animation::SpriteAnimatorState* cppState = reinterpret_cast<Animation::SpriteAnimatorState*>(state);
    std::shared_ptr<Animation::SpriteAnimatorState> cppStateTarget = std::shared_ptr<Animation::SpriteAnimatorState>(reinterpret_cast<Animation::SpriteAnimatorState*>(stateTarget));
    std::vector<std::function<bool()>> conditions = *reinterpret_cast<std::vector<std::function<bool()>>*>(vector);
    
    cppState->insertNewState(cppStateTarget, conditions);
    return NRT_SUCCESS;
}

int32_t Nrt_SpriteAnimatorState_removeStateAtIndex(NrtSpriteAnimatorState state, size_t index) {
    if (state == nullptr) {
        Nrt_setErrMsgIsNullptrInternal();
        return NRT_FAILURE_UNKOWN;
    }

    Animation::SpriteAnimatorState* cppState = reinterpret_cast<Animation::SpriteAnimatorState*>(state);
    
    cppState->removeStateAtIndex(index);
    
    return NRT_SUCCESS;
}

int32_t Nrt_SpriteAnimatorState_getShouldLoop(NrtSpriteAnimatorState state, int32_t* outputLoop) {
    if (state == nullptr || outputLoop == nullptr) {
        Nrt_setErrMsgIsNullptrInternal();
        return NRT_FAILURE_UNKOWN;
    }

    Animation::SpriteAnimatorState* cppState = reinterpret_cast<Animation::SpriteAnimatorState*>(state);
    
    *outputLoop = static_cast<int32_t>(cppState->shouldLoop());
    
    return NRT_SUCCESS;
}

int32_t Nrt_SpriteAnimatorState_setShouldLoop(NrtSpriteAnimatorState state, int32_t loop) {
    if (state == nullptr) {
        Nrt_setErrMsgIsNullptrInternal();
        return NRT_FAILURE_UNKOWN;
    }

    Animation::SpriteAnimatorState* cppState = reinterpret_cast<Animation::SpriteAnimatorState*>(state);
    
    cppState->shouldLoop() = static_cast<bool>(loop);
    
    return NRT_SUCCESS;
}

int32_t Nrt_SpriteAnimatorState_getFrames(NrtSpriteAnimatorState state, NrtSpriteAnimatorFrameVector* outputFrames) {
    if (state == nullptr || outputFrames == nullptr) {
        Nrt_setErrMsgIsNullptrInternal();
        return NRT_FAILURE_UNKOWN;
    }

    Animation::SpriteAnimatorState* cppState = reinterpret_cast<Animation::SpriteAnimatorState*>(state);
    std::vector<Animation::SpriteAnimatorFrame>* frames = new std::vector<Animation::SpriteAnimatorFrame>();
    *frames = cppState->frames();

    *outputFrames = reinterpret_cast<NrtSpriteAnimatorFrameVector>(&frames);
    return NRT_SUCCESS;
}

int32_t Nrt_SpriteAnimatorState_setFrames(NrtSpriteAnimatorState state, NrtSpriteAnimatorFrameVector frames) {
    if (state == nullptr || frames == nullptr) {
        Nrt_setErrMsgIsNullptrInternal();
        return NRT_FAILURE_UNKOWN;
    }

    Animation::SpriteAnimatorState* cppState = reinterpret_cast<Animation::SpriteAnimatorState*>(state);
    std::vector<Animation::SpriteAnimatorFrame>* cppFrames = reinterpret_cast<std::vector<Animation::SpriteAnimatorFrame>*>(frames);//new std::vector<Animation::SpriteAnimatorFrame>();
    cppState->frames() = *cppFrames;
    return NRT_SUCCESS;
}

int32_t Nrt_SpriteAnimatorState_tryFindValidTransition(NrtSpriteAnimatorState state, NrtSpriteAnimatorState* outputTransitionState) {
    if (state == nullptr || outputTransitionState == nullptr) {
        Nrt_setErrMsgIsNullptrInternal();
        return NRT_FAILURE_UNKOWN;
    }

    Animation::SpriteAnimatorState* cppState = reinterpret_cast<Animation::SpriteAnimatorState*>(state);
    
    try {
        *outputTransitionState = reinterpret_cast<NrtSpriteAnimatorState>(cppState->tryFindValidTransition().get());
    }
    catch (const std::exception& ex) {
        const char* message = ex.what();
        char* target = new char[strlen(message) + 1];
        strcpy_s(target, strlen(message + 1), message);
        Nrt_setErrMsgCustomInternal(target);
        return NRT_FAILURE_UNKOWN;
    }
    
    return NRT_SUCCESS;    
}

NrtSpriteAnimatorFrameVector Nrt_SpriteAnimatorFrameVector_create() {
    std::vector<Animation::SpriteAnimatorFrame>* vector = new std::vector<Animation::SpriteAnimatorFrame>();
    return reinterpret_cast<NrtSpriteAnimatorFrameVector>(vector);
}

int32_t Nrt_SpriteAnimatorFrameVector_addFrame(NrtSpriteAnimatorFrameVector vector, NrtSpriteAnimatorFrame frame) {
    if (vector == nullptr || frame == nullptr) {
        Nrt_setErrMsgIsNullptrInternal();
        return NRT_FAILURE_UNKOWN;
    }

    std::vector<Animation::SpriteAnimatorFrame> cppVector = *reinterpret_cast<std::vector<Animation::SpriteAnimatorFrame>*>(vector);
    Animation::SpriteAnimatorFrame cppFrame = *reinterpret_cast<Animation::SpriteAnimatorFrame*>(frame);
    cppVector.push_back(cppFrame);
    return NRT_SUCCESS;
}

int32_t Nrt_SpriteAnimatorFrameVector_getFrameAtIndex(NrtSpriteAnimatorFrameVector vector, int32_t index, NrtSpriteAnimatorFrame* outputFrame) {
    if (vector == nullptr || outputFrame == nullptr) {
        Nrt_setErrMsgIsNullptrInternal();
        return NRT_FAILURE_UNKOWN;
    }

    std::vector<Animation::SpriteAnimatorFrame> cppVector = *reinterpret_cast<std::vector<Animation::SpriteAnimatorFrame>*>(vector);
    Animation::SpriteAnimatorFrame* cppFrame = new Animation::SpriteAnimatorFrame();
    *cppFrame = cppVector.at(index);
    return NRT_SUCCESS;
}

int32_t Nrt_SpriteAnimatorFrameVector_removeFrameAtIndex(NrtSpriteAnimatorFrameVector vector, int32_t index) {
    if (vector == nullptr) {
        Nrt_setErrMsgIsNullptrInternal();
        return NRT_FAILURE_UNKOWN;
    }

    std::vector<Animation::SpriteAnimatorFrame> cppVector = *reinterpret_cast<std::vector<Animation::SpriteAnimatorFrame>*>(vector);
    cppVector.erase(cppVector.begin() + index);
    return NRT_SUCCESS;
}

int32_t Nrt_SpriteAnimatorFrameVector_delete(NrtSpriteAnimatorFrameVector vector) {
    if (vector == nullptr) {
        Nrt_setErrMsgIsNullptrInternal();
        return NRT_FAILURE_UNKOWN;
    }

    std::vector<Animation::SpriteAnimatorFrame>* cppVector = reinterpret_cast<std::vector<Animation::SpriteAnimatorFrame>*>(vector);
    cppVector->clear();
    delete cppVector;
    return NRT_SUCCESS;
}

#ifdef __cplusplus
}
#endif
