// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include "NovelRT.Interop/Timing/NovelRTTimestamp.h"
#include "NovelRT.Interop/NovelRTInteropUtils.h"
#include "NovelRT.h"

#ifdef __cplusplus
extern "C" {
#endif


int32_t NovelRT_Timestamp_isNaN(NovelRTTimestamp timestamp) {
    if(std::isnan(static_cast<double>(timestamp))) {
      return NOVELRT_TRUE;
    }

    return NOVELRT_FALSE;
  }

NovelRTTimestamp NovelRT_Timestamp_create(uint64_t ticks) {
    auto stamp = NovelRT::Timing::Timestamp(ticks);
    return reinterpret_cast<NovelRTTimestamp&>(stamp);
}

double NovelRT_Timestamp_getSecondsDouble(NovelRTTimestamp timestamp) {
    auto stamp = reinterpret_cast<NovelRT::Timing::Timestamp&>(timestamp);
    return stamp.getSecondsDouble();
}

float NovelRT_Timestamp_getSecondsFloat(NovelRTTimestamp timestamp) {
    auto stamp = reinterpret_cast<NovelRT::Timing::Timestamp&>(timestamp);
    return stamp.getSecondsFloat();
}

NovelRTTimestamp NovelRT_Timestamp_zero() {
    auto stamp = NovelRT::Timing::Timestamp::zero();
    return reinterpret_cast<NovelRTTimestamp&>(stamp);
}

NovelRTTimestamp NovelRT_Timestamp_fromSeconds(double seconds) {
    auto stamp = NovelRT::Timing::Timestamp::fromSeconds(seconds);
    return reinterpret_cast<NovelRTTimestamp&>(stamp);
}

int32_t NovelRT_Timestamp_addTimestamp(NovelRTTimestamp first, NovelRTTimestamp other, NovelRTTimestamp* output, const char** errorMessage) {
    if (output == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }
    
    NovelRT::Timing::Timestamp cFirst = reinterpret_cast<NovelRT::Timing::Timestamp&>(first);
    NovelRT::Timing::Timestamp cOther = reinterpret_cast<NovelRT::Timing::Timestamp&>(other);
    if (NovelRT_Timestamp_isNaN(first) || NovelRT_Timestamp_isNaN(other)) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNaN();
        }
        return NOVELRT_FAILURE;
    }

    NovelRT::Timing::Timestamp result = cFirst + cOther;
    *output = reinterpret_cast<NovelRTTimestamp&>(result);
    return NOVELRT_SUCCESS;
}

int32_t NovelRT_Timestamp_subtractTimestamp(NovelRTTimestamp first, NovelRTTimestamp other, NovelRTTimestamp* output, const char** errorMessage) {
    if (output == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }
    
    NovelRT::Timing::Timestamp cFirst = reinterpret_cast<NovelRT::Timing::Timestamp&>(first);
    NovelRT::Timing::Timestamp cOther = reinterpret_cast<NovelRT::Timing::Timestamp&>(other);
    if (NovelRT_Timestamp_isNaN(first) || NovelRT_Timestamp_isNaN(other)) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNaN();
        }
        return NOVELRT_FAILURE;
    }

    NovelRT::Timing::Timestamp result = cFirst - cOther;
    *output = reinterpret_cast<NovelRTTimestamp&>(result);
    return NOVELRT_SUCCESS;
}

int32_t NovelRT_Timestamp_multiplyTimestamp(NovelRTTimestamp first, NovelRTTimestamp other, NovelRTTimestamp* output, const char** errorMessage) {
    if (output == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }
    
    NovelRT::Timing::Timestamp cFirst = reinterpret_cast<NovelRT::Timing::Timestamp&>(first);
    NovelRT::Timing::Timestamp cOther = reinterpret_cast<NovelRT::Timing::Timestamp&>(other);
    if (NovelRT_Timestamp_isNaN(first) || NovelRT_Timestamp_isNaN(other)) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNaN();
        }
        return NOVELRT_FAILURE;
    }

    NovelRT::Timing::Timestamp result = cFirst * cOther;
    *output = reinterpret_cast<NovelRTTimestamp&>(result);
    return NOVELRT_SUCCESS;
}

int32_t NovelRT_Timestamp_divideTimestamp(NovelRTTimestamp first, NovelRTTimestamp other, NovelRTTimestamp* output, const char** errorMessage) {
    if (output == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }
    
    NovelRT::Timing::Timestamp cFirst = reinterpret_cast<NovelRT::Timing::Timestamp&>(first);
    NovelRT::Timing::Timestamp cOther = reinterpret_cast<NovelRT::Timing::Timestamp&>(other);
    if (NovelRT_Timestamp_isNaN(first) || NovelRT_Timestamp_isNaN(other)) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNaN();
        }
        return NOVELRT_FAILURE;
    }

    if (other == 0) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsDivideByZero();
        }
        return NOVELRT_FAILURE;
    }

    NovelRT::Timing::Timestamp result = cFirst / cOther;
    *output = reinterpret_cast<NovelRTTimestamp&>(result);
    return NOVELRT_SUCCESS;
}

