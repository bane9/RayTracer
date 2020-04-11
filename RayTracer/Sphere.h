#pragma once
#include "Hitable.h"
#include <math.h>
#include "Material.h"

class Sphere : public Hitable 
{
public:
	Sphere() noexcept = default;
	Sphere(const Sphere&) noexcept = default;
	Sphere& operator=(const Sphere&) noexcept = default;
	Sphere(const Vector3& center, float radius, std::shared_ptr<Material>&& material) noexcept 
		: center(center), radius(radius), material(std::move(material))
	{}

	virtual bool hit(const Ray& r, float tMin, float tMax, HitRecord& rec) const noexcept override
	{
		Vector3 oc = r.origin - center;
		float a = Vec3Dot(r.direction, r.direction);
		float b = 2.0f * Vec3Dot(oc, r.direction);
		float c = Vec3Dot(oc, oc) - radius * radius;
		float discriminant = b * b - 4 * a * c;
		if (discriminant > 0.0f) {
			rec.material = material;
			const float sqrtDiscriminant = sqrtf(discriminant);

			float temp = (-b - sqrtDiscriminant) / (2 * a);
			if (temp < tMax && temp > tMin) {
				rec.hit = temp;
				rec.p = r.distanceFromOrigin(temp);
				rec.normal = (rec.p - center) / radius;
				return true;
			}
			
			temp = (-b + sqrtDiscriminant) / (2 * a);
			if (temp < tMax && temp > tMin) {
				rec.hit = temp;
				rec.p = r.distanceFromOrigin(temp);
				rec.normal = (rec.p - center) / radius;
				return true;
			}
		}
		return false;
	}

	std::shared_ptr<Material> material;
	Vector3 center;
	float radius;
};
