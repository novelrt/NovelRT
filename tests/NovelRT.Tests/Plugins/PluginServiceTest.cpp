// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#include <gtest/gtest.h>
#include <NovelRT.h>

using namespace NovelRT::Plugins;

class PluginServiceTest : public testing::Test {
protected:
  std::filesystem::path _validAbsoluteJsonPath = NovelRT::Utilities::Misc::getExecutableDirPath() / "Resources" / "Plugins" / "testlibconf.json";
  std::filesystem::path _validRelativeJsonPath = "testlibconf.json";
  static inline PluginService _pluginService;

  std::filesystem::path _dummyAbsolutePath = _validAbsoluteJsonPath.parent_path() / "DummyFolder" / "testlibconf.json";
  std::filesystem::path _dummyRelativePath = std::filesystem::path("DummyFolder") / "testlibconf.json";
  
  static void SetUpTestCase() {
    _pluginService = PluginService();
  }
};

TEST_F(PluginServiceTest, tryGetPluginInfoReturnsTrueIfValidPluginJsonFoundWithRelativePath) {
  PluginInfo info;
  ASSERT_TRUE(_pluginService.tryGetPluginInfo(_validAbsoluteJsonPath, info));
  EXPECT_EQ(info.name(), "The Dank Plugin");
  EXPECT_EQ(info.kind(), PluginKind::GraphicsPipeline);
  EXPECT_EQ(info.location(), "DoTest");
  EXPECT_EQ(info.engineVersion(), "0.0.1");
  EXPECT_EQ(info.pluginInfoVersion(), "1");
}

TEST_F(PluginServiceTest, tryGetPluginInfoReturnsTrueIfValidPluginJsonFoundWithAbsolutePath) {
  PluginInfo info;
  ASSERT_TRUE(_pluginService.tryGetPluginInfo(_validAbsoluteJsonPath, info, false));
  EXPECT_EQ(info.name(), "The Dank Plugin");
  EXPECT_EQ(info.kind(), PluginKind::GraphicsPipeline);
  EXPECT_EQ(info.location(), "DoTest");
  EXPECT_EQ(info.engineVersion(), "0.0.1");
  EXPECT_EQ(info.pluginInfoVersion(), "1");
}

TEST_F(PluginServiceTest, getAllAvailablePluginInfoReturnsCollectionOfPluginInfoObjectsWithRelativeDefaultPathNonRecursive) {
  EXPECT_EQ(_pluginService.getAllAvailablePluginInfo(std::filesystem::path("Plugins"), true, false).size(), 1); //the path is the same as default C++ is just a meme sometimes
}

TEST_F(PluginServiceTest, getAllAvailablePluginInfoReturnsCollectionOfPluginInfoObjectsWithRelativeSpecifiedPathNonRecursive) {
  EXPECT_EQ(_pluginService.getAllAvailablePluginInfo(std::filesystem::path("Plugins") / "DummyFolder", true, false).size(), 1);
}

TEST_F(PluginServiceTest, getAllAvailablePluginInfoReturnsCollectionOfPluginInfoObjectsWithAbsolutePathNonRecursive) {
  auto parent = _validAbsoluteJsonPath.parent_path();
  std::filesystem::create_directory(parent / "DummyFolder");
  EXPECT_EQ(_pluginService.getAllAvailablePluginInfo(parent, false, false).size(), 1);
}

TEST_F(PluginServiceTest, getAllAvailablePluginInfoReturnsCollectionOfPluginInfoObjectsWithDefaultRelativePathRecursive) {
  EXPECT_EQ(_pluginService.getAllAvailablePluginInfo().size(), 2);
}

TEST_F(PluginServiceTest, getAllAvailablePluginInfoReturnsCollectionOfPluginInfoObjectsWithAbsolutePathRecursive) {
  auto parent = _dummyAbsolutePath.parent_path().parent_path(); //TODO: This is dumb
  EXPECT_EQ(_pluginService.getAllAvailablePluginInfo(parent, false).size(), 2);
}

TEST_F(PluginServiceTest, getAllAvailablePluginInfoReturnsCollectionOfPluginInfoObjectsWithSpecifiedRelativePathRecursive) {
  EXPECT_EQ(_pluginService.getAllAvailablePluginInfo(std::filesystem::path("Plugins") / "DummyFolder").size(), 1);
}

TEST_F(PluginServiceTest, createRenderingServiceReturnsPtr) {
  auto pluginPtr = _pluginService.createRenderingService(_pluginService.getAllAvailablePluginInfo().at(0));
  EXPECT_NE(pluginPtr, nullptr);
}

TEST_F(PluginServiceTest, createRenderingServiceReturnsWorkingPtr) {
  auto pluginPtr = _pluginService.createRenderingService(_pluginService.getAllAvailablePluginInfo().at(0));
  EXPECT_EQ(pluginPtr->initialiseRendering(), 0);
  auto fillRectPtr = pluginPtr->createBasicFillRect(NovelRT::Transform(), 0, NovelRT::Graphics::RGBAConfig(0, 0, 0, 0));
  EXPECT_EQ(fillRectPtr, nullptr);
  auto imageRectPtr = pluginPtr->createImageRect(NovelRT::Transform(), 0, NovelRT::Graphics::RGBAConfig(0, 0, 0, 0));
  EXPECT_EQ(imageRectPtr, nullptr);
  auto textRectPtr = pluginPtr->createTextRect(NovelRT::Transform(), 0, NovelRT::Graphics::RGBAConfig(0, 0, 0, 0), 0, "");
  EXPECT_EQ(textRectPtr, nullptr);
  auto cameraPtr = pluginPtr->getCamera();
  EXPECT_TRUE(cameraPtr.expired());

}