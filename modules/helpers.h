#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <boost/lexical_cast.hpp>
//#include <QDebug>
#include <math.h>

#include <glad/glad.h>
//#include <GLFW/glfw3.h>

//the following are UBUNTU/LINUX ONLY terminal color codes.
#define RESET		"\033[0m"					/* Reset */
#define BLACK		"\033[30m"					/* Black */
#define RED			"\033[31m"					/* Red */
#define GREEN		"\033[32m"					/* Green */
#define YELLOW		"\033[33m"					/* Yellow */
#define BLUE		"\033[34m"					/* Blue */
#define MAGENTA		"\033[35m"					/* Magenta */
#define CYAN		"\033[36m"					/* Cyan */
#define WHITE		"\033[37m"					/* White */
#define BOLDBLACK	"\033[1m\033[30m"			/* Bold Black */
#define BOLDRED		"\033[1m\033[31m"			/* Bold Red */
#define BOLDGREEN	"\033[1m\033[32m"			/* Bold Green */
#define BOLDYELLOW	"\033[1m\033[33m"			/* Bold Yellow */
#define BOLDBLUE	"\033[1m\033[34m"			/* Bold Blue */
#define BOLDMAGENTA	"\033[1m\033[35m"			/* Bold Magenta */
#define BOLDCYAN	"\033[1m\033[36m"			/* Bold Cyan */
#define BOLDWHITE	"\033[1m\033[37m"				/* Bold White */
//	Usage:
//	std::cout << RED << "hello world" << RESET << std::endl;
//

#define ASSERT(x) if(!(x))  asm("int $3");
#define gl(x)  helpers::clearerrors(); x;  ASSERT(helpers::logcall(__LINE__, #x, __FILE__));

namespace helpers {

namespace messages {

enum message_type : int {
	Error = 0,
	Warning = 1,
	Info = 2,
	Undefined = -1
};
}

void print(std::string Message, messages::message_type Type);



template<typename T>
GLsizeiptr vectorsizeof(const typename std::vector<T>& vec);

std::vector<std::string> split(std::string str, std::string delimiter);



void clearerrors();

bool logcall(int line, const char* fn, const char* filename);

float clamp(float value, float min, float max);

bool replace(std::string& str, const std::string& from, const std::string& to);

void replaceall(std::string& str, const std::string& from, const std::string& to);

}

