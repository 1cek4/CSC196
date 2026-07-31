#include "Hazard.h"

void Hazard::Update(float dt) {
	m_transform.position.x -= m_scrollSpeed * dt;

	if (m_transform.position.x < -100.0f) {
		Destroy();
	}
}
