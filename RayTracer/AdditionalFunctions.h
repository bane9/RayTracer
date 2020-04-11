#pragma once
#include "Vector3.h"
#include "Ray.h"
#include <random>

inline constexpr double PI = 3.14159265358979323846;

inline float RandomReal() noexcept {
	static std::random_device rd;
	static std::mt19937 gen{ rd() };
	static std::uniform_real_distribution<> dis{ 0.0, 1.0 };
	return dis(gen);
}

inline Vector3 RandomUnitInSphere() noexcept {
	Vector3 p;
	do {
		p = 2.0f * Vector3(RandomReal(), RandomReal(), RandomReal()) - Vector3(1.0f);
	} while (p.squaredLength() >= 1.0f);
	return p;
}

inline Vector3 Reflect(const Vector3& v, const Vector3& n) noexcept {
	return v - 2.0f * Vec3Dot(v, n) * n;
}

inline bool Refract(const Vector3& v, const Vector3& n, float nOverT, Vector3& refracted) noexcept {
	Vector3 uv = v.toUnitVector();
	float dt = Vec3Dot(uv, n);
	float discriminant = 1.0f - nOverT * nOverT * (1.0f - dt * dt);
	if (discriminant > 0.0f) {
		refracted = nOverT * (uv - n * dt) - n * sqrtf(discriminant);
		return true;
	}
	else return false;
}

inline float Schlik(float cos, float refId) noexcept {
	float r0 = (1.0f - refId) / (1.0f + refId);
	r0 *= r0;
	return r0 + (1.0f - r0) * powf((1.0f - cos), 5.0f);
}

inline Vector3 RandomUnitInDisk() noexcept {
	Vector3 p;
	do {
		p = 2.0f * Vector3(RandomReal(), RandomReal(), 0.0f) - Vector3(1.0f, 1.0f, 0.0f);
	} while (Vec3Dot(p, p) >= 1.0f);
	return p;
}
