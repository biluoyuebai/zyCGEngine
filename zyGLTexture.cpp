#include "zyGLTexture.h"
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.hpp>
#endif // !STB_IMAGE_IMPLEMENTATION
using namespace zyLib;
GLTexture2D::GLTexture2D(unsigned int unit_num)
	: texture_unit_num{ unit_num }
{
	glGenTextures(1, &ID);
}
void GLTexture2D::read_source(const char * const & path)
{
	glBindTexture(GL_TEXTURE_2D, ID);
	stbi_set_flip_vertically_on_load(true);
	auto data = stbi_load(path, &width, &height, &channels, 0);
	if (!data) throw std::runtime_error("failed to load picture");
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	set_fill(GL_LINEAR);
	set_filter(GL_LINEAR);
	stbi_image_free(data);
}
GLTexture2D::GLTexture2D(const char * const & path, unsigned int unit_num /* = 0 */)
	: GLTexture2D{ unit_num }
{
	read_source(path);
}
GLTexture2D::GLTexture2D(const float * const & data, crv<size_t> width, crv<size_t> height, unsigned int unit_num /* = 0 */)
	: GLTexture2D{ unit_num }
{
	glBindTexture(GL_TEXTURE_2D, ID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_FLOAT, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	set_fill(GL_LINEAR);
	set_filter(GL_LINEAR);
}
GLuint GLTexture2D::get_id() const
{
	return ID;
}
unsigned int GLTexture2D::get_unit_num() const
{
	return texture_unit_num;
}
int zyLib::GLTexture2D::get_width() const
{
	return width;
}
int zyLib::GLTexture2D::get_height() const
{
	return height;
}
int zyLib::GLTexture2D::get_channels() const
{
	return channels;
}
void GLTexture2D::set_fill(GLenum type)
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, type);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, type);
}
void GLTexture2D::set_filter(GLenum type)
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, type);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, type);
}
void zyLib::GLTexture2D::active() const
{
	glActiveTexture(this->texture_unit_num + GL_TEXTURE0);
}
GLTexture2D::~GLTexture2D()
{
	glDeleteTextures(1, &ID);
}