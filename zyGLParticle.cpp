#include "zyGLParticle.h"
namespace zyLib
{
	void GLParticle::connect_opengl()
	{
		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		auto size_of_points = sizeof(Vector3D) * (points != nullptr ? points->size() : 0);
		auto size_of_colors = sizeof(Color3D) * (colors != nullptr ? colors->size() : 0);
		glBufferData(GL_ARRAY_BUFFER, size_of_points + size_of_colors, nullptr, GL_STATIC_DRAW);
		if (points != nullptr)
			glBufferSubData(GL_ARRAY_BUFFER, 0, size_of_points, points->data());
		if (colors != nullptr)
			glBufferSubData(GL_ARRAY_BUFFER, size_of_points, size_of_colors, colors->data());
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *)(size_of_points));
		glEnableVertexAttribArray(1);
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	void GLParticle::detach_opengl()
	{
		if (vao)
		{
			glDeleteVertexArrays(1, &vao);
			glDeleteBuffers(1, &vbo);
		}
	}
	GLParticle::GLParticle(crv<ZVector<Vector3D>> points, crv<ZVector<Color3D>> colors)
		: points{ points }, colors{ colors }
	{
		connect_opengl();
	}
	GLParticle::GLParticle(crv<GLParticle> arg)
		: points{ arg.points.copy() }, colors{ arg.colors.copy() }, vao{ 0 }, vbo{ 0 }
	{
		connect_opengl();
	}
	GLParticle::GLParticle(rrv<GLParticle> arg)
		: points{ std::move(arg.points) }, colors{ std::move(arg.colors) },
		vao{ arg.vao }, vbo{ arg.vbo }
	{
		arg.vao = arg.vbo = 0;
	}
	lrv<GLParticle> GLParticle::operator=(crv<GLParticle> arg)
	{
		points = arg.points.copy();
		colors = arg.colors.copy();
		detach_opengl();
		connect_opengl();
		return *this;
	}
	lrv<GLParticle> GLParticle::operator=(rrv<GLParticle> arg)
	{
		points = std::move(arg.points);
		colors = std::move(arg.colors);
		std::swap(vao, arg.vao);
		std::swap(vbo, arg.vbo);
		return *this;
	}
	GLParticle::~GLParticle()
	{
		detach_opengl();
	}
	bool GLParticle::has_colors() const
	{
		return colors != nullptr;
	}
	void GLParticle::do_rendering() const
	{
		glBindVertexArray(vao);
		glDrawArrays(GL_POINTS, 0, points->size());
	}
}