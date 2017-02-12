// GLEW
//#define GLEW_STATIC
#include "GL/glew.h"
#include "glm/glm.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include "control.h"

#define MAX_OBJECTS 20

#define CONTAINER  0
#define CAMERA 1
#define PLAYER 2
#define LIGHT 3
#define SPHERE 4
#define SPHERE_INTERIOR 5
#define BOX 6
#define BOX_INTERIOR 7
#define TORUS 8

namespace rme
{

	class Object3D
	{
	public:
		std::string name;
		glm::vec3 position;
		glm::vec3 correction;
		glm::vec3 velocity;
		glm::vec3 direction;
		//glm::mat4 translation;
		float radius;
		glm::vec3 shape;
		int geometry;
		float mass;
		float charge;
		float age;
		bool collisions;
		bool physics;
		std::vector<Object3D> children;
		glm::vec3 color;
		//	Material *material;
		Object3D(std::string n);
	};

	struct shaderObject3D {
		GLuint position; //vec3
		GLuint direction; //vec3
		//GLuint translation; //mat4
		GLuint radius; //float
		GLuint age; //float
		GLuint shape; //vec3
		GLuint geometry; //int
		GLuint mass; //float
		//GLuint shininess; //float
		//GLuint luminance; //float
		GLuint color; //vec3
		//GLuint shading; //int
	};

	class Camera :public Object3D
	{
	public:
		glm::vec4 rotation;
		Camera(std::string n);
	};

	class Light :public Object3D
	{
	public:
		Light(std::string n);
	};

	class Sphere :public Object3D
	{
	public:
		Sphere(std::string n);
	};

	class BoxInterior :public Object3D
	{
	public:
		BoxInterior(std::string n);
	};

}