#include "zyGLGPUProgram.h"
using namespace zyLib;
GLProgram::GLProgram() : ID{ glCreateProgram() } {}
GLProgram::~GLProgram()
{
	glDeleteProgram(ID);
}
GLProgram::GLProgram(const ZGLVertexShader & vert, const ZGLFragmentShader & frag)
	: GLProgram{}
{
	this->add_vertex_shader(vert);
	this->add_fragment_shader(frag);
	this->link_program();
}
void GLProgram::use() const
{
	glUseProgram(ID);
}
GLProgram & GLProgram::add_vertex_shader(const ZGLVertexShader & vert)
{
	glAttachShader(ID, vert->get_id());
	return *this;
}
GLProgram & GLProgram::add_fragment_shader(const ZGLFragmentShader & frag)
{
	glAttachShader(ID, frag->get_id());
	return *this;
}
void GLProgram::link_program()
{
	glLinkProgram(ID);
	int success;
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) throw std::runtime_error{ "failed to link program" };
}
void GLProgram::set_uniform(const char * const name, const GLfloat & value) const
{
	glUniform1fv(glGetUniformLocation(ID, name), 1, &value);
}
void GLProgram::set_uniform(const char * const name, const glm::vec2 & value) const
{
	glUniform2fv(glGetUniformLocation(ID, name), 1, &value[0]);
}
void GLProgram::set_uniform(const char *const name, const glm::vec3 & value) const
{
	glUniform3fv(glGetUniformLocation(ID, name), 1, &value[0]);
}
void GLProgram::set_uniform(const char * const name, const glm::vec4 & value) const
{
	glUniform4fv(glGetUniformLocation(ID, name), 1, &value[0]);
}
void GLProgram::set_uniform(const char * const name, const glm::mat4 & value) const
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, &value[0][0]);
}
void GLProgram::set_uniform(const char * const name, const GLTexture2D & value) const
{
	glUniform1i(glGetUniformLocation(ID, name), value.get_unit_num());
	value.active();
	glBindTexture(GL_TEXTURE_2D, value.get_id());
}
ZGLProgram & ZGLProgram::operator<<(ZGLVertexShader & vert)
{
	data->add_vertex_shader(vert);
	return *this;
}
ZGLProgram & ZGLProgram::operator<<(ZGLFragmentShader & frag)
{
	data->add_fragment_shader(frag);
	return *this;
}
void ZGLProgram::operator<<(std::nullptr_t arg)
{
	data->link_program();
}