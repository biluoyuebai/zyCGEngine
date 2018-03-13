#pragma once
#include "zyGLPrerequisites.h"
#include "zyCGMath.h"
#include "zyVector.hpp"
#include "zyGLMaterial.h"
#include <string>
namespace zyLib
{
	//struct VectorData
	//{
	//	Vector3D vertex;
	//	Color3D color;
	//	Normal normal;
	//	TexCoord texcoord;
	//};
	class GLMesh
	{
	protected:
		const char * src_name;
		ZVector<Vector3D> vertices;
		ZVector<Color3D> colors;
		ZVector<Normal> normals;
		ZVector<GLuint> indices;
		ZGLMaterial material;
		GLuint vao;
		GLuint vbo;
		GLuint ebo;
	protected:
		void connect_opengl();
		void detach_opengl();
	public:
		GLMesh(crv<ZVector<Vector3D>> vert, crv<ZVector<Color3D>> col, crv<ZVector<Normal>> norm, crv<ZVector<GLuint>> i, crv<ZGLMaterial> m);
		GLMesh(crv<GLMesh> arg);
		GLMesh(GLMesh && arg);
		GLMesh & operator=(crv<GLMesh> arg);
		GLMesh & operator=(GLMesh && arg);
		~GLMesh();
		ZVector<Vector3D> & get_vertices();
		ZVector<Color3D> & get_colors();
		ZVector<Normal> & get_normals();
		ZGLMaterial & get_material();
		crv<ZVector<Vector3D>> get_vertices() const;
		crv<ZVector<Color3D>> get_colors() const;
		crv<ZVector<Normal>> get_normals() const;
		crv<ZGLMaterial> get_material() const;
		bool has_vertices() const;
		bool has_colors() const;
		bool has_normals() const;
		bool has_material() const;
		void do_rendering() const;
	};
	TCCDefaultAll(GLMesh, ZGLMesh)
}