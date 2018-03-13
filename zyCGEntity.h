#pragma once
#include "zyCGPrerequisites.h"
#include "zyResource.hpp"
#include "zyGLMesh.h"
#include "zyGLTexture.h"
#include "zyGLParticle.h"
#include <assimp/Importer.hpp>
namespace zyLib
{
	template<typename type, class = std::enable_if_t<std::is_same_v<type, ZGLMesh> || std::is_same_v<type, ZGLPartical>>>
	class Entity :
		my_implements IResource
	{
	protected:
		type mesh;
		
		inline void read_source(const char * const & path)
		{
			// TO DO
		}
	public:
		Entity(const char * const & path)
		{
			read_source(path);
		}
		Entity(crv<type> m)
			: mesh{ m } {}
		TPAll(mesh)
	};
	template<typename type>
	TCCDefaultAll(Entity<type>, ZEntity)
	using CGEntity = Entity<ZGLMesh>;
	using ZCGEntity = ZEntity<ZGLMesh>;
	using CGParticalEntity = Entity<ZGLPartical>;
	using ZCGParticleEntity = ZEntity<ZGLPartical>;
}