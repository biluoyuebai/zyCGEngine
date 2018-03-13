#pragma once
#include "zyGLPrerequisites.h"
#include <utility>
namespace zyLib
{
	class GLApplication
	{
	my_out_type:
		using OpenGLVersion = std::pair<std::size_t, std::size_t>;
	my_prop:
		std::size_t m_major;
		std::size_t m_minor;
	my_ctor:
		GLApplication();
		GLApplication(std::size_t major, std::size_t minor);
		GLApplication(GLApplication &&) = default;
		GLApplication(const GLApplication &) = delete;
		GLApplication & operator=(const GLApplication &) = delete;
		GLApplication & operator=(GLApplication &&) = default;
		~GLApplication() = default;
	};
	class ZGLApplication :
		my_extends ZGLObject
	{
		using T = GLApplication;
	public:
		TCCUniqueDefault(ZGLApplication)
	public:
		ZGLApplication(std::size_t major, std::size_t minor);
		void reset(std::size_t major, std::size_t minor);
		TCCBackDoor(ZGLApplication)
	};
}