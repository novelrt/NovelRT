// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_UI_IUIELEMENT_H
#define NOVELRT_UI_IUIELEMENT_H

#ifndef NOVELRT_UI_H
#error NovelRT does not support including types explicitly by default. Please include UI.h instead for the Windowing namespace subset.
#endif

namespace NovelRT::UI
{
    class IUIElement : public std::enable_shared_from_this<IUIElement>
    {
    protected:
        std::string _identifier;
        UIElementState _state;

    public:
        virtual void Render() = 0;

        [[nodiscard]] inline std::string& Identifier()
        {
            return _identifier;
        }

        [[nodiscard]] inline const std::string& Identifier() const
        {
            return _identifier;
        }

        [[nodiscard]] inline UIElementState& State()
        {
            return _state;
        }

        [[nodiscard]] inline const UIElementState& State() const
        {
            return _state;
        }
    };
}

#endif // NOVELRT_UI_IUIELEMENT_H
