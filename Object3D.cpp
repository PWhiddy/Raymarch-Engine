#include "Object3D.h"

namespace rme
{

	Object3D::Object3D(std::string n)
	{
		name = n;
		position = glm::vec3(0.0);
		correction = glm::vec3(0.0);
		velocity = glm::vec3(0.0);
		direction = glm::vec3(0.0, 0.0, 1.0);
		radius = 2.0;
		shape = glm::vec3(0.0, 0.0, 0.0);
		geometry = CONTAINER;
		mass = 1.0;
		charge = 0.1;
		age = 0.0;
		collisions = true;
		physics = false;
		color = glm::vec3(1.0, 1.0, 1.0);
		//	material = new Material();
	}

	Camera::Camera(std::string n) :Object3D(n)
	{
		geometry = CAMERA;
		rotation = glm::vec4(0.0);
		physics = true;
		radius = 4.0;
	}

	Light::Light(std::string n) :Object3D(n) { geometry = LIGHT; }

	Sphere::Sphere(std::string n) :Object3D(n) { geometry = SPHERE; }

	BoxInterior::BoxInterior(std::string n) : Object3D(n) { geometry = BOX_INTERIOR; }

}