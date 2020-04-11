#include "Vector3.h"
#include <math.h>

Vector3::Vector3(float x, float y, float z) noexcept
	: x(x), y(y), z(z)
{
}

Vector3::Vector3(float n) noexcept
	: x(n), y(n), z(n)
{
}

Vector3& Vector3::operator+=(const Vector3& rhs) noexcept
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	return *this;
}

Vector3& Vector3::operator+=(float n) noexcept
{
	x += n;
	y += n;
	z += n;
	return *this;
}

Vector3& Vector3::operator-=(const Vector3& rhs) noexcept
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	return *this;
}

Vector3& Vector3::operator-=(float n) noexcept
{
	x -= n;
	y -= n;
	z -= n;
	return *this;
}

Vector3& Vector3::operator*=(const Vector3& rhs) noexcept
{
	x *= rhs.x;
	y *= rhs.y;
	z *= rhs.z;
	return *this;
}

Vector3& Vector3::operator*=(float n) noexcept
{
	x *= n;
	y *= n;
	z *= n;
	return *this;
}

Vector3& Vector3::operator/=(const Vector3& rhs) noexcept
{
	x /= rhs.x;
	y /= rhs.y;
	z /= rhs.z;
	return *this;
}

Vector3& Vector3::operator/=(float n) noexcept
{
	x /= n;
	y /= n;
	z /= n;
	return *this;
}

Vector3 Vector3::operator-() const noexcept
{
	return Vector3(-x, -y, -z);
}

float Vector3::lenght() const noexcept
{
	return sqrtf(squaredLength());
}

float Vector3::squaredLength() const noexcept
{
	return x * x + y * y + z * z;
}

Vector3 Vector3::toUnitVector() const noexcept
{
	return Vector3(*this) *= (1.0f / lenght());
}

Vector3 operator+(float n, const Vector3& rhs) noexcept
{
	return Vector3(rhs) += n;
}

Vector3 operator-(float n, const Vector3& rhs) noexcept
{
	return {n - rhs.x, n - rhs.y, n - rhs.z};
}

Vector3 operator*(float n, const Vector3& rhs) noexcept
{
	return Vector3(rhs) *= n;
}

Vector3 operator/(float n, const Vector3& rhs) noexcept
{
	return { n / rhs.x, n / rhs.y, n / rhs.z };
}

Vector3 operator+(const Vector3& lhs, const Vector3& rhs) noexcept
{
	return Vector3(lhs) += rhs;
}

Vector3 operator+(const Vector3& lhs, float n) noexcept
{
	return Vector3(lhs) += n;
}

Vector3 operator-(const Vector3& lhs, const Vector3& rhs) noexcept
{
	return Vector3(lhs) -= rhs;
}

Vector3 operator-(const Vector3& lhs, float n) noexcept
{
	return Vector3(lhs) -= n;
}

Vector3 operator*(const Vector3& lhs, const Vector3& rhs) noexcept
{
	return Vector3(lhs) *= rhs;
}

Vector3 operator*(const Vector3& lhs, float n) noexcept
{
	return Vector3(lhs) *= n;
}

Vector3 operator/(const Vector3& lhs, const Vector3& rhs) noexcept
{
	return Vector3(lhs) /= rhs;
}

Vector3 operator/(const Vector3& lhs, float n) noexcept
{
	return Vector3(lhs) /= n;
}
