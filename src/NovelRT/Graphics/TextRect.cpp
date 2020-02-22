// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <NovelRT.h>

namespace NovelRT::Graphics {
  void TextRect::drawObject() {
    for (auto& rect : _letterRects) {
      rect->executeObjectBehaviour();
    }
  }

  void TextRect::setColourConfig(const RGBAConfig& value) {
    _colourConfig = value;
    configureObjectBuffers();
  }

  void TextRect::configureObjectBuffers() {
    reloadText();
  }

  TextRect::TextRect(const Transform& transform,
    int layer,
    ShaderProgram shaderProgram,
    Camera* camera,
    std::shared_ptr<FontSet> fontSet,
    const RGBAConfig& colourConfig) :
    RenderObject(
      transform,
      layer,
      shaderProgram,
      camera),
    _text(""),
    _logger(Utilities::Misc::CONSOLE_LOG_GFX),
    _colourConfig(colourConfig),
    _fontSet(fontSet) {}

  std::string TextRect::getText() const {
    return _text;
  }
  void TextRect::setText(const std::string& value) {
    _text = value;
    auto difference = _text.length() - _letterRects.size();
    auto modifiedTransform = getTransform();
    modifiedTransform.setScale(Maths::GeoVector<float>(50, 50));
    for (size_t i = 0; i < difference; i++) {
      auto rect = std::make_unique<ImageRect>(
          modifiedTransform,
          getLayer(),
          _shaderProgram,
          _camera,
          _colourConfig);
      rect->setActive(getActive());
      _letterRects.push_back(std::move(rect));
    }

    if (_bufferInitialised) {
      reloadText();
    }
  }
  void TextRect::reloadText() {

    auto ttfOrigin = getTransform().getPosition();

    int i = 0;
    for (const char& c : getText()) {

      auto ch = _fontSet->getCharacterBasedonGLchar(c);

      auto currentWorldPosition = Maths::GeoVector<float>((ttfOrigin.getX() + ch.size.getX() / 2.0f) + ch.bearing.getX(),
        (ttfOrigin.getY() - (ch.bearing.getY() / 2.0f))
        + ((ch.size.getY() - ch.bearing.getY()) / 2.0f));

      auto& target = _letterRects.at(i++);
      target->setTexture(ch.texture);
      target->getTransform().setPosition(currentWorldPosition);
      target->getTransform().setScale(Maths::GeoVector<float>(static_cast<float>(ch.size.getX()), static_cast<float>(ch.size.getY())));
      target->setActive(true);
      ttfOrigin.setX(ttfOrigin.getX() + (ch.advance >> 6));
    }

    if (_letterRects.size() == static_cast<size_t>(i) + 1)
      return;

    auto beginIt = _letterRects.begin() + i;
    auto endIt = _letterRects.end();

    std::for_each(beginIt, endIt, [](const std::unique_ptr<ImageRect>& ptr) {
      ptr->setActive(false);
      });
  }

  void TextRect::setActive(bool value) {
    WorldObject::setActive(value);
    std::for_each(_letterRects.begin(), _letterRects.end(), [&value](auto& x){x->setActive(value);});
  }
}
