#pragma once
#include "Ray.h"
#include "Hitable.h"
#include "Vector3.h"
#include "Ray.h"
#include "AdditionalFunctions.h"
#include <algorithm>

class Material {
public:
	virtual bool scatter(const Ray& rayIn, const HitRecord& hitRecord, Vector3& attenuation, Ray& rayOut) const noexcept = 0;
};

class Metal : public Material
{
public:
	Metal() noexcept = default;
	Metal(const Vector3& albedo, float fuzz = 0.0f) noexcept : albedo(albedo), fuzz(std::clamp(fuzz, 0.0f, 1.0f)) {}
	virtual bool scatter(const Ray& rayIn, const HitRecord& hitRecord, Vector3& attenuation, Ray& rayOut) const noexcept override
	{
		Vector3 reflected = Reflect(rayIn.direction.toUnitVector(), hitRecord.normal);
		rayOut = Ray(hitRecord.p, reflected + fuzz * RandomUnitInSphere());
		attenuation = albedo;
		return Vec3Dot(reflected, hitRecord.normal) > 0.0f;
	}

	Vector3 albedo;
	float fuzz;
};

class Lambertian : public Material
{
public:
	Lambertian() noexcept = default;
	Lambertian(const Vector3& albedo) noexcept : albedo(albedo) {}
	virtual bool scatter(const Ray& rayIn, const HitRecord& hitRecord, Vector3& attenuation, Ray& rayOut) const noexcept override
	{
		Vector3 target = hitRecord.p + hitRecord.normal + RandomUnitInSphere();
		rayOut = Ray(hitRecord.p, target - hitRecord.p);
		attenuation = albedo;
		return true;
	}

	Vector3 albedo;
};

class Dielectric : public Material
{
public:
	Dielectric() noexcept = default;
	Dielectric(float refId) noexcept : refId(refId) {}
	virtual bool scatter(const Ray& rayIn, const HitRecord& hitRecord, Vector3& attenuation, Ray& rayOut) const noexcept override
	{
		Vector3 outwardNormal;
		Vector3 reflected = Reflect(rayIn.direction, hitRecord.normal);
		float nOverT;
		attenuation = Vector3(1.0f, 1.0f, 1.0f);
		Vector3 refracted;
		float cos;
		float reflectProb;
		if (Vec3Dot(rayIn.direction, hitRecord.normal) > 0) {
			outwardNormal = -hitRecord.normal;
			nOverT = refId;
			cos = refId * Vec3Dot(rayIn.direction, hitRecord.normal) / rayIn.direction.lenght();
		}
		else {
			outwardNormal = hitRecord.normal;
			nOverT = 1.0f / refId;
			cos = -Vec3Dot(rayIn.direction, hitRecord.normal) / rayIn.direction.lenght();
		}
		if (Refract(rayIn.direction, outwardNormal, nOverT, refracted)) reflectProb = Schlik(cos, refId);
		else reflectProb = 1.0f;
		if (RandomReal() < reflectProb) rayOut = Ray(hitRecord.p, reflected);
		else rayOut = Ray(hitRecord.p, refracted);
		return true;
	}

	float refId;
};

