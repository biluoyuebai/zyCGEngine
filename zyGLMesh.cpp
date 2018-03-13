#include "zyGLMesh.h"
using namespace zyLib;
void GLMesh::connect_opengl()
{
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	if (indices != nullptr)
		glGenBuffers(1, &ebo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	auto & textures = material->get_texcoord();
	auto size_of_vertices = sizeof(Vector3D) * (vertices != nullptr ? vertices->size() : 0);
	auto size_of_colors = sizeof(Color3D) * (colors != nullptr ? colors->size() : 0);
	auto size_of_normals = sizeof(Normal) * (normals != nullptr ? normals->size() : 0);
	auto size_of_textures = sizeof(TexCoord) * (material != nullptr ? textures->size() : 0);
	glBufferData(GL_ARRAY_BUFFER, size_of_vertices + size_of_colors + size_of_normals + size_of_textures, nullptr, GL_STATIC_DRAW);
	if (vertices != nullptr)
		glBufferSubData(GL_ARRAY_BUFFER, 0, size_of_vertices, vertices->data());
	if (colors != nullptr)
		glBufferSubData(GL_ARRAY_BUFFER, size_of_vertices, size_of_colors, colors->data());
	if (normals != nullptr)
		glBufferSubData(GL_ARRAY_BUFFER, size_of_vertices + size_of_colors, size_of_normals, normals->data());
	if (material != nullptr)
		glBufferSubData(GL_ARRAY_BUFFER, size_of_vertices + size_of_colors + size_of_normals, size_of_textures, textures->data());
	if (indices != nullptr)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices->size(), indices->data(), GL_STATIC_DRAW);
	}
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *)(size_of_vertices));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void *)(size_of_vertices + size_of_colors));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, (void *)(size_of_vertices + size_of_colors + size_of_normals));
	glEnableVertexAttribArray(3);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
GLMesh::GLMesh(crv<ZVector<Vector3D>> vert, crv<ZVector<Color3D>> col, crv<ZVector<Normal>> norm, crv<ZVector<GLuint>> in, crv<ZGLMaterial> m)
	: src_name{ nullptr }, vertices{ vert }, colors{ col }, normals{ norm }, indices{ in }, material{ m },
	vao{ 0 }, vbo{ 0 }, ebo{ 0 }
{
	connect_opengl();
}
GLMesh::GLMesh(crv<GLMesh> arg)
	: src_name{ arg.src_name }, vertices{ arg.vertices.copy() }, colors{ arg.colors.copy() }, normals{ arg.normals.copy() }, material{ arg.material }, indices{ arg.indices.copy() },
	vao{ 0 }, vbo{ 0 }, ebo{ 0 }
{
	connect_opengl();
}
GLMesh::GLMesh(GLMesh && arg)
	: src_name{ std::move(arg.src_name) }, vertices{ std::move(arg.vertices) }, colors{ std::move(arg.colors) }, normals{ std::move(arg.normals) }, material{ std::move(arg.material) }, indices{ std::move(arg.indices) },
	vao{ std::move(arg.vao) }, vbo{ std::move(arg.vbo) }, ebo{ std::move(arg.ebo) }
{
	arg.vao = arg.vbo = arg.ebo = 0;
}
void GLMesh::detach_opengl()
{
	if (vao)
	{
		glDeleteVertexArrays(1, &vao);
		glDeleteBuffers(1, &vbo);
	}
	if (ebo)
		glDeleteBuffers(1, &ebo);
}
GLMesh::~GLMesh()
{
	detach_opengl();
}
void GLMesh::do_rendering() const
{
	glBindVertexArray(vao);
	if (indices != nullptr)
		glDrawElements(GL_TRIANGLES, indices->size(), GL_UNSIGNED_INT, 0);
	else
		glDrawArrays(GL_TRIANGLES, 0, vertices->size());
}
ZVector<Vector3D> & GLMesh::get_vertices()
{
	return vertices;
}
ZVector<Color3D> & GLMesh::get_colors()
{
	return colors;
}
ZVector<Normal> & GLMesh::get_normals()
{
	return normals;
}
ZGLMaterial & zyLib::GLMesh::get_material()
{
	return material;
}
crv<ZVector<Vector3D>> GLMesh::get_vertices() const
{
	return vertices;
}
crv<ZVector<Color3D>> GLMesh::get_colors() const
{
	return colors;
}
crv<ZVector<Normal>> GLMesh::get_normals() const
{
	return normals;
}
crv<ZGLMaterial> GLMesh::get_material() const
{
	return material;
}
bool GLMesh::has_vertices() const
{
	return vertices != nullptr;
}
bool GLMesh::has_colors() const
{
	return colors != nullptr;
}
bool GLMesh::has_normals() const
{
	return normals != nullptr;
}
bool zyLib::GLMesh::has_material() const
{
	return material != nullptr;
}
GLMesh & GLMesh::operator=(crv<GLMesh> arg)
{
	src_name = arg.src_name;
	vertices = arg.vertices.copy();
	colors = arg.colors.copy();
	normals = arg.normals.copy();
	indices = arg.indices.copy();
	material = arg.material;
	detach_opengl();
	connect_opengl();
	return *this;
}
GLMesh & GLMesh::operator=(GLMesh && arg)
{
	src_name = std::move(arg.src_name);
	vertices = std::move(arg.vertices);
	colors = std::move(arg.colors);
	normals = std::move(arg.normals);
	indices = std::move(arg.indices);
	material = std::move(arg.material);
	std::swap(vao, arg.vao);
	std::swap(vbo, arg.vbo);
	std::swap(ebo, arg.ebo);
	return *this;
}