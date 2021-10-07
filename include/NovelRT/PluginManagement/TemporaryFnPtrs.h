// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_PLUGINMANAGEMENT_TEMPORARYFNPTRS_H
#define NOVELRT_PLUGINMANAGEMENT_TEMPORARYFNPTRS_H

#ifndef NOVELRT_PLUGINMANAGEMENT_H
#error NovelRT does not support including types explicitly by default. Please include PluginManagement.h instead for the PluginManagement namespace subset.
#endif

/**
 * @brief This whole header is a hack. It won't be here post-MVP.
 */
namespace NovelRT::PluginManagement
{
    [[nodiscard]] std::shared_ptr<IGraphicsPluginProvider> GetVulkanPluginProvider() noexcept;
    [[nodiscard]] std::shared_ptr<IWindowingPluginProvider> GetGlfwPluginProvider() noexcept;
}

#endif // NOVELRT_PLUGINMANAGEMENT_TEMPORARYFNPTRS_H
