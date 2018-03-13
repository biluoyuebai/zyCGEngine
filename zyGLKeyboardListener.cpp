#include "zyGLKeyboardListener.h"
using namespace zyLib;
GLKeyboardListener::GLKeyboardListener()
	: key_event_array{} {}
void GLKeyboardListener::push_to_camera(rv<ZCGCamera> camera)
{
	for (auto & x : key_event_array)
	{
		if (x == camera->params->kx)
			camera->move_x(camera->params->vx);
		else if (x == camera->params->ky)
			camera->move_y(camera->params->vy);
		else if (x == camera->params->kz)
			camera->move_z(camera->params->vz);
		else if (x == camera->params->kpitch)
			camera->pitch(camera->params->vpitch);
		else if (x == camera->params->kyaw)
			camera->yaw(camera->params->vyaw);
		else if (x == camera->params->vroll)
			camera->roll(camera->params->vroll);
		else if (x == camera->params->mkx)
			camera->move_x(-camera->params->vx);
		else if (x == camera->params->mky)
			camera->move_y(-camera->params->vy);
		else if (x == camera->params->mkz)
			camera->move_z(-camera->params->vz);
		else if (x == camera->params->mkpitch)
			camera->pitch(-camera->params->vpitch);
		else if (x == camera->params->mkyaw)
			camera->yaw(-camera->params->vyaw);
		else if (x == camera->params->mkroll)
			camera->roll(-camera->params->vroll);
	}
}
void GLKeyboardListener::clear_events()
{
	// key_event_array.clear();
}
void GLKeyboardListener::push_event(int event)
{
	key_event_array.insert(event);
}
void GLKeyboardListener::pop_event(int event)
{
	key_event_array.erase(event);
}
void GLKeyboardListener::key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	if (action != GLFW_RELEASE)
		GLKeyboardListener::get_mutable_instance().push_event(key);
	else
		GLKeyboardListener::get_mutable_instance().pop_event(key);
}