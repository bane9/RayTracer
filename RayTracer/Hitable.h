#pragma once
#include "Vector3.h"
#include "Ray.h"
#include <memory>
#include <vector>

class Material;

struct HitRecord {
	float hit = 0.0f;
	Vector3 p;
	Vector3 normal;
	
	std::shared_ptr<Material> material;
};

class Hitable {
public:
	virtual bool hit(const Ray& r, float tMin, float tMax, HitRecord& rec) const noexcept = 0;
};

class HitableList : public Hitable
{
public:
	using HitableVec = std::vector<std::unique_ptr<Hitable>>;

	HitableList() noexcept = default;
	HitableList(const HitableList&) noexcept = default;
	HitableList& operator=(const HitableList&) noexcept = default;

	virtual bool hit(const Ray& r, float tMin, float tMax, HitRecord& rec) const noexcept override
	{
		HitRecord tempRec;
		bool hitAnything = false;
		float closest = tMax;
		for (auto& hitable : list) {
			if (hitable->hit(r, tMin, closest, tempRec)) {
				hitAnything = true;
				closest = tempRec.hit;
				rec = tempRec;
			};

		}

		return hitAnything;
	}

	HitableVec list;
};

