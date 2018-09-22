#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#include <modules/helpers.h>



namespace camera {

enum direction : int {
	Forward = 0,
	Back = 1,
	Left = 2,
	Right = 3
};

class camera {
private:
	glm::vec3 _front = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 _up = glm::vec3(0.0, 1.0, 0.0);
	double* _deltatime;
	float _pitch = 0.0;
	float _yaw = -90.0;

public:
	glm::vec3 position;
	float speed = 1.5;
	float sensitivity = 0.15;

	camera() = default;
	camera(glm::vec3 position, double* deltatime);
	glm::mat4 view();
	void move(direction MoveDirection);
	void turn(float dx, float dy);

};


}



#endif // CAMERA_H
