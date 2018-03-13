#pragma once
#include "zyGLPrerequisites.h"
#include <string>
#include <glm/glm.hpp>
namespace zyLib
{
	class GLWindow
	{
	public:
		static_func void default_framebuffer_resize_callback(GLFWwindow * window, int width, int height);
	my_out_type:
		using FramebufferResizeCallback = void(GLFWwindow *, int, int);
	public:
		FramebufferResizeCallback * m_pFramebufferResizeCallback;
		GLFWwindow * m_pWindow;
		int get_width(void) const
		{
			int width, height;
			glfwGetWindowSize(m_pWindow, &width, &height);
			return width;
		}
		int get_height(void) const
		{
			int width, height;
			glfwGetWindowSize(m_pWindow, &width, &height);
			return height;
		}
		float get_aspect(void) const
		{
			int width, height;
			glfwGetWindowSize(m_pWindow, &width, &height);
			return static_cast<float>(width) / height;
		}
	public:
		std::string m_title;
		const std::string &GLWindow::get_title() const;
		//GLbitfield m_displayField;
		//glm::vec4 m_backgroundColor;
	my_set_func:
		//void set_display_mode(const GLbitfield & mode);
		//void set_background_color(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1.0f);
		void set_scroll_callback(GLFWscrollfun func);
		void set_key_callback(GLFWkeyfun func);
		void set_mouse_move_callback(GLFWcursorvosfun func);
	my_ctor:
		GLWindow(const char * const _title = "default window", const std::size_t & _width = 1280, const std::size_t & _height = 960, FramebufferResizeCallback * fc = GLWindow::default_framebuffer_resize_callback);
		GLWindow(const GLWindow &) = delete;
		GLWindow(GLWindow &&) = default;
	my_dtor:
		~GLWindow();
	my_func:
		void display() const;
		bool should_close() const;
	my_opr:
		GLWindow & operator=(const GLWindow &) = delete;
		GLWindow & operator=(GLWindow &&) = default;
	};
	class ZGLWindow :
		my_extends ZGLObject,
		my_implements IEqualable<ZGLWindow>
	{
		using T = GLWindow;
	public:
		TCCDefault(ZGLWindow)
	public:
		ZGLWindow(const char * const title = "default window", const std::size_t & width = 1200, const std::size_t & height = 960, GLWindow::FramebufferResizeCallback * fc = GLWindow::default_framebuffer_resize_callback);
		void reset(const char * const title = "default window", const std::size_t & width = 1200, const std::size_t & height = 960, GLWindow::FramebufferResizeCallback * fc = GLWindow::default_framebuffer_resize_callback);
	public:
		bool operator==(const ZGLWindow & rhs) const;
		TCCBackDoor(ZGLWindow)
	};
}