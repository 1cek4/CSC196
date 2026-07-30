#include "pch.h"
#include "Input.h"

#include <SDL3/SDL.h>

namespace nu {

    bool Input::Initialize()
    {
        int numkeys;
        const bool* keyState = SDL_GetKeyboardState(&numkeys);

        if (keyState == nullptr) {
            return false;
        }

        m_curKeyStates.resize(numkeys);
        std::copy(keyState, keyState + numkeys, m_curKeyStates.begin());
        m_prevKeyStates = m_curKeyStates;

        return true;
    }


    void Input::Shutdown()
    {
    }

    void Input::Update() {
        m_prevButtonStates = m_buttonStates;
        m_buttonStates = SDL_GetMouseState(&m_mouseX, &m_mouseY);

        m_prevKeyStates = m_curKeyStates;
        const bool* state = SDL_GetKeyboardState(&m_numKeys);
        m_curKeyStates.assign(state, state + m_numKeys);
    }

    bool Input::GetKeyDown(SDL_Scancode key) const {
        return (size_t)key < m_curKeyStates.size() && m_curKeyStates[key] != 0;
    }

    bool Input::GetPrevKeyDown(SDL_Scancode key) const {
        return (size_t)key < m_prevKeyStates.size() && m_prevKeyStates[key] != 0;
    }

    uint32_t Input::GetButtonBit(MouseButton button) const {
        return (1u << (button - 1));
    }


}