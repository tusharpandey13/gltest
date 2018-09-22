#include "light.h"





light::directionallight::directionallight(glm::vec3 direction, glm::vec3 color, float ambient,
										  float diffuse, float specular, float intensity)
	: _direction(direction), _color(color), _ambient(ambient), _diffuse(diffuse), _specular(specular),
	  _intensity(intensity) {

}
