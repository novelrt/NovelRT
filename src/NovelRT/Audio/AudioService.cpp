// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <NovelRT.h>

namespace NovelRT::Audio {

AudioService::AudioService() : _logger(LoggingService(Utilities::Misc::CONSOLE_LOG_AUDIO)) {
  auto device = alcOpenDevice(NULL);
  if (!device) {
    throw std::runtime_error("Could not get audio devices!");
  }
  auto context = alcCreateContext(device, NULL);
  alcMakeContextCurrent(context);
  isInitialized = true;
  _logger.logInfoLine("OpenAL Initialized");
}


AudioService::~AudioService() {
  auto context = alcGetCurrentContext();
  auto device = alcGetContextsDevice(context);
  alcMakeContextCurrent(NULL);
  alcDestroyContext(context);
  alcCloseDevice(device);
}

}
