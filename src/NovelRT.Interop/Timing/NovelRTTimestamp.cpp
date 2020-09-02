// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include "NovelRT.Interop/Timing/NovelRTTimestamp.h"
#include "NovelRT.Interop/NovelRTInteropUtils.h"
#include "NovelRT.h"

NovelRTResult NovelRT_Timestamp_create(uint64_t ticks, NovelRTTimestamp* output, const char** errorMessage) {
    if (output == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }

    auto stamp = NovelRT::Timing::Timestamp(ticks);
    *output = reinterpret_cast<NovelRTTimestamp>(&stamp);
    return NOVELRT_SUCCESS;
}

NovelRTResult NovelRT_Timestamp_getTicks(NovelRTTimestamp timestamp, uint64_t* output, const char** errorMessage) {
    if (timestamp == nullptr || output == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }

    auto cStamp = reinterpret_cast<NovelRT::Timing::Timestamp&>(timestamp);
    *output = cStamp.getTicks();
    return NOVELRT_SUCCESS;
}

NovelRTResult NovelRT_Timestamp_getSecondsDouble(NovelRTTimestamp timestamp, double* output, const char** errorMessage) {
    if (timestamp == nullptr || output == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }

    auto cStamp = reinterpret_cast<NovelRT::Timing::Timestamp&>(timestamp);
    *output = cStamp.getSecondsDouble();
    return NOVELRT_SUCCESS;
}

NovelRTResult NovelRT_Timestamp_getSecondsFloat(NovelRTTimestamp timestamp, float* output, const char** errorMessage) {
    if (timestamp == nullptr || output == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }

    auto cStamp = reinterpret_cast<NovelRT::Timing::Timestamp&>(timestamp);
    *output = cStamp.getSecondsFloat();
    return NOVELRT_SUCCESS;
}

NovelRTResult NovelRT_Timestamp_zero(NovelRTTimestamp* output, const char** errorMessage) {
    if (output == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }

    auto newStamp = NovelRT::Timing::Timestamp::zero();
    *output = reinterpret_cast<NovelRTTimestamp>(&newStamp);
    return NOVELRT_SUCCESS;
}

NovelRTResult NovelRT_Timestamp_fromSeconds(double seconds, NovelRTTimestamp* output, const char** errorMessage) {
    if (output == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }

    auto newStamp = NovelRT::Timing::Timestamp::fromSeconds(seconds);
    *output = reinterpret_cast<NovelRTTimestamp>(&newStamp);
    return NOVELRT_SUCCESS;
}

 NovelRTResult NovelRT_Timestamp_add(NovelRTTimestamp first, NovelRTTimestamp other, NovelRTTimestamp* output, const char** errorMessage) {
    if (first == nullptr || other == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }

    auto cFirst = reinterpret_cast<NovelRT::Timing::Timestamp&>(first);
    auto cOther = reinterpret_cast<NovelRT::Timing::Timestamp&>(other);
    auto newStamp = cFirst + cOther;
    *output = reinterpret_cast<NovelRTTimestamp>(&newStamp);
    return NOVELRT_SUCCESS;
}

NovelRTResult NovelRT_Timestamp_subtract(NovelRTTimestamp first, NovelRTTimestamp other, NovelRTTimestamp* output, const char** errorMessage) {
    if (first == nullptr || other == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }

    auto cFirst = reinterpret_cast<NovelRT::Timing::Timestamp&>(first);
    auto cOther = reinterpret_cast<NovelRT::Timing::Timestamp&>(other);
    auto newStamp = cFirst - cOther;
    *output = reinterpret_cast<NovelRTTimestamp>(&newStamp);
    return NOVELRT_SUCCESS;
}

NovelRTResult NovelRT_Timestamp_multiply(NovelRTTimestamp first, NovelRTTimestamp other, NovelRTTimestamp* output, const char** errorMessage) {
    if (first == nullptr || other == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }

    auto cFirst = reinterpret_cast<NovelRT::Timing::Timestamp&>(first);
    auto cOther = reinterpret_cast<NovelRT::Timing::Timestamp&>(other);
    auto newStamp = cFirst * cOther;
    *output = reinterpret_cast<NovelRTTimestamp>(&newStamp);
    return NOVELRT_SUCCESS;
}

NovelRTResult NovelRT_Timestamp_divide(NovelRTTimestamp first, NovelRTTimestamp other, NovelRTTimestamp* output, const char** errorMessage) {
    if (first == nullptr || other == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }

    auto cFirst = reinterpret_cast<NovelRT::Timing::Timestamp&>(first);
    auto cOther = reinterpret_cast<NovelRT::Timing::Timestamp&>(other);
    auto newStamp = cFirst / cOther;
    *output = reinterpret_cast<NovelRTTimestamp>(&newStamp);
    return NOVELRT_SUCCESS;
}

