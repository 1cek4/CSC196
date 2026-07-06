#pragma once
#ifndef RENDERER_H
#define RENDERER_H

#include <SDL3/SDL.h>
#include <string>

class Renderer {
public:
    Renderer(const std::string& title, int width, int height);
    ~Renderer();

    void Clear();
    void SetDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    void DrawLine(float x1, float y1, float x2, float y2);
    void DrawPoint(float x, float y);
    void DrawRect(float x, float y, float w, float h);
    void Present();

    bool IsValid() const { return m_window != nullptr && m_renderer != nullptr; }

private:
    SDL_Window* m_window = nullptr;
    SDL_Renderer* m_renderer = nullptr;
};

#endif

