#include "camera.h"

camera::camera::camera(glm::vec3 pos, double* deltatime) : position(pos), _deltatime(deltatime){}

void camera::camera::move(direction MoveDirection/*, float deltatime*/){


		float _speed = speed * (*_deltatime);
		switch(MoveDirection){
		case(0) : {position += _speed * _front; break;}
		case(1) : {position -= _speed * _front; break;}
		case(2) : {position -= glm::normalize(glm::cross(_front, _up)) * _speed; break;}
		case(3) : {position += glm::normalize(glm::cross(_front, _up)) * _speed; break;}
		}
}

void camera::camera::turn(float dx, float dy){

//	_yaw = helpers::clamp(_yaw + (dx * sensitivity), -89.0, 0.0);
	_yaw += dx * sensitivity;
	_pitch = helpers::clamp(_pitch + (dy * sensitivity), -89.0, 89.0);

	_front = glm::normalize(glm::vec3(cos(glm::radians(_yaw)) * cos(glm::radians(_pitch)),
									  sin(glm::radians(_pitch)),
									  sin(glm::radians(_yaw)) * cos(glm::radians(_pitch))));

}

glm::mat4 camera::camera::view(){
	glm::vec3 tmp = glm::normalize(position - glm::vec3(0.0, 0.0, 0.0));
	glm::vec3 tmp2right = glm::normalize(glm::cross(_up, tmp));
	_up = glm::cross(tmp, tmp2right);
	return glm::lookAt(position, position + _front, _up);
}
