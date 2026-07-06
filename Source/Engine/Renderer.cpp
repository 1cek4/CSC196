#include "Renderer.h"
#include <iostream>

Renderer::Renderer(const std::string& title, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return;
    }

    m_window = SDL_CreateWindow(title.c_str(), width, height, 0);
    if (!m_window) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        return;
    }

    m_renderer = SDL_CreateRenderer(m_window, NULL);
    if (!m_renderer) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
    }
}

Renderer::~Renderer() {
    if (m_renderer) SDL_DestroyRenderer(m_renderer);
    if (m_window) SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void Renderer::Present() {
    SDL_RenderPresent(m_renderer);
}

void Renderer::DrawLine(float x1, float y1, float x2, float y2) {
    SDL_RenderLine(m_renderer, x1, y1, x2, y2);
}

void Renderer::DrawPoint(float x, float y) {
    SDL_RenderPoint(m_renderer, x, y);
}

void Renderer::DrawRect(float x, float y, float w, float h) {
    SDL_FRect rect{ x, y, w, h };
    SDL_RenderFillRect(m_renderer, &rect);
}

void Renderer::Clear() {
    SDL_RenderClear(m_renderer);
}

void Renderer::SetDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    SDL_SetRenderDrawColor(m_renderer, r, g, b, a);
}


