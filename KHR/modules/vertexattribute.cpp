#include "vertexattribute.h"

vertexattribute::vertexattribute(std::string name, GLint length, GLuint index)
	: _name(name), _length(length), _index(index) {}

void vertexattribute::set(GLuint ShaderProgramHandle) {
//	gl(_index = glGetAttribLocation(ShaderProgramHandle, _name.c_str()));
	glEnableVertexAttribArray(_index);
	// _index is -1 when vertexattribute is not used anywhere in the shader
	//so removed gl() coz it causes harmless error
	//---------------------EDIT-------------------------------------------
	//apparantly the shader compiler optimizes out unused attributes
	//this happened even when it was used in the vs
	//so manually set attribute locations
}

vertexattribute::~vertexattribute() {
}

