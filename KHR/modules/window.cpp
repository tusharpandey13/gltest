#include "window.h"



void window::_init2() {
	_camera = camera::camera(glm::vec3(0, 0, 3), &_deltatime);

	for (model& m : _modellist) {
		m.init({
			vertexattribute("aPos", 3, 0),
			vertexattribute("aNormal", 3, 1),
//		vertexattribute("aColor", 3),
			vertexattribute("aTexCoord", 2, 2)
		}, _width, _height);
	}
}

void window::run() {

	_init2();

	_lasttime = glfwGetTime();
	double fpslasttime = _lasttime;
	_frames = 0;

	glfwSetInputMode(_handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	while (!glfwWindowShouldClose(_handle)) {

		double tmp = glfwGetTime();
		_deltatime = tmp - _lasttime;
		_lasttime = tmp;

		double tmp2 = tmp;
		_frames++;
		if ((tmp2 - fpslasttime) >= 0.1) {
			glfwSetWindowTitle(_handle,
							   (boost::lexical_cast<std::string>(100.0 / (double)_frames)
								/*boost::lexical_cast<std::string>(g_dx)
								+ boost::lexical_cast<std::string>(g_dy))*/.c_str()));
			_frames = 0;
			fpslasttime += 0.1;
		}

		_input();
		_render();

	}

	//_end();	//automatically disposed on dtor
}



void window::_render() {


	gl(glClearColor(0.0, 0.0, 0.0, 1.0f));
	gl(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));


	for (model& m : _modellist) {
		m.setcameraview(_camera.view());
		m.setcamerapos(_camera.position);
		m.draw();
	}

	// Swap buffers
	glfwSwapBuffers(_handle);
	glfwPollEvents();

}

void window::_input() {
	if (glfwGetKey(_handle, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		gl(glfwSetWindowShouldClose(_handle, true));
	}

	_camera.turn(g_dx, g_dy);
	g_dx = 0; g_dy = 0;

	if (glfwGetKey(_handle, GLFW_KEY_W) == GLFW_PRESS) {_camera.move(camera::direction::Forward);}
	if (glfwGetKey(_handle, GLFW_KEY_S) == GLFW_PRESS) {_camera.move(camera::direction::Back);}
	if (glfwGetKey(_handle, GLFW_KEY_A) == GLFW_PRESS) {_camera.move(camera::direction::Left);}
	if (glfwGetKey(_handle, GLFW_KEY_D) == GLFW_PRESS) {_camera.move(camera::direction::Right);}

}

void window::_init() {
	if (!_dirty) {
		helpers::print("window not initialized", helpers::messages::Error);
		return;
	}

	// Initialise GLFW
	if (!glfwInit())	{
		helpers::print("Failed to initialize GLFW", helpers::messages::Error);
	}	helpers::print("GLFW initialized", helpers::messages::Info);

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	_handle = glfwCreateWindow(_width, _height, _title, NULL, NULL);
	if (_handle == NULL) {
		helpers::print("Failed to open GLFW window. Maybe the graphics card does not support Opengl v3",
					   helpers::messages::Error);
		_end();
	}	helpers::print("Context created for window", helpers::messages::Info);

	glfwMakeContextCurrent(_handle);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		helpers::print("Failed to initialize GLAD", helpers::messages::Error);
	} helpers::print("GLAD initialized", helpers::messages::Info);

	gl(glViewport(0, 0, _width, _height));

	glfwSetFramebufferSizeCallback(_handle, _framebuffer_size_callback);

	glfwSetCursorPosCallback(_handle, mouse_callback);

	glEnable(GL_DEPTH_TEST);
}

void window::_framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	gl(glViewport(0, 0, width, height));
}


void window::_end() {
	// Close OpenGL window and terminate GLFW
	for (model& m : _modellist) {
		m.dispose();
	}
	glfwTerminate();
	helpers::print("GLFW terminated", helpers::messages::Info);
}

void window::addmodel(model m) {
	_modellist.push_back(m);
}

/*void window::addshader(shader s){
	_shaderlist.push_back(s);
}*/


window::window(int W, int H, const char* _Title) {
	_width = W;
	_height = H;
	_title = _Title;
	helpers::print("window constructed", helpers::messages::Info);
	_dirty = 1;
	_init();	// ugly code
}


window::~window() {
	_end();
	helpers::print("window destroyed", helpers::messages::Info);
}

