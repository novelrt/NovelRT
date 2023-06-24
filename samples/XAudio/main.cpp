// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Audio/XAudio2/Audio.XAudio2.h>
#include <NovelRT/LoggingService.h>

int main()
{
    NovelRT::LoggingService logger = NovelRT::LoggingService();

    NovelRT::Audio::XAudio2::XAudio2Engine engine = NovelRT::Audio::XAudio2::XAudio2Engine();

    logger.logInfoLine("Hello");
    engine.Initialise();
    NovelRT::Audio::SoundDefinition def{};
    def.defaultVolumeIndB = 1.0f;
    def.soundName = "goat";
    def.looping = false;
    engine.LoadSound(def);
    engine.PlaySound("goat", 0.0);
    int flag = 1;

    while(flag)
    {
        if(GetKeyState(VK_SPACE & 0x8000))
        {
            flag = 0;
        }
    }

    return 0;
}
