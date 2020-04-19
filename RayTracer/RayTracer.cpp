#define OLC_PGE_APPLICATION
#include "PixelGameEngine.h"
#include "Vector3.h"
#include "Ray.h"
#include "Hitable.h"
#include "Sphere.h"
#include "Camera.h"
#include "Material.h"
#include "AdditionalFunctions.h"
#include <limits>
#include <math.h>
#include <iostream>
#include <memory>
#include <random>


class RayTracer : public olc::PixelGameEngine
{
public:
	RayTracer()
	{
		sAppName = "Ray Tracer";
	}

public:
	static constexpr int numOfSpheres = 500;

	bool OnUserCreate() override
	{
		auto& list = hitableList.list;
		list.resize(numOfSpheres);
		int i = 0;
		list[i++] = std::make_unique<Sphere>(Vector3(0.0f, -1000.0f, 0.0f), 1000.0f, std::make_shared<Lambertian>(Vector3(0.5f)));
		for (int a = -11; a < 11; a++) {
			for (int b = -11; b < 11; b++) {
				float material = RandomReal();
				Vector3 center = Vector3(a + 0.9f * RandomReal(), 0.2f, b + 0.9f * RandomReal());
				if ((center - Vector3(4.0f, 0.2f, 0.0f)).lenght() > 0.9f) {
					if(material < 0.8f) list[i++] = std::make_unique<Sphere>(center, 0.2f, 
						std::make_shared<Lambertian>(Vector3(RandomReal() * RandomReal(), RandomReal() * RandomReal(), RandomReal() * RandomReal())));
					else if (material < 0.95f) list[i++] = std::make_unique<Sphere>(center, 0.2f,
						std::make_shared<Metal>(Vector3(0.5f * (1.0f + RandomReal()), 0.5f * (1.0f + RandomReal()), 0.5f * (1.0f + RandomReal())), 0.5f * (1.0f + RandomReal())));
					else list[i++] = std::make_unique<Sphere>(center, 0.2f, std::make_shared<Dielectric>(1.5f));
				}
			}
		}

		list[i++] = std::make_unique<Sphere>(Vector3(0.0f, 1.0f, 0.0f), 1.0f, std::make_shared<Dielectric>(1.5f));
		list[i++] = std::make_unique<Sphere>(Vector3(-4.0f, 1.0f, 0.0f), 1.0f, std::make_shared<Lambertian>(Vector3(0.4f, 0.2f, 0.1f)));
		list[i++] = std::make_unique<Sphere>(Vector3(4.0f, 1.0f, 0.0f), 1.0f, std::make_shared<Metal>(Vector3(0.7f, 0.6f, 0.5f), 0.0f));

		list.resize(i);

		return true;
	}

	Vector3 Color(const Ray& r, const Hitable& world, int depth = 0) {
		HitRecord hitRec;
		if (world.hit(r, 0.001f, std::numeric_limits<float>::max(), hitRec)) {
			Ray scattered;
			Vector3 attenuation;
			if (depth < 50 && hitRec.material->scatter(r, hitRec, attenuation, scattered)) {
				return attenuation * Color(scattered, world, depth + 1);
			}
			else return Vector3(0.0f);
		}
		else {
			float t = 0.5f * (r.direction.toUnitVector().y + 1.0f);
			return (1.0f - t) * Vector3(1.0f) + t * Vector3(0.5f, 0.7f, 1.0f);
		}
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		static int x = 0, y = 0;
		Vector3 col;
		for (int i = 0; i < numOfSamples; i++) {
			float u = (x + RandomReal()) / ScreenWidth();
			float v = 1.0f - ((y + RandomReal()) / ScreenHeight());
			Ray r = cam.getRay(u, v);
			col += Color(r, hitableList);
		}
		col /= numOfSamples;
		col = Vector3(sqrtf(col.x), sqrtf(col.y), sqrtf(col.z)) * 255.0f;
				
		Draw(x, y, { (uint8_t)col.x, (uint8_t)col.y, (uint8_t)col.z });

		if (++x == ScreenWidth()) {
			x = 0;
			if (++y == ScreenHeight()) y = 0;
		}

		return true;
	}

	HitableList hitableList;
	const Vector3 lookFrom = Vector3(-2.0f, 2.0f, 4.0f);
	const Vector3 lookAt = Vector3(0.0f, 1.0f, -1.0f);
	Camera cam{ lookFrom, lookAt, Vector3(0.0f, 1.0f, 0.0f),
		60.0f, (float)width / height, (lookFrom - lookAt).lenght(), 0.0f};
	static constexpr int numOfSamples = 100;
	static constexpr int width = 640;
	static constexpr int height = 360;

};


int main()
{
	RayTracer rt;
	if (rt.Construct(RayTracer::width, RayTracer::height, 2, 2))
		rt.Start();

	return 0;
}
