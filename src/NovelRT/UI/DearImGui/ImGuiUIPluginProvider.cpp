// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include "NovelRT/UI/DearImGui/UI.DearImGui.h"

namespace NovelRT::UI::DearImGui
{
    ImGuiUIPluginProvider::ImGuiUIPluginProvider() noexcept
        : _uiProvider([&]() { return CreateImGuiUIProviderInternal(); })
    {
    }

    std::shared_ptr<ImGuiUIProvider> ImGuiUIPluginProvider::CreateImGuiUIProviderInternal()
    {
        return std::make_shared<ImGuiUIProvider>();
    }

    ImGuiUIProvider* ImGuiUIPluginProvider::GetUIProviderInternal()
    {
        return _uiProvider.getActual().get();
    }
}
