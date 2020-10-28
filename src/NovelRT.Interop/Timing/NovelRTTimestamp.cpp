// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include "NovelRT.Interop/Timing/NovelRTTimestamp.h"
#include "NovelRT.Interop/NovelRTInteropUtils.h"
#include "NovelRT.h"

#ifdef __cplusplus
using namespace NovelRT;
extern "C" {
#endif


int32_t NovelRT_Timestamp_isNaN(NovelRTTimestamp timestamp, const char** errorMessage) {
    if (timestamp == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_TRUE;
    }

    Timing::Timestamp* ts = reinterpret_cast<Timing::Timestamp*>(timestamp);
    if(std::isnan(static_cast<double>(ts->_ticks))) {
      if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNaN();
        }
      return NOVELRT_TRUE;
    }

    return NOVELRT_FALSE;
  }

int32_t NovelRT_Timestamp_create(uint64_t ticks, NovelRTTimestamp* outputTimestamp, const char** errorMessage) {
    if (outputTimestamp == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }
    
    auto stamp = new Timing::Timestamp(ticks);
    *outputTimestamp = reinterpret_cast<NovelRTTimestamp>(&stamp);
    return NOVELRT_SUCCESS;
}

int32_t NovelRT_Timestamp_getSecondsDouble(NovelRTTimestamp timestamp, double* output, const char** errorMessage) {
    if (timestamp == nullptr || output == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }
    
    if (NovelRT_Timestamp_isNaN(timestamp, nullptr)) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNaN();
        }
        return NOVELRT_FAILURE;
    }

    Timing::Timestamp* ts = reinterpret_cast<Timing::Timestamp*>(timestamp);
    *output = ts->getSecondsDouble();
    return NOVELRT_SUCCESS;
}

int32_t NovelRT_Timestamp_getSecondsFloat(NovelRTTimestamp timestamp, float* output, const char** errorMessage) {
    if (timestamp == nullptr || output == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }

    if (NovelRT_Timestamp_isNaN(timestamp, nullptr)) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNaN();
        }
        return NOVELRT_FAILURE;
    }

    Timing::Timestamp* ts = reinterpret_cast<Timing::Timestamp*>(timestamp);
    *output = ts->getSecondsFloat();
    return NOVELRT_SUCCESS;
}

int32_t NovelRT_Timestamp_zero(NovelRTTimestamp* outputTimestamp, const char** errorMessage) {
    if (outputTimestamp == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }
    
    auto stamp = new Timing::Timestamp(0ULL);
    *outputTimestamp = reinterpret_cast<NovelRTTimestamp>(&stamp);
    return NOVELRT_SUCCESS;
}

int32_t NovelRT_Timestamp_fromSeconds(double seconds, NovelRTTimestamp* outputTimestamp, const char** errorMessage) {
    if (outputTimestamp == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }
    
    auto stamp = new Timing::Timestamp(0);
    *stamp = Timing::Timestamp::fromSeconds(seconds);
    *outputTimestamp = reinterpret_cast<NovelRTTimestamp>(&stamp);
    return NOVELRT_SUCCESS;
}

int32_t NovelRT_Timestamp_addTimestamp(NovelRTTimestamp first, NovelRTTimestamp other, NovelRTTimestamp* output, const char** errorMessage) {
    if (output == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }
    
    if (NovelRT_Timestamp_isNaN(first, nullptr) || NovelRT_Timestamp_isNaN(other, nullptr)) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNaN();
        }
        return NOVELRT_FAILURE;
    }

    Timing::Timestamp cFirst = *reinterpret_cast<Timing::Timestamp*>(first);
    Timing::Timestamp cOther = *reinterpret_cast<Timing::Timestamp*>(other);
    
    Timing::Timestamp* result = new Timing::Timestamp(0); 
    *result = cFirst + cOther;
    *output = reinterpret_cast<NovelRTTimestamp>(result);
    return NOVELRT_SUCCESS;
}

