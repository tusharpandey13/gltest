#include <modules/shader.h>



shader::shader(std::string src, GLenum Type) : _src(src), _type(Type) {}

shader::shader(std::string FileName) : _filename(FileName) {
	std::ifstream in;
	in.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	in.open(_filename);

	try {
		std::string contents((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
		_src = contents;

//		std::string tmp = helpers::split(_filename, ".")[1];
//		if (tmp.compare("vert") == 0) {_type = GL_VERTEX_SHADER;}
//		if (tmp.compare("frag") == 0) {_type = GL_FRAGMENT_SHADER;}

		if (_filename.substr(_filename.size() - 4, 4).compare("frag") == 0) {
			_type = GL_FRAGMENT_SHADER;
		}
		if (_filename.substr(_filename.size() - 4, 4).compare("vert") == 0) {
			_type = GL_VERTEX_SHADER;
		}

	}
	catch (std::ifstream::failure e) {
		helpers::print("Error reading file", helpers::messages::Error);
	}
	helpers::print("Shader loaded : " + _filename, helpers::messages::Info);
//	_init();
}

void shader::init(int lightcount) {
	gl(_handle = glCreateShader(_type));

	if (_type == GL_FRAGMENT_SHADER) {
		helpers::replace(_src, "__nrpointlights__",
						 boost::lexical_cast<std::string>(fmax(lightcount, 1)));
	}

	const char* tmp = _src.c_str();
	gl(glShaderSource(_handle, 1, &tmp, NULL));
	gl(glCompileShader(_handle));

	int success = 1;
	char ilog[1024];
	gl(glGetShaderiv(_handle, GL_COMPILE_STATUS, &success));
	if (!success) {
		gl(glGetShaderInfoLog(_handle, 1024, NULL, ilog));
		helpers::print(std::string("shader compile error : ")
					   + std::string(ilog)
					   , helpers::messages::Error);
	}

}


GLuint shader::handle() {return _handle;}

GLenum shader::gettype() {return _type;}

void shader::dispose() {
	gl(glDeleteShader(_handle));
}

std::string shader::filename() {return _filename;}
