#include "Scene.h"


namespace rme
{


	Scene::Scene()
	{
		std::vector<Object3D*> children;
		warpA = NULL;// new rme::Sphere("warpA");
		warpB = NULL;// rme::Sphere("warpB");
		//control();
	}

	void Scene::add(Object3D *obj)
	{
		children.push_back(obj);
	}

	void Scene::remove(std::string name)
	{
		int index = -1;
		int count = 0;
		for (std::vector<Object3D*>::iterator it = children.begin(); it != children.end(); ++it)
		{
			if (children[count]->name == name)
			{
				index = count;
				break;
			}
			count++;
		}
		if (index < 0)
		{
			std::cout << "Object to remove does not exist\n";
		}
		else
		{
			children.erase(children.begin() + count);
		}
	}

	void Scene::spawn(Camera* camera, bool left, Controls* control)
	{
		Sphere *sphere;
		if (left)
		{
			sphere = new rme::Sphere("warpA");
			delete this->warpA;
		}
		else
		{
			sphere = new rme::Sphere("warpB");
			delete this->warpB;
		}
		glm::vec2 yRot = rot2D(glm::vec2(0.0, 1.0), control->yRotation);
		glm::vec2 xRot = rot2D(glm::vec2(0.0, yRot.y), control->xRotation);
		glm::vec3 dir = glm::normalize(glm::vec3(xRot.x, yRot.x, xRot.y));

		sphere->color = glm::vec3(0.0, 1.0, 0.0);
		//sphere->material->color = glm::vec3(0.0, 1.0, 0.0);
		sphere->radius = 2.75;
		sphere->position = camera->position + 1.1f*sphere->radius*dir;
		sphere->charge = 0.0;
		sphere->velocity = dir*0.07f;
		sphere->physics = true;
		if (left)
		{
			this->warpA = sphere;
		}
		else
		{
			this->warpB = sphere;
		}

	}

	void Scene::update(Controls* control)
	{
		// Collision detection and interaction
		for (int i = 0; i < children.size(); i++)
		{
			Object3D *current = children[i];

			current->age += 1.0;

			if (current->physics) {
				current->velocity += glm::vec3(0.0, -0.0005, 0.0);
			}

			// Camera collides but does not feel force
			if (current->geometry == CAMERA)
			{
				// Move player with WASD
				glm::vec2 direction = rot2D(glm::vec2(0.0, 1.0), control->xRotation);
				glm::vec2 directionPerp = rot2D(glm::vec2(1.0, 0.0), control->xRotation);

				glm::vec3 candidate = current->position + current->velocity;
				float testDist = map(candidate, i);
				glm::vec3 camNorm = normal(candidate, i);
				if (testDist < current->radius)
				{
					
					if (control->w) current->velocity += 0.002f*glm::vec3(direction.x, 0.0, direction.y);
					if (control->a) current->velocity += -0.002f*glm::vec3(directionPerp.x, 0.0, directionPerp.y);
					if (control->s) current->velocity += -0.002f*glm::vec3(direction.x, 0.0, direction.y);
					if (control->d) current->velocity += 0.002f*glm::vec3(directionPerp.x, 0.0, directionPerp.y);

					//	if (glm::dot(camNorm, glm::vec3(0.0, 1.0, 0.0)) > 0.0)
					//	{
					current->velocity = 0.97f*(current->velocity - glm::dot(current->velocity, camNorm)*camNorm);
					//	}
					if (control->space && glm::dot(camNorm, glm::vec3(0.0, 1.0, 0.0)) > 0.7)
					{
						current->velocity += glm::vec3(0.0, 0.06, 0.0);
						current->position += current->velocity;
					}

				}

				if (control->lmb)
				{
					spawn((Camera*)current, true, control);
					control->lmb = false;
				}
				if (control->rmb)
				{
					spawn((Camera*)current, false, control);
					control->rmb = false;
				}

			}

			if (current->geometry != SPHERE) continue;

			// Electromagnetic/Gravity like force
			for (int j = 0; j < children.size(); j++)
			{
				Object3D *other = children[j];
				if (other->geometry != SPHERE || i == j) continue;
				glm::vec3 diff = current->position - other->position;
				float radius = glm::length(diff);
				float force = current->charge*other->charge / (radius*radius);
				current->velocity += diff * force;
			}

			// Collision detection
			float distance = map(current->position, i);
			float delta = distance - current->radius;
			// Collision
			if (delta < 0.0f && current->collisions)
			{
				glm::vec3 norm = glm::vec3(normal(current->position, i));
				current->velocity = 1.0f*glm::reflect(current->velocity, norm);
				//	current->correction += -1.0f*delta*glm::normalize(current->velocity);
			}

		}

		// Update positions
		for (int i = 0; i < children.size(); i++)
		{
			Object3D *current = children[i];
			current->velocity *= 0.999;
			current->position += (current->velocity + current->correction);
			current->correction = glm::vec3(0.0);
		}

	}

	float Scene::map(glm::vec3 p, int exclude)
	{
		float dist = 1000000.0;
		for (int i = 0; i < children.size(); i++) {
			if (i == exclude) continue;
			switch (children[i]->geometry) {
			case 4:
				dist = glm::min(dist, sdSphere(p - children[i]->position, children[i]->radius));
				break;
			case 7:
				dist = glm::min(dist, sdBoxInterior(p - children[i]->position, children[i]->shape));
				break;
			default:
				dist = dist;
			}
		}
		return dist;
	}

	glm::vec3 Scene::normal(glm::vec3 p, int exclude)
	{
		glm::vec3 eps = glm::vec3(0.002, 0.0, 0.0);
		return glm::normalize(glm::vec3(
			map(p + glm::vec3(eps.x, eps.y, eps.y), exclude) - map(p - glm::vec3(eps.x, eps.y, eps.y), exclude),
			map(p + glm::vec3(eps.y, eps.x, eps.y), exclude) - map(p - glm::vec3(eps.y, eps.x, eps.y), exclude),
			map(p + glm::vec3(eps.y, eps.y, eps.x), exclude) - map(p - glm::vec3(eps.y, eps.y, eps.x), exclude)));
	}

	glm::vec2 Scene::rot2D(glm::vec2 p, float angle)
	{
		float s = glm::sin(angle);
		float c = glm::cos(angle);
		return p * glm::mat2(c, s, -s, c);
	}

	///// Signed Distance Geometries ////

	float Scene::sdSphere(glm::vec3 p, float s)
	{
		return glm::length(p) - s;
	}

	float Scene::sdTorus(glm::vec3 p, glm::vec2 t)
	{
		glm::vec2 q = glm::vec2(glm::length(glm::vec2(p.x, p.y)) - t.x, p.z);
		return glm::length(q) - t.y;
	}

	float Scene::sdRoundBox(glm::vec3 p, glm::vec3 b, float r)
	{
		glm::vec3 d = glm::abs(p) - b;
		return glm::min(glm::max(d.x, glm::max(d.y, d.z)), 0.0f) + glm::length(glm::max(d, glm::vec3(0.0))) - r;
	}

	float Scene::sdBoxInterior(glm::vec3 p, glm::vec3 b)
	{
		glm::vec3 d = glm::abs(p) - b;
		return -(glm::min(glm::max(d.x, glm::max(d.y, d.z)), 0.0f) + glm::length(glm::max(d, glm::vec3(0.0))));
	}

}