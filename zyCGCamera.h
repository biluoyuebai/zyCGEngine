#pragma once
#include "zyCGMath.h"
#include "zyGLPrerequisites.h"
namespace zyLib
{
	class GLKeyboardListener;
	class GLCameraParameters
	{
		friend class GLKeyboardListener;
	public:
		float vx, vy, vz;
		int kx, ky, kz;
		int mkx, mky, mkz;
		//bool ix, iy, iz;
		float vpitch, vyaw, vroll;
		int kpitch, kyaw, kroll;
		int mkpitch, mkyaw, mkroll;
		//bool ipitch, iyaw, iroll;
#define default_velocity 0.05f
	public:
		GLCameraParameters(crv<float> _vx = default_velocity, crv<float> _vy = default_velocity, crv<float> _vz = default_velocity,
			crv<int> _kx = GLFW_KEY_D, crv<int> _mkx = GLFW_KEY_A,
			crv<int> _ky = GLFW_KEY_I, crv<int> _mky = GLFW_KEY_K,
			crv<int> _kz = GLFW_KEY_W, crv<int> _mkz = GLFW_KEY_S,
			crv<float> _vpitch = default_velocity, crv<float> _vyaw = default_velocity, crv<float> _vroll = default_velocity,
			crv<int> _kpitch = GLFW_KEY_E, crv<int> _mkpitch = GLFW_KEY_Q,
			crv<int> _kyaw = GLFW_KEY_U, crv<int> _mkyaw = GLFW_KEY_J,
			crv<int> _kroll = GLFW_KEY_X, crv<int> _mkroll = GLFW_KEY_Z);
	};
	TCCDefaultAll(GLCameraParameters, ZGLCameraListener)
		class CGCamera
	{
		friend class GLKeyboardListener;
	protected:
		ZGLCameraListener params;
		Vector3D up, front, right, pos;
		glm::mat4 perspective;
	public:
		CGCamera(crv<Vector3D> pos = Vector3D{ 0.0f, 0.0f, 3.0f }, crv<Vector3D> up = Vector3D{ 0.f, 1.f, 0.f }, crv<Vector3D> front = Vector3D{ 0.f, 0.f, -1.f }, crv<ZGLCameraListener> _listener = new GLCameraParameters{}, crv<glm::mat4> perspective = glm::perspective(glm::radians(45.f), 4.f / 3, 0.1f, 20000.f));
		Vector3D get_pos() const;
		glm::mat4 get_look_at() const;
		crv<glm::mat4> get_perspective() const;
		void pitch(crv<float> angle);
		void yaw(crv<float> angle);
		void roll(crv<float> angle);
		void move_x(crv<float> distance);
		void move_y(crv<float> distance);
		void move_z(crv<float> distance);
	};
	TCCDefaultAll(CGCamera, ZCGCamera)
}