#include "..\..\..\..\..\include\NovelRT\Experimental\Input\Glfw\GlfwInputDevice.h"


GlfwInputDevice::GlfwInputDevice() noexcept
    : _previousBufferIndex(0),
      _currentBufferIndex(1)
{
    //windowingService->WindowResized += [this](auto value) { setScreenSize(value); };
    //have to make sure windowingdevice updates this class

    //have to move polling to InputDevice
    /*
      windowingService->MouseButtonClicked += [this](auto eventArgs) {
          acceptMouseButtonClickPush(eventArgs.button, eventArgs.action, eventArgs.mousePosition);
      };
      windowingService->KeyboardButtonChanged +=
          [this](auto eventArgs) { acceptKeyboardInputBindingPush(eventArgs.key, eventArgs.action); };
    */
}

void GlfwInputDevice::processKeyStates()
{
    auto& currentBuffer = _keyStates.at(_currentBufferIndex);

    for (const auto& pair : _keyStates.at(_previousBufferIndex))
    {
        auto findResultForCurrent = currentBuffer.find(pair.first);
        if (findResultForCurrent != currentBuffer.end())
        {
            processKeyState(findResultForCurrent->first, findResultForCurrent->second.getCurrentState());
        }
        else
        {
            processKeyState(pair.first, pair.second.getCurrentState());
        }
    }
}

void GlfwInputDevice::processKeyState(KeyCode code, KeyState state)
{
    auto& previousBuffer = _keyStates.at(_previousBufferIndex);
    auto& currentBuffer = _keyStates.at(_currentBufferIndex);

    auto previousBufferResult = previousBuffer.find(code);
    KeyState previousStateResult;

    if (previousBufferResult == previousBuffer.end())
    {
        previousStateResult = KeyState::Idle;
    }
    else
    {
        previousStateResult = previousBufferResult->second.getCurrentState();
    }

    auto currentBufferResult = currentBuffer.find(code);
    KeyStateFrameChangeLog changeLogObject{};

    if (currentBufferResult == currentBuffer.end())
    {
        changeLogObject = KeyStateFrameChangeLog();
    }
    else
    {
        changeLogObject = currentBufferResult->second;
    }

    switch (state)
    {
        case KeyState::KeyDown:
            if (previousStateResult == KeyState::KeyDown)
            {
                changeLogObject.pushNewState(KeyState::KeyDownHeld);
            }
            else if (previousStateResult != KeyState::KeyDownHeld)
            {
                changeLogObject.pushNewState(KeyState::KeyDown); // TODO: Is this actually gonna work lol
            }
            break;
        case KeyState::KeyDownHeld:
        case KeyState::KeyUp:
            changeLogObject.pushNewState((previousStateResult == KeyState::KeyUp) ? KeyState::Idle : state);
            break;
        case KeyState::Idle:
        default:
            // do nothing. Seriously. These cases are only here because the Ubuntu build cried at me in CI for not
            // having them suddenly.
            break;
    }
}

void GlfwInputDevice::acceptMouseButtonClickPush(int32_t button, int32_t action, Maths::GeoVector2F mousePosition)
{
    auto keyState = static_cast<KeyState>(action);
    auto keyCode = static_cast<KeyCode>(button);
    auto value = Maths::GeoVector4F(mousePosition).vec4Value() *
                 glm::scale(glm::vec3(1920.0f / _screenSize.x, 1080.0f / _screenSize.y, 0.0f));

    _cursorPosition = Maths::GeoVector2F(value.x, value.y);
    KeyStateFrameChangeLog log{};

    if (_keyStates.at(_currentBufferIndex).find(keyCode) != _keyStates.at(_currentBufferIndex).end())
    {
        log = _keyStates.at(_currentBufferIndex).at(keyCode);
    }

    log.pushNewState(keyState);
    _keyStates.at(_currentBufferIndex).insert_or_assign(keyCode, log);
}

void GlfwInputDevice::acceptKeyboardInputBindingPush(int32_t key, int32_t action)
{
    auto keyState = static_cast<KeyState>(action);
    auto keyCode = static_cast<KeyCode>(key);
    KeyStateFrameChangeLog log{};

    if (_keyStates.at(_currentBufferIndex).find(keyCode) != _keyStates.at(_currentBufferIndex).end())
    {
        log = _keyStates.at(_currentBufferIndex).at(keyCode);
    }

    log.pushNewState(keyState);
    _keyStates.at(_currentBufferIndex).insert_or_assign(keyCode, log);
}

void GlfwInputDevice::consumePlayerInput()
{
    _currentBufferIndex = (_currentBufferIndex + 1) % INPUT_BUFFER_COUNT;
    _keyStates.at(_currentBufferIndex).clear();
    glfwPollEvents();
    processKeyStates();
    _previousBufferIndex = _currentBufferIndex;
}
