#pragma once
#include <string>
#include <glad/glad.h>
//#include <GLFW/glfw3.h>
#include <modules/helpers.h>



class vertexattribute {
private:
	GLuint _index;
	std::string _name;
	GLint _length;

public:
	vertexattribute(std::string name, GLint length, GLuint index);
	void set(GLuint ShaderProgramHandle) ;

	int offset = 0;
	const char* name() {return _name.c_str();}
	GLuint index() {return _index;}
	int length() {return _length;}
	GLsizei size() {return (GLsizei)_length * sizeof(GLfloat);}



	~vertexattribute();
};

