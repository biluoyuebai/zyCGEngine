#include "zyGLRenderSystem.h"
#include "zyGLUtility.h"
#include <iostream>
#include <algorithm>
using namespace zyLib;
zyLib::GLRenderUnit::GLRenderUnit(crv<ZSceneNode> scene_node, crv<ZGLProgram> program, decltype(func_of_scene) func)
	: scene_node{ scene_node }, program{ program }, func_of_scene{ func }, particle_node{ nullptr } {}
zyLib::GLRenderUnit::GLRenderUnit(crv<ZCGParticleNode> particle_node, crv<ZGLProgram> program, decltype(func_of_particle) func)
	: particle_node{ particle_node }, program{ program }, func_of_particle{ func }, scene_node{ nullptr } {}
//void zyLib::ZGLRenderSystem::tick(ZSceneNode & scene_node, ZGLProgram & program, ZGLWindow & window)
//{
//	glClearColor(CR_BACKGROUND, 1.0f);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	program->use();
//	auto & mesh = scene_node->get_entity()->get_mesh();
//	auto mat_from_local_to_world = glm::translate(glm::mat4{}, *scene_node->get_pos()) * glm::mat4{ *scene_node->get_ori() };
//	program->set_uniform("model", mat_from_local_to_world);
//	program->set_uniform("view", glm::perspective(glm::radians(45.f), 4.0f / 3, 0.1f, 100.0f));
//	mesh->do_rendering();
//	window->display();
//}
GLRenderSystem::GLRenderSystem(crv<List<ZGLRenderUnit>> list)
	: render_list{ list } {}
void GLRenderSystem::rendering(rv<ZCGCamera> camera, rv<ZGLWindow> window)
{
	glClearColor(CR_BLACK, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	GLKeyboardListener::get_mutable_instance().push_to_camera(camera);
	for (auto &x : render_list)
	{
		auto func_of_scene = x->get_func_of_scene();
		if (func_of_scene != nullptr && x->get_scene_node() != nullptr)
			func_of_scene(x->get_scene_node(), x->get_program(), window, camera);
		auto func_of_particle = x->get_func_of_particle();
		if (func_of_particle != nullptr && x->get_particle_node() != nullptr)
			func_of_particle(x->get_particle_node(), x->get_program(), window, camera);
	}
	GLKeyboardListener::get_mutable_instance().clear_events();
}
GLRenderSystem & GLRenderSystem::add_unit(crv<ZGLRenderUnit> list)
{
	render_list.push_back(list);
	return *this;
}
GLRenderSystem & GLRenderSystem::add_unit(ZGLRenderUnit && list)
{
	render_list.push_back(std::move(list));
	return *this;
}