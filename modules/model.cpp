#include "model.h"

model::model(std::vector<mesh> meshes) : _meshlist(meshes) {}

model::model(std::vector<mesh> meshes, shaderprogram sp)
	: _meshlist(meshes), _shaderprogram(sp) {}

model::~model() {}

void model::draw() {
	for (mesh& m : _meshlist) {
		m.draw();
	}
}

void model::init(std::vector<vertexattribute> vattribs, int _width, int _height) {

	for (mesh& m : _meshlist) {
		if (m.islight()) {
			m.lightindex = _lightcount;
			_lightcount += 1;
		}
	}


	_shaderprogram = shaderprogram(_shaderlist);
	_shaderprogram.init(_lightcount);

	//glm::mat4 modelm;
	//_shaderprogram.setMat4("model", modelm);
	_shaderprogram.setMat4("projection", glm::perspective(glm::radians(45.0f),
														  static_cast<float>(_width) / static_cast<float>(_height),
														  0.1f, 100.0f));

	for (mesh& m : _meshlist) {m.init(vattribs, &_shaderprogram);}

}

void model::dispose() {
	for (mesh& m : _meshlist) {
		m.dispose();
	}
}

void model::addshader(shader s) {
	_shaderlist.push_back(s);
}
