#include "Input.h"

namespace nu {

    Input::Input() {
        const bool* state = SDL_GetKeyboardState(&m_numKeys);
        m_curKeyStates.assign(state, state + m_numKeys);
        m_prevKeyStates = m_curKeyStates;
    }

    uint32_t Input::GetButtonBit(MouseButton button) const {
        return SDL_BUTTON_MASK((uint32_t)button);
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

}