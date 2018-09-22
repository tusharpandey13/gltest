#pragma once
#include <glad/glad.h>
//#include <GLFW/glfw3.h>
#include <vector>
#include <modules/shader.h>
#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class shaderprogram{
private:
	//std::vector<shader> _shaderlist;
	GLuint _handle;
	std::vector<shader> _shaderlist;


public:
	shaderprogram() = default;
	shaderprogram(std::vector<shader> shaderlist);
	void init(int lightcount);
	GLuint handle() {return _handle;}
	void use();

	// utility uniform functions
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setIntv(const std::string &name, int v, int value[]) const;
	void setFloat(const std::string &name, float value) const;
	void setMat4(const std::string &name, glm::mat4 value) const;
	void setVec3(const std::string &name, glm::vec3 value) const;


	~shaderprogram();
};
