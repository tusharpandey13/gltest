#pragma once

#include <modules/mesh.h>
#include <modules/shader.h>
#include <modules/shader.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class model {
private:
	std::vector<mesh> _meshlist;
	shaderprogram _shaderprogram;
	std::vector<shader> _shaderlist;
	int _lightcount = 0;

public:
	model(std::vector<mesh> meshes);
	model(std::vector<mesh> meshes, shaderprogram sp);
	~model();

	void draw();
	void init(std::vector<vertexattribute> vattribs, int _width, int _height);
	void dispose();
	void setcameraview(glm::mat4 view) {_shaderprogram.setMat4("view", view);}
	void setcamerapos(glm::vec3 pos) {_shaderprogram.setVec3("camerapos", pos);}
	void addshader(shader s);
};