int32_t NovelRT_Timestamp_subtractTimestamp(NovelRTTimestamp first, NovelRTTimestamp other, NovelRTTimestamp* output, const char** errorMessage) {
    if (output == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }
    
    if (NovelRT_Timestamp_isNaN(first, nullptr) || NovelRT_Timestamp_isNaN(other, nullptr)) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNaN();
        }
        return NOVELRT_FAILURE;
    }
    
    Timing::Timestamp cFirst = *reinterpret_cast<Timing::Timestamp*>(first);
    Timing::Timestamp cOther = *reinterpret_cast<Timing::Timestamp*>(other);

    Timing::Timestamp* result = new Timing::Timestamp(0);
    *result = cFirst - cOther;
    *output = reinterpret_cast<NovelRTTimestamp>(result);
    return NOVELRT_SUCCESS;
}

int32_t NovelRT_Timestamp_multiplyTimestamp(NovelRTTimestamp first, NovelRTTimestamp other, NovelRTTimestamp* output, const char** errorMessage) {
    if (output == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }
    
    if (NovelRT_Timestamp_isNaN(first, nullptr) || NovelRT_Timestamp_isNaN(other, nullptr)) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNaN();
        }
        return NOVELRT_FAILURE;
    }

    Timing::Timestamp cFirst = *reinterpret_cast<Timing::Timestamp*>(first);
    Timing::Timestamp cOther = *reinterpret_cast<Timing::Timestamp*>(other);
    Timing::Timestamp result = cFirst * cOther;
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
    
    if (NovelRT_Timestamp_isNaN(first, nullptr) || NovelRT_Timestamp_isNaN(other, nullptr)) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNaN();
        }
        return NOVELRT_FAILURE;
    }

    Timing::Timestamp cFirst = *reinterpret_cast<Timing::Timestamp*>(first);
    Timing::Timestamp cOther = *reinterpret_cast<Timing::Timestamp*>(other);
    
    if (other == 0) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsDivideByZero();
        }
        return NOVELRT_FAILURE;
    }

    Timing::Timestamp result = cFirst / cOther;
    *output = reinterpret_cast<NovelRTTimestamp&>(result);
    return NOVELRT_SUCCESS;
}

int32_t NovelRT_Timestamp_addAssignTimestamp(NovelRTTimestamp first, NovelRTTimestamp other, const char** errorMessage) {
    if (first == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }

    if (NovelRT_Timestamp_isNaN(first, nullptr) || NovelRT_Timestamp_isNaN(other, nullptr)) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNaN();
        }
        return NOVELRT_FAILURE;
    }

    *reinterpret_cast<Timing::Timestamp*>(first) += *reinterpret_cast<Timing::Timestamp*>(other);
    return NOVELRT_SUCCESS;
}

int32_t NovelRT_Timestamp_subtractAssignTimestamp(NovelRTTimestamp first, NovelRTTimestamp other, const char** errorMessage) {
    if (first == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }

    if (NovelRT_Timestamp_isNaN(first, nullptr) || NovelRT_Timestamp_isNaN(other, nullptr)) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNaN();
        }
        return NOVELRT_FAILURE;
    }

    *reinterpret_cast<Timing::Timestamp*>(first) -= *reinterpret_cast<Timing::Timestamp*>(other);
    return NOVELRT_SUCCESS;
}

int32_t NovelRT_Timestamp_multiplyAssignTimestamp(NovelRTTimestamp first, NovelRTTimestamp other, const char** errorMessage) {
    if (first == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }

    if (NovelRT_Timestamp_isNaN(first, nullptr) || NovelRT_Timestamp_isNaN(other, nullptr)) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNaN();
        }
        return NOVELRT_FAILURE;
    }

    *reinterpret_cast<Timing::Timestamp*>(first) *= *reinterpret_cast<Timing::Timestamp*>(other);
    return NOVELRT_SUCCESS;
}

int32_t NovelRT_Timestamp_divideAssignTimestamp(NovelRTTimestamp first, NovelRTTimestamp other, const char** errorMessage) {
    if (first == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }

    if (NovelRT_Timestamp_isNaN(first, nullptr) || NovelRT_Timestamp_isNaN(other, nullptr)) {
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

    *reinterpret_cast<Timing::Timestamp*>(first) /= *reinterpret_cast<Timing::Timestamp*>(other);
    return NOVELRT_SUCCESS;
}

int32_t NovelRT_Timestamp_lessThan(NovelRTTimestamp lhs, NovelRTTimestamp rhs, const char** errorMessage) {
    if (lhs == nullptr || rhs == nullptr)  {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }
    
    if (NovelRT_Timestamp_isNaN(lhs, nullptr) || NovelRT_Timestamp_isNaN(rhs, nullptr)) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNaN();
        }
        return NOVELRT_FAILURE;
    }
    
    Timing::Timestamp cFirst = *reinterpret_cast<Timing::Timestamp*>(lhs);
    Timing::Timestamp cOther = *reinterpret_cast<Timing::Timestamp*>(rhs);
    if(cFirst < cOther) {
      return NOVELRT_TRUE;
    }

    return NOVELRT_FALSE;
}

