// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#include <gtest/gtest.h>
#include <NovelRT.h>

using namespace NovelRT::Plugins;

class PluginServiceTest : public testing::Test {
protected:
  std::filesystem::path _validAbsoluteJsonPath = NovelRT::Utilities::Misc::getExecutableDirPath() / "Resources" / "Plugins" / "validJson.json";
  std::filesystem::path _validRelativeJsonPath = "validJson.json";
  PluginService _pluginService;

  void SetUp() override {
    std::ofstream validJsonFile;
    validJsonFile.open(_validAbsoluteJsonPath);
    validJsonFile << "{\"name\":\"The Dank Plugin\",\"kind\":2,\"location\":\"DankDll.dll\",\"engineVersion\":\"0.0.1\",\"pluginInfoVersion\":1}" << std::endl;
    validJsonFile.close();
  }

  void TearDown() override {
    std::filesystem::remove(_validAbsoluteJsonPath);
  }
};

TEST_F(PluginServiceTest, tryGetPluginInfoReturnsTrueIfValidPluginJsonFoundWithRelativePath) {
  PluginInfo info;
  ASSERT_TRUE(_pluginService.tryGetPluginInfo(_validAbsoluteJsonPath, info));
  EXPECT_EQ(info.name(), "The Dank Plugin");
  EXPECT_EQ(info.kind(), PluginKind::WindowingSystem);
  EXPECT_EQ(info.location(), "DankDll.dll");
  EXPECT_EQ(info.engineVersion(), "0.0.1");
  EXPECT_EQ(info.pluginInfoVersion(), "1");
}

TEST_F(PluginServiceTest, tryGetPluginInfoReturnsTrueIfValidPluginJsonFoundWithAbsolutePath) {
  PluginInfo info;
  ASSERT_TRUE(_pluginService.tryGetPluginInfo(_validAbsoluteJsonPath, info, false));
  EXPECT_EQ(info.name(), "The Dank Plugin");
  EXPECT_EQ(info.kind(), PluginKind::WindowingSystem);
  EXPECT_EQ(info.location(), "DankDll.dll");
  EXPECT_EQ(info.engineVersion(), "0.0.1");
  EXPECT_EQ(info.pluginInfoVersion(), "1");
}

TEST_F(PluginServiceTest, getAllAvailablePluginInfoReturnsCollectionOfPluginInfoObjectsWithRelativeDefaultPath) {
  auto parent = _validAbsoluteJsonPath.parent_path();
  for (size_t i = 0; i < 5; i++)
  {
    std::filesystem::copy(_validAbsoluteJsonPath, parent / (std::to_string(i) + ".json"));
  }

  EXPECT_EQ(_pluginService.getAllAvailablePluginInfo().size(), 6);

  for (size_t i = 0; i < 5; i++)
  {
    std::filesystem::remove(parent / (std::to_string(i) + ".json"));
  }
}

TEST_F(PluginServiceTest, getAllAvailablePluginInfoReturnsCollectionOfPluginInfoObjectsWithRelativeSpecifiedPath) {
  auto parent = _validAbsoluteJsonPath.parent_path();
  std::filesystem::create_directory(parent / "DummyFolder");

  for (size_t i = 0; i < 5; i++)
  {
    std::filesystem::copy(_validAbsoluteJsonPath, parent / "DummyFolder" / (std::to_string(i) + ".json"));
  }

  EXPECT_EQ(_pluginService.getAllAvailablePluginInfo(std::filesystem::path("Plugins") / "DummyFolder").size(), 5);

  for (size_t i = 0; i < 5; i++)
  {
    std::filesystem::remove(parent / "DummyFolder" / (std::to_string(i) + ".json"));
  }

  std::filesystem::remove(parent / "DummyFolder");
}

TEST_F(PluginServiceTest, getAllAvailablePluginInfoReturnsCollectionOfPluginInfoObjectsWithAbsolutePath) {
  auto parent = _validAbsoluteJsonPath.parent_path();
  std::filesystem::create_directory(parent / "DummyFolder");

  for (size_t i = 0; i < 5; i++)
  {
    std::filesystem::copy(_validAbsoluteJsonPath, parent / "DummyFolder" / (std::to_string(i) + ".json"));
  }

  EXPECT_EQ(_pluginService.getAllAvailablePluginInfo(parent / "DummyFolder", false).size(), 5);

  for (size_t i = 0; i < 5; i++)
  {
    std::filesystem::remove(parent / "DummyFolder" / (std::to_string(i) + ".json"));
  }

  std::filesystem::remove(parent / "DummyFolder");
}

TEST_F(PluginServiceTest, getAllAvailablePluginInfoReturnsCollectionOfPluginInfoObjectsWithDefaultRelativePathRecursive) {
  auto parent = _validAbsoluteJsonPath.parent_path();
  std::filesystem::create_directory(parent / "DummyFolder");

  for (size_t i = 0; i < 5; i++)
  {
    std::filesystem::copy(_validAbsoluteJsonPath, parent / "DummyFolder" / (std::to_string(i) + ".json"));
  }

  EXPECT_EQ(_pluginService.getAllAvailablePluginInfo().size(), 6);

  for (size_t i = 0; i < 5; i++)
  {
    std::filesystem::remove(parent / "DummyFolder" / (std::to_string(i) + ".json"));
  }

  std::filesystem::remove(parent / "DummyFolder");
}

TEST_F(PluginServiceTest, getAllAvailablePluginInfoReturnsCollectionOfPluginInfoObjectsWithAbsolutePathRecursive) {
  auto parent = _validAbsoluteJsonPath.parent_path();
  std::filesystem::create_directory(parent / "DummyFolder");
  std::filesystem::create_directory(parent / "DummyFolder" / "AnotherDummyFolder");

  for (size_t i = 0; i < 5; i++)
  {
    std::filesystem::copy(_validAbsoluteJsonPath, parent / "DummyFolder" / "AnotherDummyFolder" / (std::to_string(i) + ".json"));
  }

  EXPECT_EQ(_pluginService.getAllAvailablePluginInfo(parent / "DummyFolder", false).size(), 5);

  for (size_t i = 0; i < 5; i++)
  {
    std::filesystem::remove(parent / "DummyFolder" / "AnotherDummyFolder" / (std::to_string(i) + ".json"));
  }

  std::filesystem::remove(parent / "DummyFolder" / "AnotherDummyFolder");
  std::filesystem::remove(parent / "DummyFolder");
}

TEST_F(PluginServiceTest, getAllAvailablePluginInfoReturnsCollectionOfPluginInfoObjectsWithSpecifiedRelativePathRecursive) {
  auto parent = _validAbsoluteJsonPath.parent_path();
  std::filesystem::create_directory(parent / "DummyFolder");
  std::filesystem::create_directory(parent / "DummyFolder" / "AnotherDummyFolder");

  for (size_t i = 0; i < 5; i++)
  {
    std::filesystem::copy(_validAbsoluteJsonPath, parent / "DummyFolder" / "AnotherDummyFolder" / (std::to_string(i) + ".json"));
  }

  EXPECT_EQ(_pluginService.getAllAvailablePluginInfo(std::filesystem::path("Plugins") / "DummyFolder").size(), 5);

  for (size_t i = 0; i < 5; i++)
  {
    std::filesystem::remove(parent / "DummyFolder" / "AnotherDummyFolder" / (std::to_string(i) + ".json"));
  }

  std::filesystem::remove(parent / "DummyFolder" / "AnotherDummyFolder");
  std::filesystem::remove(parent / "DummyFolder");
}


