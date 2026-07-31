#include "Platform.h"

void Platform::Update(float dt) {
	if (m_scrollSpeed == 0.0f) {
		return;
	}

	m_transform.position.x -= m_scrollSpeed * dt;

	if (m_transform.position.x < -300.0f) {
		Destroy();
	}
}
