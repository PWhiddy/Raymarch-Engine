#include "Scene.h"

// GLEW
//#define GLEW_STATIC
#include "GL/glew.h"

// GLFW
#include "GLFW/glfw3.h"

namespace rme
{
	class RaymarchRenderer
	{
		std::string loadSource(char* filename);
		/*const*/ GLuint width, height;
		GLuint VBO, VAO, EBO;
		GLuint shaderProgram;
		GLuint timeLocation, resolutionLocation, rotationLocation, camPosLocation, objCountLocation, warpCountLoc;
		shaderObject3D *objectLocations;
		shaderObject3D warpALoc, warpBLoc;
		void getObject3DLocation(shaderObject3D *obj, std::string id);
		void updateUniforms(Scene* scene, Camera* camera);
		void updateObject3D(shaderObject3D location, Object3D *obj);
	public:
		RaymarchRenderer(int w, int h);
		~RaymarchRenderer();
		GLFWwindow* window;
		//Controls control;
		Controls* getControl();
		void resize(int x, int y);
		void render(Scene* scene, Camera* camera);
	};


	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

	static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);

}

