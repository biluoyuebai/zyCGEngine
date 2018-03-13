#pragma once
#include "zyGLPrerequisites.h"
#include "zyCGMath.h"
#include "zyVector.hpp"
namespace zyLib
{
	class GLParticle
	{
	protected:
		ZVector<Vector3D> points;
		ZVector<Color3D> colors;
		GLuint vao;
		GLuint vbo;
	protected:
		void connect_opengl();
		void detach_opengl();
	public:
		GLParticle(crv<ZVector<Vector3D>> points, crv<ZVector<Color3D>> colors);
		GLParticle(crv<GLParticle> arg);
		GLParticle(rrv<GLParticle> arg);
		lrv<GLParticle> operator=(crv<GLParticle> arg);
		lrv<GLParticle> operator=(rrv<GLParticle> arg);
		~GLParticle();
		TPAll(points)
		TPAll(colors)
		bool has_colors() const;
		void do_rendering() const;
	};
	TCCDefaultAll(GLParticle, ZGLPartical)
}