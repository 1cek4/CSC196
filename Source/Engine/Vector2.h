#pragma once
#include <cmath>
#include <cassert>
namespace nu {
	struct Vector2 {
		float x, y;

		Vector2() = default;
		Vector2(float x, float y) : x{ x }, y{ y } {}
		Vector2(float xy) : x{ xy }, y{ xy } {}

		float& operator [] (int index) { assert(index >= 0 && index < 2); return (&x)[index];}
		const float& operator [] (int index) const { assert(index >= 0 && index < 2); return (&x)[index];}

		bool operator == (const Vector2& v) const { return this->x == v.x && this->y == v.y;}
		bool operator != (const Vector2& v) const { return !(*this == v); }

		Vector2 operator + (float v) const { return Vector2(this->x + v, this->y + v); }
		Vector2 operator - (float v) const { return Vector2(this->x - v, this->y - v); }
		Vector2 operator * (float v) const { return Vector2(this->x * v, this->y * v); }
		Vector2 operator / (float v) const { return Vector2(this->x / v, this->y / v); }

		Vector2& operator += (float v) { this->x += v; this->y += v; return *this; }
		Vector2& operator -= (float v) { this->x -= v; this->y -= v; return *this; }
		Vector2& operator *= (float v) { this->x *= v; this->y *= v; return *this; }
		Vector2& operator /= (float v) { this->x /= v; this->y /= v; return *this; }

		Vector2 operator + (const Vector2& v) const { return Vector2(this->x + v.x, this->y + v.y); }
		Vector2 operator - (const Vector2& v) const { return Vector2(this->x - v.x, this->y - v.y); }
		Vector2 operator * (const Vector2& v) const { return Vector2(this->x * v.x, this->y * v.y); }
		Vector2 operator / (const Vector2& v) const { return Vector2(this->x / v.x, this->y / v.y); }

		Vector2& operator += (const Vector2& v) { this->x += v.x; this->y += v.y; return *this; }
		Vector2& operator -= (const Vector2& v) { this->x -= v.x; this->y -= v.y; return *this; }
		Vector2& operator *= (const Vector2& v) { this->x *= v.x; this->y *= v.y; return *this; }
		Vector2& operator /= (const Vector2& v) { this->x /= v.x; this->y /= v.y; return *this; }
		
		float Length() const { return sqrt(LengthSqr());}
		float LengthSqr() const { return (x * x) + (y * y);}

		Vector2 Normalized() const {
			return Vector2(x / Length(), y / Length());
		}

		float Dot(const Vector2& v) const { return (this->x * v.x) + (this->y * v.y);}

		float Angle() const { return atan2(this->y, this->x);}

		float AngleBetween(const Vector2& v) const {
			float lengths = this->Length() * v.Length();
			if (lengths == 0.0f) return 0.0f;
			float cosAngle = this->Dot(v) / lengths;
			if (cosAngle > 1.0f) cosAngle = 1.0f;
			if (cosAngle < -1.0f) cosAngle = -1.0f;
			return acos(cosAngle);
		}

		Vector2 Rotate(float radians) const {
			float cs = cos(radians);
			float sn = sin(radians);
			return Vector2(x * cs - y * sn, x * sn + y * cs);
		}
	};
};