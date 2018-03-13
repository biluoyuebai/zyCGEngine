#pragma once
#include "zyGLPrerequisites.h"
#include "zyResource.hpp"
namespace zyLib
{
	class GLTexture2D :
		my_implements IResource
	{
	protected:
		GLuint ID;
		unsigned int texture_unit_num;
		int width, height;
		int channels;
	public:
		GLTexture2D(unsigned int unit_num);
		GLTexture2D(const char * const & path, unsigned int unit_num = 0);
		GLTexture2D(const float * const & data, crv<size_t> width, crv<size_t> height, unsigned int unit_num = 0);
		~GLTexture2D();
		GLTexture2D(crv<GLTexture2D>) = delete;
		GLTexture2D(GLTexture2D &&) = default;
		GLTexture2D & operator=(crv<GLTexture2D>) = delete;
		GLTexture2D & operator=(GLTexture2D &&) = default;
		void read_source(const char * const & path);
		unsigned int get_unit_num() const;
		int get_width() const;
		int get_height() const;
		int get_channels() const;
		void set_fill(GLenum type);
		void set_filter(GLenum type);
		void active() const;
		GLuint get_id() const;
	};
	TCCUncopyAll(GLTexture2D, ZGLTexture2D)
}