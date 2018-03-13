#include "zyGLApplication.h"
using namespace zyLib;
GLApplication::GLApplication() : GLApplication{ 3,3 } {}
GLApplication::GLApplication(std::size_t major, std::size_t minor) : m_major{ major }, m_minor{ minor }
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}
ZGLApplication::ZGLApplication(std::size_t major, std::size_t minor)
	: data{ new T{major, minor} } {}
void ZGLApplication::reset(std::size_t major, std::size_t minor)
{
	data.reset(new T{ major, minor });
}