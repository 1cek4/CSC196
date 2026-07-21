#include "pch.h"
#include "Actor.h"
#include "Renderer.h"
#include "MathUtils.h"


using namespace nu;

namespace nu {

    void Actor::Update(float dt) {
        m_transform.position += (m_velocity * dt);
        m_velocity *= 0.997f;

        m_transform.position.x = Wrap(0.0f, 1920.0f, m_transform.position.x);
        m_transform.position.y = Wrap(0.0f, 1080.0f, m_transform.position.y);
    }

    void Actor::Draw(const Renderer& renderer) const {
        renderer.DrawModel(m_model, m_transform);
        
    }
}