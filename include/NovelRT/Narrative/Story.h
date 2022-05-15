// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_STORY_H
#define NOVELRT_STORY_H

namespace NovelRT::Narrative
{
    class Story
    {
    public:
        virtual void LoadData(gsl::span<uint8_t> data) = 0;
        virtual void RegisterScriptMethod(const std::string& name, std::function<void()> method) = 0;
        virtual void UnregisterScriptMethod(const std::string& name) = 0; // TODO: idk if we need unregistering for this
        [[nodiscard]] virtual const DialogueNode& PlayFromBeginning() = 0;
        [[nodiscard]] virtual const DialogueNode& MoveNext() = 0;
        [[nodiscard]] virtual const DialogueNode& JumpToSection(const std::string& sectionName) = 0;
        [[nodiscard]] virtual gsl::span<const DialogueNode> GetDialogueHistoryTimeline() = 0;
    };
}

#endif // NOVELRT_STORY_H
