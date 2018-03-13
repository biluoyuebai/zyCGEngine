#pragma once
#include "zyGLShader.h"
#include "zyGLTexture.h"
#include "zyCGMath.h"
namespace zyLib
{
	class ZGLProgram;
	class GLProgram
	{
		friend class ZGLProgram;
	protected:
		const GLuint ID;
	public:
		GLProgram();
		GLProgram(const ZGLVertexShader & vert, const ZGLFragmentShader & frag);
		~GLProgram();
		GLProgram(const GLProgram &) = delete;
		GLProgram(GLProgram &&) = default;
		GLProgram & operator=(const GLProgram &) = delete;
		GLProgram & operator=(GLProgram &&) = default;
		void use() const;
		GLProgram & add_vertex_shader(const ZGLVertexShader & vert);
		GLProgram & add_fragment_shader(const ZGLFragmentShader & frag);
		void link_program();
		void set_uniform(const char * const name, const GLfloat & value) const;
		void set_uniform(const char * const name, const glm::vec2 & value) const;
		void set_uniform(const char *const name, const glm::vec3 & value) const;
		void set_uniform(const char * const name, const glm::vec4 & value) const;
		void set_uniform(const char * const name, const glm::mat4 & value) const;
		void set_uniform(const char * const name, const GLTexture2D & value) const;
	};
	class ZGLProgram :
		my_extends ZGLObject
	{
		using T = GLProgram;
	public:
		TCCDefault(ZGLProgram)
		TCCBackDoor(ZGLProgram)
		ZGLProgram & operator<<(ZGLVertexShader & vert);
		ZGLProgram & operator<<(ZGLFragmentShader & frag);
		void operator<<(std::nullptr_t arg);
	};
}