NovelRTResult NovelRT_Timestamp_addIntoTimestamp(NovelRTTimestamp first, NovelRTTimestamp other, const char** errorMessage) {
    if (first == nullptr || other == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }

    auto cFirst = reinterpret_cast<NovelRT::Timing::Timestamp&>(first);
    auto cOther = reinterpret_cast<NovelRT::Timing::Timestamp&>(other);
    cFirst += cOther;
    first = reinterpret_cast<NovelRTTimestamp>(&cFirst);
    return NOVELRT_SUCCESS;
}

NovelRTResult NovelRT_Timestamp_subtractIntoTimestamp(NovelRTTimestamp first, NovelRTTimestamp other, const char** errorMessage) {
    if (first == nullptr || other == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }

    auto cFirst = reinterpret_cast<NovelRT::Timing::Timestamp&>(first);
    auto cOther = reinterpret_cast<NovelRT::Timing::Timestamp&>(other);
    cFirst -= cOther;
    first = reinterpret_cast<NovelRTTimestamp>(&cFirst);
    return NOVELRT_SUCCESS;
}

NovelRTResult NovelRT_Timestamp_multiplyIntoTimestamp(NovelRTTimestamp first, NovelRTTimestamp other, const char** errorMessage) {
    if (first == nullptr || other == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }

    auto cFirst = reinterpret_cast<NovelRT::Timing::Timestamp&>(first);
    auto cOther = reinterpret_cast<NovelRT::Timing::Timestamp&>(other);
    cFirst *= cOther;
    first = reinterpret_cast<NovelRTTimestamp>(&cFirst);
    return NOVELRT_SUCCESS;
}

NovelRTResult NovelRT_Timestamp_divideIntoTimestamp(NovelRTTimestamp first, NovelRTTimestamp other, const char** errorMessage) {
    if (first == nullptr || other == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }

    auto cFirst = reinterpret_cast<NovelRT::Timing::Timestamp&>(first);
    auto cOther = reinterpret_cast<NovelRT::Timing::Timestamp&>(other);
    cFirst /= cOther;
    first = reinterpret_cast<NovelRTTimestamp>(&cFirst);
    return NOVELRT_SUCCESS;
}

NovelRTResult NovelRT_Timestamp_lessThan(NovelRTTimestamp first, NovelRTTimestamp other, NovelRTBool* result, const char** errorMessage) {
    if (first == nullptr || other == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }

    auto cFirst = reinterpret_cast<NovelRT::Timing::Timestamp&>(first);
    auto cOther = reinterpret_cast<NovelRT::Timing::Timestamp&>(other);
    *result = cFirst < cOther;
    return NOVELRT_SUCCESS;
}

NovelRTResult NovelRT_Timestamp_lessThanOrEqualTo(NovelRTTimestamp first, NovelRTTimestamp other, NovelRTBool* result, const char** errorMessage) {
    if (first == nullptr || other == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }

    auto cFirst = reinterpret_cast<NovelRT::Timing::Timestamp&>(first);
    auto cOther = reinterpret_cast<NovelRT::Timing::Timestamp&>(other);
    *result = cFirst <= cOther;
    return NOVELRT_SUCCESS;
}

NovelRTResult NovelRT_Timestamp_greaterThan(NovelRTTimestamp first, NovelRTTimestamp other, NovelRTBool* result, const char** errorMessage) {
    if (first == nullptr || other == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }

    auto cFirst = reinterpret_cast<NovelRT::Timing::Timestamp&>(first);
    auto cOther = reinterpret_cast<NovelRT::Timing::Timestamp&>(other);
    *result = cFirst > cOther;
    return NOVELRT_SUCCESS;
}

NovelRTResult NovelRT_Timestamp_greaterThanOrEqualTo(NovelRTTimestamp first, NovelRTTimestamp other, NovelRTBool* result, const char** errorMessage) {
    if (first == nullptr || other == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }

    auto cFirst = reinterpret_cast<NovelRT::Timing::Timestamp&>(first);
    auto cOther = reinterpret_cast<NovelRT::Timing::Timestamp&>(other);
    *result = cFirst >= cOther;
    return NOVELRT_SUCCESS;
}

NovelRTResult NovelRT_Timestamp_equal(NovelRTTimestamp first, NovelRTTimestamp other, NovelRTBool* result, const char** errorMessage) {
    if (first == nullptr || other == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }

    auto cFirst = reinterpret_cast<NovelRT::Timing::Timestamp&>(first);
    auto cOther = reinterpret_cast<NovelRT::Timing::Timestamp&>(other);
    *result = cFirst == cOther;
    return NOVELRT_SUCCESS;
}

NovelRTResult NovelRT_Timestamp_notEqual(NovelRTTimestamp first, NovelRTTimestamp other, NovelRTBool* result, const char** errorMessage) {
    if (first == nullptr || other == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }

    auto cFirst = reinterpret_cast<NovelRT::Timing::Timestamp&>(first);
    auto cOther = reinterpret_cast<NovelRT::Timing::Timestamp&>(other);
    *result = cFirst != cOther;
    return NOVELRT_SUCCESS;
}