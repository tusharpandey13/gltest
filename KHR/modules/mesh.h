#pragma once

#include <glad/glad.h>
//#include <GLFW/glfw3.h>
#include <modules/generic_buffer.hpp>
#include <vector>
#include <string>
#include <modules/vertexattribute.h>
#include <modules/shaderprogram.h>
#include <modules/texture.h>
#include <modules/helpers.h>
#include <glm/glm.hpp>
#include <boost/lexical_cast.hpp>

class mesh {
private:
	GLuint _VAO;
	generic_buffer<GLfloat> _VBO;
	generic_buffer<GLuint> _EBO;
	int _stride = 0;
	std::vector<texture::texture> _texturelist;
//	std::vector<vertexattribute> _attriblist;
	std::vector<GLfloat> _vertexlist;
	std::vector<GLuint> _indexlist;
	shaderprogram* _shaderprogram;
	glm::mat4 _transform;
	bool _eboenabled = true;
	bool _islight = false;
	glm::vec3 _lightcolor;
	float _lightambient, _lightdiffuse, _lightspecular = 0;


	void _bind();
	void _buffer();


public:
	mesh(std::vector<GLfloat> vertices, std::vector<GLuint> indices = {},
		 std::vector<texture::texture> textures = {});
	mesh(const mesh& other) = default;
	mesh(mesh& Mesh, glm::mat4 transform);
	mesh(mesh& Mesh, glm::mat4 transform, glm::vec3 lightcolor, float ambient, float diffuse,
		 float specular);


	~mesh();
	void draw();
	void dispose();
//	void addvertexattrib(vertexattribute v);
//	void finalize();
//	void addtexture(std::string filename, std::string Name);
	void init(std::vector<vertexattribute> vattribs, shaderprogram* sppointer);


	bool islight() {return _islight;}
	int lightindex = -1;

//	int texturecount() {return _texturelist.size();}
};

