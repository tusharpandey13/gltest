#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <modules/helpers.h>
//#include <modules/mesh.h>
#include <modules/model.h>
#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <modules/camera.h>
#include <boost/lexical_cast.hpp>
#include <functional>
#include <modules/globals.h>





static void mouse_callback(GLFWwindow* window, double xpos, double ypos){

	if (g_firstmouse){
		g_lastx = xpos;
		g_lasty = ypos;
		g_firstmouse = 0;
	}

	g_dx = xpos - g_lastx;
	g_dy = -(ypos - g_lasty);
	g_lastx = xpos;
	g_lasty = ypos;
}



class window{
private:
	int _width, _height;
	const char* _title;
	GLFWwindow* _handle;
	int _dirty = 0;
	std::vector<model> _modellist;
	/*std::vector<shader> _shaderlist;
	shaderprogram _shaderprogram;*/
	camera::camera _camera;
	double _lasttime;
	double _deltatime;
	int _frames = 0;

	void _render();
	void _input();
	void _init();
	void _init2();
	static void _framebuffer_size_callback(GLFWwindow *window, int width, int height);
	void _end();

public:
	window() = default;
	window(int W, int H, const char* _Title) ;

	void addmodel(model m);
//	void addshader(shader s);
	void run();

	GLFWwindow* handle(){return _handle;}

	~window();

};

