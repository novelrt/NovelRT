// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository
// root for more information.

#include <NovelRT/NovelRT.h>

using namespace NovelRT::Ecs;
using namespace NovelRT::Input;
using namespace NovelRT::PluginManagement;
using namespace NovelRT::Persistence;

NovelRT::Utilities::Event<NovelRT::Timing::Timestamp> DummyUpdateStuff;

int main()
{
    struct TestStruct
    {
        int32_t value;
        int32_t multiplier;
        EntityId testEntityValue;
        bool shouldDelete;

        TestStruct& operator+=(const TestStruct& rhs)
        {
            value = rhs.value;
            multiplier = rhs.multiplier;
            testEntityValue = rhs.testEntityValue;
            shouldDelete = rhs.shouldDelete;

            return *this;
        }

        bool operator==(const TestStruct& rhs)
        {
            return value == rhs.value && multiplier == rhs.multiplier && testEntityValue == rhs.testEntityValue &&
                   shouldDelete == rhs.shouldDelete;
        }
    };

    class TestStructSerialisationRule final : public NovelRT::Persistence::ICustomSerialisationRule
    {
    private:
        struct CopyStruct
        {
            int32_t value;
            int32_t multiplier;
            EntityId testEntityValue;
        };

    public:
        size_t GetSerialisedSize() const noexcept final
        {
            return sizeof(CopyStruct);
        }

        std::vector<uint8_t> ExecuteSerialiseModification(gsl::span<const uint8_t> component) const noexcept final
        {
            TestStruct componentStruct = *reinterpret_cast<const TestStruct*>(component.data());

            std::vector<uint8_t> data{};
            data.resize(GetSerialisedSize());
            auto dataPtr = reinterpret_cast<CopyStruct*>(data.data());
            dataPtr->value = componentStruct.value;
            dataPtr->multiplier = componentStruct.multiplier;
            dataPtr->testEntityValue = componentStruct.testEntityValue;

            return data;
        }

        std::vector<uint8_t> ExecuteDeserialiseModification(gsl::span<const uint8_t> component) const noexcept final
        {
            auto dataPtr = reinterpret_cast<const CopyStruct*>(component.data());

            TestStruct newData{};
            std::vector<uint8_t> structData{};
            structData.resize(sizeof(TestStruct));
            newData.value = dataPtr->value;
            newData.multiplier = dataPtr->multiplier;
            newData.testEntityValue = dataPtr->testEntityValue;
            newData.shouldDelete = false;
            *reinterpret_cast<TestStruct*>(structData.data()) = newData;

            return structData;
        }
    };

    class TestStructComponentLoadRule : public ICustomComponentLoadRule
    {
    public:
        void ExecuteComponentLoadModification(const SparseSet<EntityId, EntityId>& localToGlobalEntityMap,
                                              void* componentDataHandle) override
        {
            auto componentPtr = reinterpret_cast<TestStruct*>(componentDataHandle);

            if (localToGlobalEntityMap.ContainsKey(componentPtr->testEntityValue))
            {
                componentPtr->testEntityValue = localToGlobalEntityMap[componentPtr->testEntityValue];
            }
        }
    };

    NovelRT::Persistence::Persistable::GetSerialisationRules().emplace(
        "TestStruct", std::unique_ptr<ICustomSerialisationRule>(new TestStructSerialisationRule()));

    NovelRT::Persistence::Persistable::GetComponentLoadRules().emplace(
        "TestStruct", std::unique_ptr<ICustomComponentLoadRule>(new TestStructComponentLoadRule()));

    NovelRT::LoggingService logger = NovelRT::LoggingService();
    logger.setLogLevel(NovelRT::LogLevel::Info);

#if NOVELRT_MOLTENVK_VENDORED
    auto icdPath = NovelRT::Utilities::Misc::getExecutablePath() / "MoltenVK_icd.json";
    setenv("VK_ICD_FILENAMES", icdPath.c_str(), 0);
    logger.logInfo("macOS detected - setting VK_ICD_FILENAMES to path: {}", icdPath.c_str());
#endif

    DefaultPluginSelector selector;
    auto windowingProvider = selector.GetDefaultPluginTypeOnCurrentPlatformFor<IWindowingPluginProvider>();
    auto inputProvider = selector.GetDefaultPluginTypeOnCurrentPlatformFor<IInputPluginProvider>();
    auto resourceManagementProvider =
        selector.GetDefaultPluginTypeOnCurrentPlatformFor<IResourceManagementPluginProvider>();

    auto scheduler =
        Configurator()
            .WithDefaultSystemsAndComponents()
            .WithPluginProvider(selector.GetDefaultPluginTypeOnCurrentPlatformFor<IGraphicsPluginProvider>())
            .WithPluginProvider(windowingProvider)
            .WithPluginProvider(inputProvider)
            .WithPluginProvider(resourceManagementProvider)
            .InitialiseAndRegisterComponents<TestStruct>(std::make_tuple(TestStruct{0, 0, 0, true}, "TestStruct"));

    std::shared_ptr<NovelRT::Ecs::Graphics::DefaultRenderingSystem> renderingSystem =
        scheduler.GetRegisteredIEcsSystemAs<NovelRT::Ecs::Graphics::DefaultRenderingSystem>();

    NovelRT::Persistence::Persistable::LoadDefaultRules(renderingSystem);

    NovelRT::Threading::FutureResult<NovelRT::Ecs::Graphics::TextureInfo> textureFuture =
        renderingSystem->GetOrLoadTexture("novel-chan");

    renderingSystem->ForceVertexTextureFutureResolution();

    auto transformBuffer = scheduler.GetComponentCache().GetComponentBuffer<TransformComponent>();
    auto entityGraphBuffer = scheduler.GetComponentCache().GetComponentBuffer<EntityGraphComponent>();
    auto testStructBuffer = scheduler.GetComponentCache().GetComponentBuffer<TestStruct>();

    EntityId parentEntity =
        renderingSystem->CreateSpriteEntityOutsideOfSystem(textureFuture.GetBackingConcurrentSharedPtr(), scheduler);

    EntityId childEntity =
        renderingSystem->CreateSpriteEntityOutsideOfSystem(textureFuture.GetBackingConcurrentSharedPtr(), scheduler);

    EntityId childOfChildEntity =
        renderingSystem->CreateSpriteEntityOutsideOfSystem(textureFuture.GetBackingConcurrentSharedPtr(), scheduler);

    transformBuffer.PushComponentUpdateInstruction(
        0, childEntity,
        TransformComponent{NovelRT::Maths::GeoVector3F(200, 200, 0), NovelRT::Maths::GeoVector2F::zero(), 0});
    transformBuffer.PushComponentUpdateInstruction(
        0, childOfChildEntity,
        TransformComponent{NovelRT::Maths::GeoVector3F(200, 200, 0), NovelRT::Maths::GeoVector2F::zero(), 0});
    entityGraphBuffer.PushComponentUpdateInstruction(0, childEntity, EntityGraphComponent{true, parentEntity, 0});
    entityGraphBuffer.PushComponentUpdateInstruction(0, childOfChildEntity, EntityGraphComponent{true, childEntity, 0});

    testStructBuffer.PushComponentUpdateInstruction(0, parentEntity, TestStruct{2, 2, 5, false});
    testStructBuffer.PushComponentUpdateInstruction(0, childEntity, TestStruct{3, 5, 10, false});
    testStructBuffer.PushComponentUpdateInstruction(0, childOfChildEntity, TestStruct{4, 10, 15, false});

    auto& entityCache = scheduler.GetEntityCache();
    entityCache.AddEntity(0, 5);
    entityCache.AddEntity(0, 10);
    entityCache.AddEntity(0, 15);

    NovelRT::Timing::Timestamp secondsPassed(0);
    Chapter chapterToLoad;
    bool fileSaved = false;

    scheduler.RegisterSystem([&](auto delta, auto catalogue) {
        secondsPassed += delta;

        if (secondsPassed >= NovelRT::Timing::Timestamp::fromSeconds(3))
        {
            fileSaved = false;
            secondsPassed = NovelRT::Timing::Timestamp(0);
            chapterToLoad.LoadFileData(
                resourceManagementProvider->GetResourceLoader()->LoadPackage("MyChapter.chapter"));
            // chapterToLoad.ToEcsInstance(scheduler.GetComponentCache(), scheduler.GetEntityCache()); //IF YOU WANT TO
            // SEE THE FILE SIZE GROW
            // FOREVER, UNCOMMENT THIS!
        }
        else if (secondsPassed >= NovelRT::Timing::Timestamp::fromSeconds(1.5f) && !fileSaved)
        {
            fileSaved = true;
            chapterToLoad = Chapter::FromEcsInstance(scheduler.GetComponentCache());
            resourceManagementProvider->GetResourceLoader()->SavePackage("MyChapter.chapter",
                                                                         chapterToLoad.ToFileData());
        }
        else
        {
            ComponentView<TransformComponent> transforms = catalogue.template GetComponentView<TransformComponent>();
            for (auto [entity, transform] : transforms)
            {
                TransformComponent newComponent{};
                newComponent.scale = NovelRT::Maths::GeoVector2F::zero();
                newComponent.rotationInRadians =
                    NovelRT::Maths::Utilities::DegreesToRadians(20 * delta.getSecondsFloat());
                newComponent.scale = NovelRT::Maths::GeoVector2F::zero();
                transforms.PushComponentUpdateInstruction(entity, newComponent);
            }
        }
    });

    entityCache.ProcessEntityRegistrationRequestsFromThreads();
    scheduler.GetComponentCache().PrepAllBuffersForNextFrame(std::vector<EntityId>{});

    NovelRT::Timing::StepTimer timer;

    auto windowPtr = windowingProvider->GetWindowingDevice();
    windowPtr->SetWindowTitle("Persistence Test");

    std::shared_ptr<NovelRT::Ecs::Input::InputSystem> inputSystem =
        scheduler.GetRegisteredIEcsSystemAs<NovelRT::Ecs::Input::InputSystem>();

    DummyUpdateStuff += [&](auto delta) { scheduler.ExecuteIteration(delta); };

    while (!windowPtr->GetShouldClose())
    {
        windowPtr->ProcessAllMessages();
        timer.tick(DummyUpdateStuff);
    }

    return 0;
}
