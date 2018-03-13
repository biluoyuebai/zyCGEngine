#pragma once
#include "zyCGPrerequisites.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
namespace zyLib
{
	class ZGLObject :
		my_extends ZObject
	{
	public:
		virtual ~ZGLObject() = default;
	};
}