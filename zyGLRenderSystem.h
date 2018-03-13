#pragma once
#include "zyGLPrerequisites.h"
#include "zyGLGPUProgram.h"
#include "zyCGSceneNode.h"
#include "zyGLWindow.h"
#include "zyCGCamera.h"
#include <functional>
#include "zyList.hpp"
#include "zyGLKeyboardListener.h"
namespace zyLib
{
	class GLRenderUnit
	{
	protected:
		ZSceneNode scene_node;
		ZCGParticleNode particle_node;
		ZGLProgram program;
		std::function<void(lrv<ZSceneNode>, lrv<ZGLProgram>, lrv<ZGLWindow>, lrv<ZCGCamera>)> func_of_scene;
		std::function<void(lrv<ZCGParticleNode>, lrv<ZGLProgram>, lrv<ZGLWindow>, lrv<ZCGCamera>)> func_of_particle;
	public:
		GLRenderUnit(crv<ZSceneNode> scene_node, crv<ZGLProgram> program, decltype(func_of_scene) func);
		GLRenderUnit(crv<ZCGParticleNode> particle_node, crv<ZGLProgram> program, decltype(func_of_particle) func);
		TPAll(scene_node)
		TPAll(particle_node)
		TPAll(program)
		TPAll(func_of_scene)
		TPAll(func_of_particle)
	};
	TCCDefaultAll(GLRenderUnit, ZGLRenderUnit)
	class GLRenderSystem : my_implements ISingleton<GLRenderSystem>
	{
	protected:
		List<ZGLRenderUnit> render_list;
	public:
		GLRenderSystem(crv<List<ZGLRenderUnit>> list = List<ZGLRenderUnit>{});
		GLRenderSystem & add_unit(crv<ZGLRenderUnit> list);
		GLRenderSystem & add_unit(ZGLRenderUnit && list);
		// void delete_by_scene_node(crv<ZSceneNode> scene_node);
		void rendering(rv<ZCGCamera> camera, rv<ZGLWindow> window);
	};
	TCCUncopyAll(GLRenderSystem, ZGLRenderSystem)
}