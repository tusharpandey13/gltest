#pragma once
#include "glm/glm.hpp"

namespace light {

class directionallight {
private:
	float _diffuse, _specular, _ambient, _intensity;
	glm::vec3 _color, _direction;
	//ads
public:
	directionallight(glm::vec3 direction, glm::vec3 color, float ambient = 0.2, float diffuse = 0.5,
					 float specular = 1.0, float intensity = 1.0) ;
};

}
