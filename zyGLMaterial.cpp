#include "zyGLMaterial.h"
using namespace zyLib;
GLMaterial::GLMaterial(crv<ZVector<TexCoord>> _texcoord, crv<ZGLTexture2D> _diffuse_texture, crv<ZGLTexture2D> _specular_texture, crv<GLfloat> _diffuse_ratio, crv<GLfloat> _specular_ratio, crv<GLint> _power /* = 32 */)
	: texcoord{ _texcoord }, diffuse_texture{ _diffuse_texture }, specular_texture{ _specular_texture }, diffuse_ratio{ _diffuse_ratio }, specular_ratio{ _specular_ratio }, power{ _power } {}
ZGLTexture2D & GLMaterial::get_diffuse_texture()
{
	return diffuse_texture;
}
const ZGLTexture2D & GLMaterial::get_diffuse_texture() const
{
	return diffuse_texture;
}
ZGLTexture2D & GLMaterial::get_specular_texture()
{
	return specular_texture;
}
const ZGLTexture2D & GLMaterial::get_specular_texture() const
{
	return specular_texture;
}
GLfloat GLMaterial::get_diffuse_ratio() const
{
	return diffuse_ratio;
}
GLfloat GLMaterial::get_specular_ratio() const
{
	return specular_ratio;
}
GLint GLMaterial::get_power() const
{
	return power;
}
void GLMaterial::set_diffuse_ratio(GLfloat dr)
{
	diffuse_ratio = dr;
}
void GLMaterial::set_specular_ratio(GLfloat sr)
{
	specular_ratio = sr;
}
void GLMaterial::set_power(GLint p)
{
	power = p;
}
ZVector<TexCoord> & GLMaterial::get_texcoord()
{
	return texcoord;
}
const ZVector<TexCoord> & GLMaterial::get_texcoord() const
{
	return texcoord;
}