int32_t NovelRT_Timestamp_addAssignTimestamp(NovelRTTimestamp* first, NovelRTTimestamp other, const char** errorMessage) {
    if (first == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }

    *reinterpret_cast<NovelRT::Timing::Timestamp*>(first) += reinterpret_cast<NovelRT::Timing::Timestamp&>(other);
    return NOVELRT_SUCCESS;
}

int32_t NovelRT_Timestamp_subtractAssignTimestamp(NovelRTTimestamp* first, NovelRTTimestamp other, const char** errorMessage) {
    if (first == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }

    *reinterpret_cast<NovelRT::Timing::Timestamp*>(first) -= reinterpret_cast<NovelRT::Timing::Timestamp&>(other);
    return NOVELRT_SUCCESS;
}

int32_t NovelRT_Timestamp_multiplyAssignTimestamp(NovelRTTimestamp* first, NovelRTTimestamp other, const char** errorMessage) {
    if (first == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }

    *reinterpret_cast<NovelRT::Timing::Timestamp*>(first) *= reinterpret_cast<NovelRT::Timing::Timestamp&>(other);
    return NOVELRT_SUCCESS;
}

int32_t NovelRT_Timestamp_divideAssignTimestamp(NovelRTTimestamp* first, NovelRTTimestamp other, const char** errorMessage) {
    if (first == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }

    if (other == 0) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsDivideByZero();
        }
        return NOVELRT_FAILURE;
    }

    *reinterpret_cast<NovelRT::Timing::Timestamp*>(first) /= reinterpret_cast<NovelRT::Timing::Timestamp&>(other);
    return NOVELRT_SUCCESS;
}

int32_t NovelRT_Timestamp_lessThan(NovelRTTimestamp lhs, NovelRTTimestamp rhs) {
    NovelRT::Timing::Timestamp cFirst = reinterpret_cast<NovelRT::Timing::Timestamp&>(lhs);
    NovelRT::Timing::Timestamp cOther = reinterpret_cast<NovelRT::Timing::Timestamp&>(rhs);
    if(cFirst < cOther) {
      return NOVELRT_TRUE;
    }

    return NOVELRT_FALSE;
}

int32_t NovelRT_Timestamp_lessThanOrEqualTo(NovelRTTimestamp lhs, NovelRTTimestamp rhs) {
    NovelRT::Timing::Timestamp cFirst = reinterpret_cast<NovelRT::Timing::Timestamp&>(lhs);
    NovelRT::Timing::Timestamp cOther = reinterpret_cast<NovelRT::Timing::Timestamp&>(rhs);
    if(cFirst <= cOther) {
      return NOVELRT_TRUE;
    }

    return NOVELRT_FALSE;
}

int32_t NovelRT_Timestamp_greaterThan(NovelRTTimestamp lhs, NovelRTTimestamp rhs) {
    NovelRT::Timing::Timestamp cFirst = reinterpret_cast<NovelRT::Timing::Timestamp&>(lhs);
    NovelRT::Timing::Timestamp cOther = reinterpret_cast<NovelRT::Timing::Timestamp&>(rhs);
    if(cFirst > cOther) {
      return NOVELRT_TRUE;
    }

    return NOVELRT_FALSE;
}

int32_t NovelRT_Timestamp_greaterThanOrEqualTo(NovelRTTimestamp lhs, NovelRTTimestamp rhs) {
    NovelRT::Timing::Timestamp cFirst = reinterpret_cast<NovelRT::Timing::Timestamp&>(lhs);
    NovelRT::Timing::Timestamp cOther = reinterpret_cast<NovelRT::Timing::Timestamp&>(rhs);
    if(cFirst >= cOther) {
      return NOVELRT_TRUE;
    }

    return NOVELRT_FALSE;
}

int32_t NovelRT_Timestamp_equal(NovelRTTimestamp lhs, NovelRTTimestamp rhs) {
    NovelRT::Timing::Timestamp cFirst = reinterpret_cast<NovelRT::Timing::Timestamp&>(lhs);
    NovelRT::Timing::Timestamp cOther = reinterpret_cast<NovelRT::Timing::Timestamp&>(rhs);
    if(cFirst == cOther) {
      return NOVELRT_TRUE;
    }

    return NOVELRT_FALSE;
}

int32_t NovelRT_Timestamp_notEqual(NovelRTTimestamp lhs, NovelRTTimestamp rhs) {
    NovelRT::Timing::Timestamp cFirst = reinterpret_cast<NovelRT::Timing::Timestamp&>(lhs);
    NovelRT::Timing::Timestamp cOther = reinterpret_cast<NovelRT::Timing::Timestamp&>(rhs);
    if(cFirst != cOther) {
      return NOVELRT_TRUE;
    }

    return NOVELRT_FALSE;
}

#ifdef __cplusplus
}
#endif
