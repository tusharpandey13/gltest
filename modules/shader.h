#pragma once

#include <glad/glad.h>
//#include <GLFW/glfw3.h>
#include <string.h>
#include <fstream>
#include <modules/helpers.h>
#include <vector>
#include <stdlib.h>
#include <boost/lexical_cast.hpp>

class shader{
private:
	std::string _src;
	GLuint _handle;
	GLenum _type;
	std::string _filename;


public:
	shader(std::string src, GLenum Type);
	shader(std::string FileName);
	~shader() = default;

	GLuint handle();
	GLenum gettype();
	void dispose();
	std::string filename();
	void init(int lightcount);

//	std::vector<std::string> texturenames;

};
