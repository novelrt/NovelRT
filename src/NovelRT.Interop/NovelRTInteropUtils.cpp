// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include "NovelRT.Interop/NovelRTInteropUtils.h"
#include <unordered_map>
#include<vector>

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
    if(&ptrPair.originalText == &errorPtr) {
      return ptrPair.translatedText;
    }
  }
  return nullptr;
}