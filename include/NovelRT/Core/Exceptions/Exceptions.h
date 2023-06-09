//
// Created by Matt on 06/01/2021.
//

#ifndef NOVELRT_CORE_EXCEPTIONS_H
#define NOVELRT_CORE_EXCEPTIONS_H

#include <chrono>
#include <stdexcept>
#include <string>

namespace NovelRT::Core::Exceptions
{
    class CharacterNotFoundException;
    class CompilationErrorException;
    class DuplicateKeyException;
    class FileNotFoundException;
    class FunctionNotFoundException;
    class InitialisationFailureException;
    class InvalidOperationException;
    class IOException;
    class KeyNotFoundException;
    class NotInitialisedException;
    class NotSupportedException;
    class NullPointerException;
    class OpenGLLinkageFailureException;
    class OutOfMemoryException;
    class RuntimeNotFoundException;
    class TimeoutException;
}

#include "CharacterNotFoundException.h"
#include "CompilationErrorException.h"
#include "DuplicateKeyException.h"
#include "FileNotFoundException.h"
#include "FunctionNotFoundException.h"
#include "IOException.h"
#include "InitialisationFailureException.h"
#include "InvalidOperationException.h"
#include "KeyNotFoundException.h"
#include "NotInitialisedException.h"
#include "NotSupportedException.h"
#include "NullPointerException.h"
#include "OpenGLLinkageFailureException.h"
#include "OutOfMemoryException.h"
#include "RuntimeNotFoundException.h"
#include "TimeoutException.h"

#endif // NOVELRT_CORE_EXCEPTIONS_H
