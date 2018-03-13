#include "zyGLWindow.h"
#include "zyGLApplication.h"
#include "zyGLShader.h"
#include "zyGLGPUProgram.h"
#include "zyCGCamera.h"
#include "zyCGSceneNode.h"
#include "zyGLRenderSystem.h"
#include "zyGLUtility.h"
#include "zyCGSimpleGeometry.h"
#include "zyDeadlineTimer.hpp"
#include "zyGLRenderSystem.h"
#include <iostream>
#include <cstdlib>
#include <string>
using namespace zyLib;
#define test_raw(type) std::cout << sizeof(type) << std::endl
#define test_size(type) std::cout << sizeof(std::shared_ptr<type>) << std::endl
const char * vertex_shader_source =
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 3) in vec2 aTex;\n"
"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"
"out vec4 outColor;\n"
"out vec2 outTex;\n"
"void main()\n"
"{\n"
"   gl_Position = projection * view * model * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"	outTex = aTex;\n"
"}\0";
const char *fragment_shader_source =
"#version 330 core\n"
"out vec4 FragColor;\n"
"in vec2 outTex;\n"
"uniform sampler2D texture1;\n"
"uniform sampler2D texture2;\n"
"void main()\n"
"{\n"
"   FragColor = mix(texture(texture1, outTex), texture(texture2, outTex), 0.2);\n"
"}\n\0";
const char * particle_vertex_shader_source =
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"
"out vec4 outColor;\n"
"out vec2 outTex;\n"
"void main()\n"
"{\n"
"   gl_Position = projection * view * model * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"	gl_PointSize = 5;\n"
"	outColor = vec4(0.4,0.6,1.0,1.0);\n"
"}\0";
const char * particle_fragment_shader_source =
"#version 330 core\n"
"out vec4 FragColor;\n"
"in vec4 outColor;\n"
"void main()\n"
"{\n"
"   FragColor = outColor;\n"
"}\n\0";
int main()
{
	ZGLApplication app = new GLApplication{ 3,3 };
	ZGLWindow win = new GLWindow{ "test window", 800, 600 };
	ZGLVertexShader vert = new GLVertexShader{ vertex_shader_source, GLShader::from_string };
	ZGLFragmentShader frag = new GLFragmentShader{ fragment_shader_source, GLShader::from_string };
	ZGLProgram program = new GLProgram{ vert, frag };
	ZGLVertexShader vert_of_particle = new GLVertexShader{ particle_vertex_shader_source, GLShader::from_string };
	ZGLFragmentShader frag_of_particle = new GLFragmentShader{ particle_fragment_shader_source, GLShader::from_string };
	ZGLProgram program_of_particle = new GLProgram{ vert_of_particle, frag_of_particle };
	ZVector<Vector3D> position = cube_pos;
	//ZVector<Color3D> color = new Vector<Color3D>{ {CR_RED}, {CR_BLUE}, {CR_GREEN}, {CR_MAGENTA}, {CR_BLACK}, {CR_WHITE}, {CR_YELLOW}, {CR_CYAN} };
	//ZVector<GLuint> indices = new Vector<GLuint>{ 0,1,3,1,2,3,7,6,4,6,5,4,4,5,0,5,1,0,3,2,7,2,6,7,0,3,4,3,7,4,2,1,6,1,5,6 };
	ZGLMaterial material = new GLMaterial{ cube_tex, new GLTexture2D{"opengl.jpg", 0}, new GLTexture2D{"texture.jpg", 1}, 0.4f, 0.6f };
	ZCGCamera camera = new CGCamera{};
	ZCGEntity entity = new CGEntity{ new GLMesh{position, nullptr, nullptr, nullptr, material } };
	ZCGSceneNode scene_node = new CGSceneNode{ new Vector3D{0.f, 0.f,-5.f}, new Quaternion{glm::angleAxis(glm::radians(30.0f), glm::vec3{1,1,0})}, entity };
	ZGLRenderUnit render_unit = new GLRenderUnit{scene_node, program, 
	[](lrv<ZSceneNode> scene_node, lrv<ZGLProgram> program, lrv<ZGLWindow> window, lrv<ZCGCamera> camera)
	{
		program->use();
		auto & mesh = scene_node->get_entity()->get_mesh();
		auto mat_from_local_to_world = glm::translate(glm::mat4{}, *scene_node->get_pos()) * glm::mat4{ *scene_node->get_ori() };
		program->set_uniform("model", mat_from_local_to_world);
		program->set_uniform("view", camera->get_look_at());
		program->set_uniform("projection", camera->get_perspective());
		program->set_uniform("texture1", scene_node->get_entity()->get_mesh()->get_material()->get_diffuse_texture());
		program->set_uniform("texture2", scene_node->get_entity()->get_mesh()->get_material()->get_specular_texture());
		mesh->do_rendering();
} };
	ZCGParticleEntity partial_entity = new CGParticalEntity{ new GLParticle{position, nullptr} };
	ZCGParticleNode partial_node = new CGParticleNode{ new Vector3D{5.f,0.f,-5.f}, new Quaternion{}, partial_entity };
	ZGLRenderUnit partial_unit = new GLRenderUnit{partial_node, program_of_particle, 
	[](lrv<ZCGParticleNode> particle_node, lrv<ZGLProgram> program, lrv<ZGLWindow> window, lrv<ZCGCamera> camera)
	{
		program->use();
		auto mat_from_local_to_world = glm::translate(glm::mat4{}, *particle_node->get_pos()) * glm::mat4{ *particle_node->get_ori() };
		program->set_uniform("model", mat_from_local_to_world);
		program->set_uniform("view", camera->get_look_at());
		program->set_uniform("projection", camera->get_perspective());
		particle_node->get_entity()->get_mesh()->do_rendering();
	} };
	GLRenderSystem::get_mutable_instance().add_unit(render_unit).add_unit(partial_unit);
	glEnable(GL_PROGRAM_POINT_SIZE);
	while (!(win->should_close()))
	{
		GLRenderSystem::get_mutable_instance().rendering(camera, win);
		win->display();
		glfwPollEvents();
	}
	return 0;
}