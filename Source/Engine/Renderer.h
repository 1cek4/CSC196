#pragma once
#ifndef RENDERER_H
#define RENDERER_H

#include <SDL3/SDL.h>
#include <string>

namespace nu {
    class Mesh;
    struct Transform;
    class Model;
    class Renderer {
    public:
        bool Initialize(const char* name, int width, int height);
        void Shutdown();

        void Clear() const;
        void Present() const;

        void SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255) const;

        void DrawPoint(float x, float y) const;
        void DrawFillRect(float x, float y, float w, float h) const;
        void DrawRect(float x, float y, float w, float h) const;
        void DrawLine(float x1, float y1, float x2, float y2) const;

        void DrawMesh(const Mesh& mesh, const Transform& transform) const;
        void DrawModel(const Model& model, const Transform& transform) const;
        
        int GetHeight() const { return m_height; }
        int GetWidth() const { return m_width; }

        bool IsValid() const { return m_window != nullptr && m_renderer != nullptr; }

    private:
        SDL_Window* m_window = nullptr;
        SDL_Renderer* m_renderer = nullptr;

		int m_width = 0;
		int m_height = 0;

    };
}

#endif

