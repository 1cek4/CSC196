#pragma once
#include <cmath>
#include <cassert>
namespace nu {
	struct Vector3 {
		float x, y, z;

		Vector3() : x{ 0.0f }, y{ 0.0f }, z{ 0.0f } {};
		Vector3(float x, float y, float z) : x{ x }, y{ y }, z{ z } {}
		Vector3(float xyz) : x{ xyz }, y{ xyz }, z{ xyz } {}

		const float& operator [] (int index) const {
			assert(index >= 0 && index < 3);
			return (&x)[index];
		}

		float& operator [] (int index) {
			assert(index >= 0 && index < 3);
			return (&x)[index];
		}

		bool operator == (const Vector3& v) const { return this->x == v.x && this->y == v.y && this->z == v.z; }
		bool operator != (const Vector3& v) const { return !(*this == v); }

		Vector3 operator + (float v) const { return Vector3(this->x + v, this->y + v, this->z + v); }
		Vector3 operator - (float v) const { return Vector3(this->x - v, this->y - v, this->z - v); }
		Vector3 operator * (float v) const { return Vector3(this->x * v, this->y * v, this->z * v); }
		Vector3 operator / (float v) const { return Vector3(this->x / v, this->y / v, this->z / v); }

		Vector3& operator += (float v) { this->x += v; this->y += v; this->z += v; return *this; }
		Vector3& operator -= (float v) { this->x -= v; this->y -= v; this->z -= v; return *this; }
		Vector3& operator *= (float v) { this->x *= v; this->y *= v; this->z *= v; return *this; }
		Vector3& operator /= (float v) { this->x /= v; this->y /= v; this->z /= v; return *this; }

		Vector3 operator + (const Vector3& v) const { return Vector3(this->x + v.x, this->y + v.y, this->z + v.z); }
		Vector3 operator - (const Vector3& v) const { return Vector3(this->x - v.x, this->y - v.y, this->z - v.z); }
		Vector3 operator * (const Vector3& v) const { return Vector3(this->x * v.x, this->y * v.y, this->z * v.z); }
		Vector3 operator / (const Vector3& v) const { return Vector3(this->x / v.x, this->y / v.y, this->z / v.z); }

		Vector3& operator += (const Vector3& v) { this->x += v.x; this->y += v.y; this->z += v.z; return *this; }
		Vector3& operator -= (const Vector3& v) { this->x -= v.x; this->y -= v.y; this->z -= v.z; return *this; }
		Vector3& operator *= (const Vector3& v) { this->x *= v.x; this->y *= v.y; this->z *= v.z; return *this; }
		Vector3& operator /= (const Vector3& v) { this->x /= v.x; this->y /= v.y; this->z /= v.z; return *this; }

		float Length() const { return sqrt(LengthSqr()); }
		float LengthSqr() const { return (x * x) + (y * y) + (z * z); }


		Vector3 Normalized() const {
			
			return Vector3(x / Length(), y / Length(), z / Length());
		}

		float Dot(const Vector3& v) const { return (this->x * v.x) + (this->y * v.y) + (this->z * v.z); }
	};
};