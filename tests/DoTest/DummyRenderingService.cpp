#include "DummyRenderingServiceFactory.h"

using namespace NovelRT;

    int DummyRenderingService::initialiseRendering() {
        return 0;

    };

    void DummyRenderingService::tearDown() {
        std::cout << "tear down called" << std::endl;
    };

    std::unique_ptr<Graphics::ImageRect> DummyRenderingService::createImageRect(const Transform& transform, int layer, const std::string& filePath, const Graphics::RGBAConfig& colourTint) {
        return nullptr;
    };

    std::unique_ptr<Graphics::ImageRect> DummyRenderingService::createImageRect(const Transform& transform, int layer, const Graphics::RGBAConfig& colourTint) {
        return nullptr;
    };

    std::unique_ptr<Graphics::BasicFillRect> DummyRenderingService::createBasicFillRect(const Transform& transform, int layer, const Graphics::RGBAConfig& colourConfig) {
        return nullptr;
    };

    std::unique_ptr<Graphics::TextRect> DummyRenderingService::createTextRect(const Transform& transform, int layer, const Graphics::RGBAConfig& colourConfig, float fontSize, const std::string& fontFilePath) {
       return nullptr;
    };

    std::weak_ptr<Graphics::Camera> DummyRenderingService::getCamera() const {
       return std::weak_ptr(_camera);
    };

    void DummyRenderingService::beginFrame() const {
       std::cout << "begin frame called" << std::endl;
    };

    void DummyRenderingService::endFrame() const {
       std::cout << "end frame called" << std::endl;
    };

    void DummyRenderingService::setBackgroundColour(const Graphics::RGBAConfig& colour) {
        std::cout << "Colour Received: " << colour.getR() << " " << colour.getG() << " " << colour.getB() << " " << colour.getA() << std:: endl;
    };

    std::shared_ptr<Graphics::Texture> DummyRenderingService::getTexture(const std::string& fileTarget) {
        return nullptr;
    };

    std::shared_ptr<Graphics::FontSet> DummyRenderingService::getFontSet(const std::string& fileTarget, float fontSize) {
        return nullptr;
    }; 