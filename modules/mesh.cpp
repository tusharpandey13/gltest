#include "mesh.h"
#include "texture.h"

mesh::mesh(std::vector<GLfloat> vertices, std::vector<GLuint> indices,
		   std::vector<texture::texture> textures)
	: _texturelist(textures), _vertexlist(vertices), _indexlist(indices) {
	if (_indexlist.size() == 0) {_eboenabled = false;}
	if (_texturelist.size() == 0) {_islight = true; _lightcolor = glm::vec3(1.0, 1.0, 1.0);}
}


mesh::mesh(mesh& Mesh, glm::mat4 transform) : mesh(Mesh) {
	_transform = transform;
	_islight = false;
}

mesh::mesh(mesh& Mesh, glm::mat4 transform, glm::vec3 lightcolor, float ambient, float diffuse,
		   float specular): mesh(Mesh) {
	_transform = transform;
	_lightcolor = lightcolor;
	_lightambient = ambient;
	_lightdiffuse = diffuse;
	_lightspecular = specular;
	_islight = true;
}


void mesh::init(std::vector<vertexattribute> vattribs, shaderprogram* sppointer) {

	_shaderprogram = sppointer;

	gl(glGenVertexArrays(1, &_VAO));

	_VBO = generic_buffer<GLfloat>(GL_ARRAY_BUFFER);
	if (_eboenabled) { _EBO = generic_buffer<GLuint>(GL_ELEMENT_ARRAY_BUFFER); }

	_VBO.add(_vertexlist);
	if (_eboenabled) { _EBO.add(_indexlist); }

	_bind();
	_buffer();

	for (vertexattribute& v1 : vattribs) {
		v1.offset = _stride;
		_stride += v1.size();
	}

	for (vertexattribute& v2 : vattribs) {
		v2.set((*_shaderprogram).handle());
		gl(glVertexAttribPointer(v2.index(), v2.length(), GL_FLOAT, 0, _stride
								 , (void*)(intptr_t)(v2.offset)));
	}

	int tmpc = 0;
	for (texture::texture& t : _texturelist) {
		t.init(tmpc);
		std::string tname = "";
		switch (t.type()) {
		case 0: {tname = "material.diffuse";}
		case 1: {tname = "material.specular";}
		case 2: {tname = "material.emission";}
		}
		(*_shaderprogram).setInt(tname, tmpc++);
	}

	gl(glBindVertexArray(0));

}

void mesh::_bind() {
	gl(glBindVertexArray(_VAO));
	_VBO.bind();
	if (_eboenabled) { _EBO.bind(); }
}

void mesh::_buffer() {
	_VBO.buffer_data();
	if (_eboenabled) { _EBO.buffer_data(); }
}

void mesh::draw() {
	for (texture::texture& t : _texturelist) {
		t.bind();
	}
	gl(glBindVertexArray(_VAO));

	(*_shaderprogram).setMat4("model", _transform);
	(*_shaderprogram).setBool("pointlights[" + boost::lexical_cast<std::string>(lightindex)
							  + "].islight"
							  , _islight);
	if (_islight) {
		(*_shaderprogram).setVec3("pointlights[" + boost::lexical_cast<std::string>(lightindex)
								  + "].position",
								  glm::vec3(_transform[3]));
		//glm::vec3 translate = glm::mat4 transform[3]
		(*_shaderprogram).setVec3("pointlights[" + boost::lexical_cast<std::string>(lightindex)
								  + "].color",
								  _lightcolor);
		(*_shaderprogram).setFloat("pointlights[" + boost::lexical_cast<std::string>(lightindex)
								   + "].ambient",
								   _lightambient);
		(*_shaderprogram).setFloat("pointlights[" + boost::lexical_cast<std::string>(lightindex)
								   + "].diffuse",
								   _lightdiffuse);
		(*_shaderprogram).setFloat("pointlights[" + boost::lexical_cast<std::string>(lightindex)
								   + "].specular",
								   _lightspecular);
	}
	else {

	}

	(*_shaderprogram).setInt("lightindex", lightindex);

	if (_eboenabled) {gl(glDrawElements(GL_TRIANGLES, _EBO.size(), GL_UNSIGNED_INT, nullptr));}
	else {gl(glDrawArrays(GL_TRIANGLES, 0, _VBO.size());)}

//	gl(glBindVertexArray(0));
}


void mesh::dispose() {
	gl(glBindVertexArray(0));
	gl(glDeleteVertexArrays(1, &_VAO));
	if (_eboenabled) { _EBO.dispose(); }
	_VBO.dispose();
	for (texture::texture& t : _texturelist) {
		t.dispose();
	}
//	delete _shaderprogram;
}

mesh::~mesh() {

}

