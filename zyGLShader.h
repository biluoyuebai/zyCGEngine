#pragma once
#include "zyGLPrerequisites.h"
#include "zyResource.hpp"
namespace zyLib
{
	class ZGLVertexShader;
	class ZGLFragmentShader;
	class GLShader :
		my_implements IResource
	{
	public:
		friend class ZGLVertexShader;
		friend class ZGLFragmentShader;
	protected:
		GLuint ID;
	public:
		GLShader(const GLuint id);
		GLShader(const GLShader &) = delete;
		GLShader(GLShader &&) = default;
		GLShader & operator=(const GLShader &) = delete;
		GLShader & operator=(GLShader &&) = default;
		const GLuint get_id() const;
		virtual ~GLShader();
		virtual void read_source(const char * const & path);
	public:
		static const nullptr_t from_string;
	};
	class GLVertexShader : public GLShader
	{
	public:
		GLVertexShader(const char * const path);
		GLVertexShader(const char *const source, std::nullptr_t tag);
	};
	class GLFragmentShader : public GLShader
	{
	public:
		GLFragmentShader(const char * const path);
		GLFragmentShader(const char *const source, std::nullptr_t tag);
	};
	class ZGLVertexShader :
		my_extends ZGLObject
	{
		using T = GLVertexShader;
	public:
		TCCUniqueDefault(ZGLVertexShader)
		TCCBackDoor(ZGLVertexShader)
	};
	class ZGLFragmentShader :
		my_extends ZGLObject
	{
		using T = GLFragmentShader;
	public:
		TCCUniqueDefault(ZGLFragmentShader)
		TCCBackDoor(ZGLFragmentShader)
	};
}