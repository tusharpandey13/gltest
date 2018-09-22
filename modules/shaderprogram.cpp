#include "shaderprogram.h"

shaderprogram::shaderprogram(std::vector<shader> shaderlist) : _shaderlist(shaderlist){}

void shaderprogram::init(int lightcount){

	gl(_handle = glCreateProgram());

	for(shader &s1 : _shaderlist){
		s1.init(lightcount);
		gl(glAttachShader(_handle, s1.handle()));
	}

	gl(glLinkProgram(_handle));

	int tmpsuccess = 1;
	char infolog[512];
	gl(glGetProgramiv(_handle, GL_LINK_STATUS, &tmpsuccess));
	if(!tmpsuccess){
		gl(glGetProgramInfoLog(_handle, 512, NULL, infolog));
		helpers::print(std::string("shaderprogram linking failed\n\n") + std::string(infolog)
					   + std::string("\n"), helpers::messages::Error);
	}
	else{
		use();
		helpers::print("shaderprogram successfully loaded", helpers::messages::Info);
	}

	for(shader &s2 : _shaderlist){
		s2.dispose();
	}


//	gl(glUseProgram(_handle));
/*	int c = 0;
	for(shader& s : _shaderlist){
		for(std::string tname : s.texturenames){
			setInt(tname, c++);
		}
	}*/
}

void shaderprogram::use(){gl(glUseProgram(_handle));}

void shaderprogram::setBool(const std::string &name, bool value) const{
	gl(glUniform1i(glGetUniformLocation(_handle, name.c_str()), (int)value));
}
void shaderprogram::setInt(const std::string &name, int value) const{
	gl(glUniform1i(glGetUniformLocation(_handle, name.c_str()), value));
}

void shaderprogram::setIntv(const std::string &name, int v, int value[]) const{
	gl(glUniform1iv(glGetUniformLocation(_handle, name.c_str()), v, value));
}
void shaderprogram::setFloat(const std::string &name, float value) const{
	gl(glUniform1f(glGetUniformLocation(_handle, name.c_str()), value));
}
void shaderprogram::setMat4(const std::string &name, glm::mat4 value) const{
	gl(glUniformMatrix4fv(glGetUniformLocation(_handle, name.c_str()), 1, GL_FALSE
						  , glm::value_ptr(value)));
}
void shaderprogram::setVec3(const std::string &name, glm::vec3 value) const{
	gl(glUniform3f(glGetUniformLocation(_handle, name.c_str()), value.x, value.y, value.z));
}


shaderprogram::~shaderprogram(){}

