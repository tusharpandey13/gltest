#pragma once

#include <vector>
//#include "helpers.h"

template <class T>
class generic_buffer {
private:
	GLuint _handle;
	std::vector<T> _data = {};
	GLenum _target;
	GLenum _usage;

public:
	generic_buffer(GLenum target, GLenum usage = GL_STATIC_DRAW) : _target(target), _usage(usage) {
		glGenBuffers(1, &_handle);
	}
	generic_buffer() = default;



	virtual void add(std::vector<T> data) {_data.insert(_data.end(), data.begin(), data.end());}

	virtual void bind() {glBindBuffer(_target, _handle);}

	virtual void buffer_data() {glBufferData(_target, sizeof(T)*_data.size(), &_data[0], _usage);}

	T* getarray() {return &_data[0];}

	virtual GLsizei size() {return (GLsizei)_data.size();}

	virtual void dispose() {
		glDeleteBuffers(1, &_handle);
	}

	~generic_buffer() {
		_data.clear();
//		glBindBuffer(_target, 0);
	}
};
