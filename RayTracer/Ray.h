#pragma once
#include "Vector3.h"

struct Ray {
	Ray() noexcept = default;
	Ray(const Ray&) noexcept = default;
	Ray& operator=(const Ray&) noexcept = default;
	Ray(const Vector3& origin, const Vector3& direction) noexcept : origin(origin), direction(direction) {}
	Vector3 distanceFromOrigin(float dist) const noexcept { return origin + direction * dist; }

	Vector3 origin;
	Vector3 direction;
};
