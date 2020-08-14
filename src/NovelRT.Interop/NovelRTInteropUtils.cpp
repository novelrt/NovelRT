// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include "NovelRT.Interop/NovelRTInteropUtils.h"
#include <unordered_map>
#include <vector>


const char* const cpuLangKey = "cpu";
const char* const errMsgIsNullptr = "Unable to continue! A nullptr was passed when a ptr was expected.";
const char* const errMsgIsNaN = "Unable to continue! Calculation resulted in an object that is not a number (NaN).";
const char* const errMsgIsDivideByZero = "Unable to continue! Divide by zero was attempted.";

struct ErrorTranslationPair {
  const char* originalText;
  const char* translatedText;
};

std::vector<ErrorTranslationPair> cpuPair {
  ErrorTranslationPair {
    errMsgIsNullptr,
    "FAILURE_IS_NULLPTR"
  },
  ErrorTranslationPair {
    errMsgIsNaN,
    "FAILURE_IS_NAN"
  },
  ErrorTranslationPair {
    errMsgIsDivideByZero,
    "FAILURE_IS_DIVIDE_BY_ZERO"
  }
};

std::unordered_map<std::string, std::vector<ErrorTranslationPair>> translations {
  {
    cpuLangKey, cpuPair
  }
};

const char* NovelRT_translateErrorCode(const char* const targetLanguage, const char* const errorPtr) {
  std::string thing(targetLanguage);
  auto& vec = translations[thing];

  for (const auto& ptrPair : vec) {
    if(std::addressof(ptrPair.originalText) == std::addressof(errorPtr)) {
      return ptrPair.translatedText;
    }
  }
  return nullptr;
}