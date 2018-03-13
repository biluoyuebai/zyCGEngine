#include "zyGLWindow.h"
#include <iostream>
#include "zyGLKeyboardListener.h"
using namespace zyLib;
void GLWindow::default_framebuffer_resize_callback(GLFWwindow * window, int width, int height)
{
	int twidth = 0, theight = 0;
	glfwGetWindowSize(window, &width, &height);
	if (width *  (static_cast<float>(theight) / twidth) < height)
		glViewport(0, 0, height * 4.0f / 3, height);
	else
		glViewport(0, 0, width, width * 3.0f / 4);
	// glViewport(0, 0, width, height);
}
//void GLWindow::set_display_mode(const GLbitfield & mode)
//{
//	this->m_displayField = mode;
//}
//void GLWindow::set_background_color(GLfloat r, GLfloat g, GLfloat b, GLfloat a /* = 1.0f */)
//{
//	this->m_backgroundColor = glm::vec4{ r,g,b,a };
//}
const std::string & GLWindow::get_title() const
{
	return m_title;
}
void GLWindow::set_scroll_callback(GLFWscrollfun func)
{
	glfwSetScrollCallback(m_pWindow, func);
}
void GLWindow::set_key_callback(GLFWkeyfun func)
{
	glfwSetKeyCallback(m_pWindow, func);
}
void GLWindow::set_mouse_move_callback(GLFWcursorvosfun func)
{
	glfwSetCursorPosCallback(m_pWindow, func);
}
GLWindow::GLWindow(const char * const _title /* = "default window" */, const std::size_t & _width /* = 1280 */, const std::size_t & _height /* = 960 */, FramebufferResizeCallback * fc /* = GLWindow::default_framebuffer_resize_callback */) 
	: m_title(_title), m_pFramebufferResizeCallback(fc)/*, m_displayField(GL_COLOR_BUFFER_BIT), m_backgroundColor(0.2f, 0.3f, 0.3f, 1.0f)*/
{
	m_pWindow = glfwCreateWindow(_width, _height, _title, nullptr, nullptr);
	if (m_pWindow == nullptr)
	{
		glfwTerminate();
		throw std::runtime_error("failed to create glfw window");
	}
	glfwMakeContextCurrent(m_pWindow);
	glfwSetFramebufferSizeCallback(m_pWindow,
		m_pFramebufferResizeCallback);
	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
	{
		glfwTerminate();
		throw std::runtime_error("failed to initialize glad");
	}
	glEnable(GL_DEPTH_TEST);
	glfwSetKeyCallback(m_pWindow, GLKeyboardListener::key_callback);
}
GLWindow::~GLWindow()
{
	glfwTerminate();
}
void GLWindow::display() const
{
	glfwSwapBuffers(m_pWindow);
}
bool GLWindow::should_close() const
{
	return glfwWindowShouldClose(m_pWindow);
}
ZGLWindow::ZGLWindow(const char * const title /* = "default window" */, const std::size_t & width /* = 1200 */, const std::size_t & height /* = 960 */, GLWindow::FramebufferResizeCallback * fc /* = GLWindow::default_framebuffer_resize_callback */)
	: data{ new T{title, width, height} } {}
void ZGLWindow::reset(const char * const title /* = "default window" */, const std::size_t & width /* = 1200 */, const std::size_t & height /* = 960 */, GLWindow::FramebufferResizeCallback * fc /* = GLWindow::default_framebuffer_resize_callback */)
{
	data.reset(new T{ title, width, height });
}