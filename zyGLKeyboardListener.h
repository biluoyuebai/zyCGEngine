#pragma once
#include "zyGLPrerequisites.h"
#include <unordered_set>
#include "zyCGCamera.h"
#include "zySingleton.hpp"
namespace zyLib
{
	class GLKeyboardListener : my_implements ISingleton<GLKeyboardListener>
	{
	protected:
		std::unordered_set<int> key_event_array;
	public:
		void push_to_camera(rv<ZCGCamera> camera);
		static void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods);
	public:
		GLKeyboardListener();
		void clear_events();
		void push_event(int event);
		void pop_event(int event);
	};
	TCCUncopyAll(GLKeyboardListener, ZGLKeyboardListener)
}