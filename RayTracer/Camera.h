#pragma once
#include "Vector3.h"
#include "Ray.h"
#include <math.h>
#include "AdditionalFunctions.h"

class Camera {
public:
	Camera(Vector3 lookFrom, Vector3 lookAt, Vector3 vUp, float fov, float aspect, float focusDist, float aperature) noexcept 
		: origin(lookFrom), lensRadious(aperature / 2)
	{
		float theta = fov * PI / 180.0f;
		float halfHeight = tan(theta / 2.0f);
		float halfWidth = aspect * halfHeight;
		w = (lookFrom - lookAt).toUnitVector();
		u = Vec3Cross(vUp, w).toUnitVector();
		v = Vec3Cross(w, u);
		lowerLeftCorner = origin - halfWidth * u * focusDist - halfHeight * v * focusDist - w * focusDist;
		horizontal = 2.0f * halfWidth * u * focusDist;
		vertical = 2.0f * halfHeight * v * focusDist;
	}

	Ray getRay(float s, float t) const noexcept { 
		Vector3 rd = lensRadious * RandomUnitInDisk();
		Vector3 offset = u * rd.x + v * rd.y;
		return Ray(origin + offset, lowerLeftCorner + horizontal * s + vertical * t - origin - offset); 
	}

	Vector3 lowerLeftCorner;
	Vector3 horizontal;
	Vector3 vertical;
	Vector3 origin;
	Vector3 w, u, v;
	float lensRadious;
};