int32_t NovelRT_Timestamp_lessThanOrEqualTo(NovelRTTimestamp lhs, NovelRTTimestamp rhs, const char** errorMessage) {
    if (lhs == nullptr || rhs == nullptr)  {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }

    if (NovelRT_Timestamp_isNaN(lhs, nullptr) || NovelRT_Timestamp_isNaN(rhs, nullptr)) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNaN();
        }
        return NOVELRT_FAILURE;
    }
    
    Timing::Timestamp cFirst = *reinterpret_cast<Timing::Timestamp*>(lhs);
    Timing::Timestamp cOther = *reinterpret_cast<Timing::Timestamp*>(rhs);
    if(cFirst <= cOther) {
      return NOVELRT_TRUE;
    }

    return NOVELRT_FALSE;
}

int32_t NovelRT_Timestamp_greaterThan(NovelRTTimestamp lhs, NovelRTTimestamp rhs, const char** errorMessage) {
    if (lhs == nullptr || rhs == nullptr)  {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }

    if (NovelRT_Timestamp_isNaN(lhs, nullptr) || NovelRT_Timestamp_isNaN(rhs, nullptr)) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNaN();
        }
        return NOVELRT_FAILURE;
    }
    
    Timing::Timestamp cFirst = *reinterpret_cast<Timing::Timestamp*>(lhs);
    Timing::Timestamp cOther = *reinterpret_cast<Timing::Timestamp*>(rhs);
    if(cFirst > cOther) {
      return NOVELRT_TRUE;
    }

    return NOVELRT_FALSE;
}

int32_t NovelRT_Timestamp_greaterThanOrEqualTo(NovelRTTimestamp lhs, NovelRTTimestamp rhs, const char** errorMessage) {
    if (lhs == nullptr || rhs == nullptr)  {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }

    if (NovelRT_Timestamp_isNaN(lhs, nullptr) || NovelRT_Timestamp_isNaN(rhs, nullptr)) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNaN();
        }
        return NOVELRT_FAILURE;
    }
    
    Timing::Timestamp cFirst = *reinterpret_cast<Timing::Timestamp*>(lhs);
    Timing::Timestamp cOther = *reinterpret_cast<Timing::Timestamp*>(rhs);
    if(cFirst >= cOther) {
      return NOVELRT_TRUE;
    }

    return NOVELRT_FALSE;
}

int32_t NovelRT_Timestamp_equal(NovelRTTimestamp lhs, NovelRTTimestamp rhs, const char** errorMessage) {
    if (lhs == nullptr || rhs == nullptr)  {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }

    if (NovelRT_Timestamp_isNaN(lhs, nullptr) || NovelRT_Timestamp_isNaN(rhs, nullptr)) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNaN();
        }
        return NOVELRT_FAILURE;
    }
    
    Timing::Timestamp cFirst = *reinterpret_cast<Timing::Timestamp*>(lhs);
    Timing::Timestamp cOther = *reinterpret_cast<Timing::Timestamp*>(rhs);
    if(cFirst == cOther) {
      return NOVELRT_TRUE;
    }

    return NOVELRT_FALSE;
}

int32_t NovelRT_Timestamp_notEqual(NovelRTTimestamp lhs, NovelRTTimestamp rhs, const char** errorMessage) {
    if (lhs == nullptr || rhs == nullptr)  {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }

    if (NovelRT_Timestamp_isNaN(lhs, nullptr) || NovelRT_Timestamp_isNaN(rhs, nullptr)) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNaN();
        }
        return NOVELRT_FAILURE;
    }
    
    Timing::Timestamp cFirst = *reinterpret_cast<Timing::Timestamp*>(lhs);
    Timing::Timestamp cOther = *reinterpret_cast<Timing::Timestamp*>(rhs);
    if(cFirst != cOther) {
      return NOVELRT_TRUE;
    }

    return NOVELRT_FALSE;
}

#ifdef __cplusplus
}
#endif
