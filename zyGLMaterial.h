#pragma once
#include "zyGLPrerequisites.h"
#include "zyGLTexture.h"
#include "zyCGMath.h"
#include "zyVector.hpp"
namespace zyLib
{
	class GLMaterial
	{
	protected:
		ZVector<TexCoord> texcoord;
		ZGLTexture2D diffuse_texture;
		ZGLTexture2D specular_texture;
		GLfloat diffuse_ratio;
		GLfloat specular_ratio;
		GLint power;
	public:
		GLMaterial(crv<ZVector<TexCoord>> _texcoord, crv<ZGLTexture2D> _diffuse_texture, crv<ZGLTexture2D> _specular_texture,
			crv<GLfloat> _diffuse_ratio, crv<GLfloat> _specular_ratio, crv<GLint> _power = 32);
		GLMaterial(crv<GLMaterial>) = delete;
		GLMaterial(GLMaterial &&) = default;
		GLMaterial & operator=(crv<GLMaterial>) = delete;
		GLMaterial & operator=(GLMaterial &&) = default;
		ZGLTexture2D & get_diffuse_texture();
		const ZGLTexture2D &get_diffuse_texture() const;
		ZGLTexture2D & get_specular_texture();
		const ZGLTexture2D & get_specular_texture() const;
		GLfloat get_diffuse_ratio() const;
		GLfloat get_specular_ratio() const;
		GLint get_power() const;
		void set_diffuse_ratio(GLfloat dr);
		void set_specular_ratio(GLfloat sr);
		void set_power(GLint p);
		ZVector<TexCoord> & get_texcoord();
		const ZVector<TexCoord> & get_texcoord() const;
	};
	class ZGLMaterial :
		my_extends ZGLObject
	{
		using T = GLMaterial;
	public:
		TCCDefault(ZGLMaterial)
		TCCBackDoor(ZGLMaterial)
	};
}