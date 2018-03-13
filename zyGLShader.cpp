#include "zyGLShader.h"
#include <fstream>
#include <sstream>
using namespace zyLib;
const nullptr_t GLShader::from_string = nullptr;
GLShader::GLShader(const GLuint id) : ID{ id } {}
const GLuint GLShader::get_id() const
{
	return ID;
}
GLShader::~GLShader()
{
	glDeleteShader(ID);
}
void GLShader::read_source(const char * const & path)
{
	std::ifstream fin;
	fin.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fin.open(path);
	std::stringstream string_buffer;
	std::string tmp;
	string_buffer << fin.rdbuf();
	auto str = string_buffer.str();
	auto c_str = str.c_str();
	glShaderSource(this->ID, 1, &c_str, nullptr);
	glCompileShader(this->ID);
}
GLVertexShader::GLVertexShader(const char * const path)
	: GLShader{ glCreateShader(GL_VERTEX_SHADER) }
{
	this->read_source(path);
	int success;
	glGetShaderiv(this->ID, GL_COMPILE_STATUS, &success);
	if (!success) throw std::runtime_error("failed to compile vertex shader");
}
GLFragmentShader::GLFragmentShader(const char * const path)
	: GLShader{ glCreateShader(GL_FRAGMENT_SHADER) }
{
	this->read_source(path);
	int success;
	glGetShaderiv(this->ID, GL_COMPILE_STATUS, &success);
	if (!success) throw "failed to compile fragment shader";
}
GLVertexShader::GLVertexShader(const char *const source, std::nullptr_t tag)
	: GLShader{ glCreateShader(GL_VERTEX_SHADER) }
{
	glShaderSource(this->ID, 1, &source, nullptr);
	glCompileShader(this->ID);
	int success;
	glGetShaderiv(this->ID, GL_COMPILE_STATUS, &success);
	if (!success) throw std::runtime_error("failed to compile vertex shader");
}
GLFragmentShader::GLFragmentShader(const char *const source, std::nullptr_t tag)
	: GLShader{ glCreateShader(GL_FRAGMENT_SHADER) }
{
	glShaderSource(this->ID, 1, &source, nullptr);
	glCompileShader(this->ID);
	int success;
	glGetShaderiv(this->ID, GL_COMPILE_STATUS, &success);
	if (!success) throw std::runtime_error("failed to compile fragment shader");
}