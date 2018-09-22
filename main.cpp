#include <modules/window.h>
#include <modules/texture.h>

int main() {

	window w2(1920, 1080, "hello");

// *INDENT-OFF*
	mesh m1 = mesh(
	{
					  -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,0.0f, 0.0f,
					   0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,1.0f, 0.0f,
					   0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,1.0f, 1.0f,
					   0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,1.0f, 1.0f,
					  -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,0.0f, 1.0f,
					  -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,0.0f, 0.0f,

					  -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
					   0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 0.0f,
					   0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 1.0f,
					   0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 1.0f,
					  -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 0.0f, 1.0f,
					  -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 0.0f, 0.0f,

					  -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,1.0f, 0.0f,
					  -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,1.0f, 1.0f,
					  -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,0.0f, 1.0f,
					  -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,0.0f, 1.0f,
					  -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,0.0f, 0.0f,
					  -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,1.0f, 0.0f,

					   0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,1.0f, 0.0f,
					   0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,1.0f, 1.0f,
					   0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,0.0f, 1.0f,
					   0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,0.0f, 1.0f,
					   0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,0.0f, 0.0f,
					   0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,1.0f, 0.0f,

					  -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,0.0f, 1.0f,
					   0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,1.0f, 1.0f,
					   0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,1.0f, 0.0f,
					   0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,1.0f, 0.0f,
					  -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,0.0f, 0.0f,
					  -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,0.0f, 1.0f,

					  -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,0.0f, 1.0f,
					   0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,1.0f, 1.0f,
					   0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,1.0f, 0.0f,
					   0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,1.0f, 0.0f,
					  -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,0.0f, 0.0f,
					  -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f,
	},
	{},
	{
		texture::texture("resources/textures/container2.png", texture::texturetype::diffuse),
		texture::texture("resources/textures/container2_specular.png", texture::texturetype::specular),
		texture::texture("resources/textures/black.jpg", texture::texturetype::emission),

	}
	);

// *INDENT-ON*

	glm::mat4 trans;
//	TRS
	trans = glm::translate(trans, glm::vec3(0, 0, 3));
	trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));

	glm::mat4 trans1 ;
	trans1 = glm::rotate(trans1, glm::radians(-40.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	trans1 = glm::rotate(trans1, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	model md1({mesh(m1, trans1), mesh(m1, trans, glm::vec3(0.3, 0.4, 1), 0.2, 0.5, 1.0),
			   mesh(m1, glm::translate(trans, glm::vec3(0, -2, -3)), glm::vec3(1, 1, 1), 0.2, 0.8, 1.0)});
	md1.addshader(shader("resources/shaders/frag1.frag"));
	md1.addshader(shader("resources/shaders/vert1.vert"));

	w2.addmodel(md1);

	w2.run();

	return 0;
}
