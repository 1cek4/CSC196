#pragma once

#include <SDL3/SDL.h>
#include <cstdint>
#include <vector>
#include "Vector2.h"

namespace nu {

    class Input {
    public:
        enum MouseButton {
            Left = 1,
            Middle = 2,
            Right = 3
        };

        bool Initialize();
        void Shutdown();

        void Update();

        bool GetButtonDown(MouseButton button) const { return (m_buttonStates & GetButtonBit(button)) != 0; }
        bool GetPrevButtonDown(MouseButton button) const { return (m_prevButtonStates & GetButtonBit(button)) != 0; }
        bool GetButtonPressed(MouseButton button) const { return GetButtonDown(button) && !GetPrevButtonDown(button); }
        bool GetButtonReleased(MouseButton button) const { return !GetButtonDown(button) && GetPrevButtonDown(button); }

        Vector2 GetMousePosition() const { return Vector2(m_mouseX, m_mouseY); }

        bool GetKeyDown(SDL_Scancode key) const;
        bool GetPrevKeyDown(SDL_Scancode key) const;
        bool GetKeyPressed(SDL_Scancode key) const { return GetKeyDown(key) && !GetPrevKeyDown(key); }
        bool GetKeyReleased(SDL_Scancode key) const { return !GetKeyDown(key) && GetPrevKeyDown(key); }

    private:
        uint32_t GetButtonBit(MouseButton button) const;

        uint32_t m_buttonStates = 0;
        uint32_t m_prevButtonStates = 0;
        float m_mouseX = 0.0f;
        float m_mouseY = 0.0f;

        std::vector<Uint8> m_curKeyStates;
        std::vector<Uint8> m_prevKeyStates;
        int m_numKeys = 0;
    };

}