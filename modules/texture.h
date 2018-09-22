#pragma once

#include <glad/glad.h>
//#include <GLFW/glfw3.h>
#include <modules/stb_image.h>
#include <string>
#include <modules/helpers.h>

namespace texture {
enum texturetype : int {
	diffuse = 0,
	specular = 1,
	emission = 2
};


class texture {
private:
	GLuint _handle;
	int _internalindex = 0;
	std::string _filename;
	texturetype _type;

public:

	texture(std::string filename, texturetype type);

	~texture();

	void init(int internalindex);
	void bind();
	void dispose();

	texturetype type() {return _type;}
};

}


