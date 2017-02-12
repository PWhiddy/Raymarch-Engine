#include "Object3D.h"

namespace rme
{

	class Scene
	{
		float map(glm::vec3, int exclude);
		float sdSphere(glm::vec3 p, float s);
		float sdTorus(glm::vec3 p, glm::vec2 t);
		float sdRoundBox(glm::vec3 p, glm::vec3 b, float r);
		float sdBoxInterior(glm::vec3 p, glm::vec3 b);
		glm::vec3 normal(glm::vec3 p, int exclude);

	public:
		std::vector<Object3D*> children;
		Sphere *warpA;
		Sphere *warpB;
		//Controls control;
		Scene();
		void add(Object3D *obj);
		void remove(std::string name);
		void spawn(Camera *camera, bool left, Controls* control);
		glm::vec2 rot2D(glm::vec2 p, float angle);
		void update(Controls* control);
	};

}