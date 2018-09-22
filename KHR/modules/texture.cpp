#include "texture.h"


texture::texture::texture(std::string filename, texturetype type) : _filename(filename),
	_type(type) {}



void texture::texture::init(int internalindex) {
	_internalindex = internalindex;

	gl(glGenTextures(1, &_handle));

	bind();

	// set the texture wrapping parameters
	gl(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
					   GL_REPEAT));	// set texture wrapping to GL_REPEAT (default wrapping method)
	gl(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

	// set texture filtering parameters
	gl(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	gl(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

	// load image, create texture and generate mipmaps
	int width, height, channels = 0;

	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(_filename.c_str(), &width, &height, &channels, 0);

	GLenum tmp = 0;
	if (channels == 3) {tmp = GL_RGB;}
	if (channels == 4) {tmp = GL_RGBA;}


	if (data) {
		gl(glTexImage2D(GL_TEXTURE_2D, 0, tmp, width, height, 0, tmp, GL_UNSIGNED_BYTE, data));
		gl(glGenerateMipmap(GL_TEXTURE_2D));
	}
	else {helpers::print("Failed to load texture : " + _filename, helpers::messages::Error);}
	stbi_image_free(data);

}

void texture::texture::bind() {
	gl(glActiveTexture(GL_TEXTURE0 + _internalindex));
	gl(glBindTexture(GL_TEXTURE_2D,
					 _handle)); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
}

void texture::texture::dispose() {
	gl(glBindTexture(GL_TEXTURE_2D, 0));
	gl(glDeleteTextures(1, &_handle));
}


texture::texture::~texture() {
}

