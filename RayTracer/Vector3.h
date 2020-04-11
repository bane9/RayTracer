#pragma once

struct Vector3 {
	Vector3() noexcept = default;
	Vector3(const Vector3&) noexcept = default;
	Vector3& operator=(const Vector3&) noexcept = default;
	Vector3(float, float, float) noexcept;
	Vector3(float) noexcept;

	Vector3& operator+=(const Vector3&) noexcept;
	Vector3& operator+=(float) noexcept;
	Vector3& operator-=(const Vector3&) noexcept;
	Vector3& operator-=(float) noexcept;
	Vector3& operator*=(const Vector3&) noexcept;
	Vector3& operator*=(float) noexcept;
	Vector3& operator/=(const Vector3&) noexcept;
	Vector3& operator/=(float) noexcept;
	Vector3 operator-() const noexcept;

	float lenght() const noexcept;
	float squaredLength() const noexcept;
	Vector3 toUnitVector() const noexcept;

	friend Vector3 operator+(const Vector3&, const Vector3&) noexcept;
	friend Vector3 operator+(const Vector3&, float) noexcept;
	friend Vector3 operator-(const Vector3&, const Vector3&) noexcept;
	friend Vector3 operator-(const Vector3&, float) noexcept;
	friend Vector3 operator*(const Vector3&, const Vector3&) noexcept;
	friend Vector3 operator*(const Vector3&, float) noexcept;
	friend Vector3 operator/(const Vector3&, const Vector3&) noexcept;
	friend Vector3 operator/(const Vector3&, float) noexcept;
	friend Vector3 operator+(float, const Vector3&) noexcept;
	friend Vector3 operator-(float, const Vector3&) noexcept;
	friend Vector3 operator*(float, const Vector3&) noexcept;
	friend Vector3 operator/(float, const Vector3&) noexcept;

	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
};

inline float Vec3Dot(const Vector3& lhs, const Vector3& rhs) noexcept {
	return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

inline Vector3 Vec3Cross(const Vector3& lhs, const Vector3& rhs) noexcept {
	return Vector3(
		lhs.y * rhs.z - lhs.z * rhs.y,
		-(lhs.x * rhs.z - lhs.z * rhs.x),
		lhs.x * rhs.y - lhs.y * rhs.x
		);
}
