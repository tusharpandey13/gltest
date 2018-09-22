#include "helpers.h"



void helpers::print(std::string Message, messages::message_type Type) {
	switch (Type) {
	case (-1): { std::cout << BLUE <<   "[UNDEFINED] " << WHITE << Message.c_str() << RESET << "\n"; break;}
	case (0): {	std::cout << RED <<    "[ERROR]     " << WHITE << Message.c_str() << RESET << "\n";	break;}
	case (1): {	std::cout << YELLOW << "[WARNING]   " << WHITE << Message.c_str() << RESET << "\n";	break;}
	case (2): {	std::cout << GREEN <<  "[INFO]      " << WHITE << Message.c_str() << RESET << "\n";	break;}
	}
}






std::vector<std::string> helpers::split(std::string str, std::string delimiter) {
	std::vector<size_t> pos;
	pos.push_back(0);
	std::vector<std::string> sc;


	while (1) {
		pos.push_back(str.find(delimiter, pos.empty() ? 0 : pos.back() + 1));
		if (pos.back() == std::string::npos) {
			pos.pop_back();
			break;
		}
	}

	pos.push_back(str.size());

	int delsize;
	for (unsigned int i; i < str.size(); i++) {
		if (pos.back() == pos[i]) { break; }
		if (i == 0) {delsize = 0;}
		else {delsize = delimiter.size();}
		sc.push_back(str.substr(pos[i] + delsize, pos[i + 1] - pos[i] - delsize));
	}

	return sc;
}


void helpers::clearerrors() {
	while (glGetError() != GL_NO_ERROR);
}

bool helpers::logcall(int line, const char* fn, const char* filename) {
	GLenum error;
	while ((error = glGetError())) {
		std::string tmp;
		switch (error) {
		case (GL_INVALID_ENUM): {tmp = "GL_INVALID_ENUM"; break;}
		case (GL_INVALID_VALUE): {tmp = "GL_INVALID_VALUE"; break;}
		case (GL_INVALID_OPERATION): {tmp = "GL_INVALID_OPERATION"; break;}
		case (0x0503): {tmp = "GL_STACK_OVERFLOW"; break;}
		case (0x0504): {tmp = "GL_STACK_UNDERFLOW"; break;}
		case (GL_OUT_OF_MEMORY) : {tmp = "GL_OUT_OF_MEMORY"; break;}
		default : {tmp = boost::lexical_cast<std::string>(error); break;}
		}
		print(boost::lexical_cast<std::string>(tmp)
			  + std::string(" at line ")
			  + boost::lexical_cast<std::string>(line)
			  + std::string(" in function ")
			  + std::string(fn)
			  + std::string(" in file : ")
			  + std::string(filename)
			  , messages::Error);
		return false;
	}
	return true;
}



template<typename T>
GLsizeiptr helpers::vectorsizeof(const typename std::vector<T>& vec) {
	return (GLsizeiptr)(sizeof(T) * vec.size());
}



float helpers::clamp(float value, float min, float max) {
	return fmin(fmax(value, min), max);
}



bool helpers::replace(std::string& str, const std::string& from, const std::string& to) {
	size_t start_pos = str.find(from);
	if (start_pos == std::string::npos) {
		return false;
	}
	str.replace(start_pos, from.length(), to);
	return true;
}


void helpers::replaceall(std::string& str, const std::string& from, const std::string& to) {
	if (from.empty()) {
		return;
	}
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
	}
}
