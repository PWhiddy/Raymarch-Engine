#include "Initialize.h"

/*
float rando(){
	return static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 0.01));
}
*/

int main()
{
	srand(0);
	
	rme::Scene *scene = new rme::Scene();

	rme::Camera *camera = new rme::Camera(std::string("camera1"));
	camera->position = glm::vec3(0.0, 2.0, -3.0);
	camera->physics = true;
	scene->add(camera);


	rme::BoxInterior *room = new rme::BoxInterior(std::string("room"));
	room->shape = glm::vec3(30.0, 16.0, 36.0);
	room->color = glm::vec3(0.0, 0.8, 0.4);
	//room->position = glm::vec3(0.5, 0.7, 0.2);
	scene->add(room);

	//rme::Light *light = new rme::Light(std::string("light"));
	//light->position = glm::vec3(0.0, 3.0, 0.0);
	//light->radius = 1.0;
	rme::Sphere *sphere = new rme::Sphere(std::string("light"));
	sphere->radius = 1.0;
	sphere->position = glm::vec3(0.0, 2.0, 10.0);
	scene->add(sphere);

	rme::RaymarchRenderer *renderer = new rme::RaymarchRenderer(1200, 720);
	
	int totalFrames = 0;
	int lastFrame = 0;
	float totalTime = 0.0;
	float lastTime = 0.0;
	//glfwSetTime(0.0);

	// Game loop
	
	while (!glfwWindowShouldClose(renderer->window))
	{
		
	//	s1->position.z += 0.002;

		for (int i = 0; i < 5; i++)
		{
			scene->update(renderer->getControl());
		}

		renderer->render(scene, camera);
		totalFrames++;
		totalTime = float(glfwGetTime());
		float delta = totalTime - lastTime;
		if (delta > 1.0)
		{
			std::printf("FPS: %f\n", float(totalFrames - lastFrame)/delta);
			lastFrame = totalFrames;
			lastTime = totalTime;
		}

	}

	delete renderer;
	return 0;
}
