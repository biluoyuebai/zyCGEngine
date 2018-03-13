#pragma once
#include "zyCGPrerequisites.h"
#include "zyCGMath.h"
#include "zyCGEntity.h"
#include "zyVector.hpp"
namespace zyLib
{
	template<typename type, class enable_if_param = std::enable_if_t<std::is_same_v<type, ZCGEntity> || std::is_same_v<type, ZCGParticleEntity>>>
	class Node
	{
	protected:
		ZVector3D pos;
		ZQuaternion ori;
		type entity;
	public:
		Node(crv<ZVector3D> p, crv<ZQuaternion> o, crv<type> e)
			: pos{ p }, ori{ o }, entity{ e } {}
		Node(crv<Node> arg)
			: Node{ arg.pos.copy(), arg.ori.copy(), arg.entity.copy() } {}
		Node(rrv<Node> arg)
			: pos{ std::move(arg.pos) }, ori{ std::move(arg.ori) }, entity{ std::move(arg.entity) } {}
		TPAll(pos)
		TPAll(ori)
		TPAll(entity)
		Node & operator=(crv<Node> arg)
		{
			pos = arg.pos.copy();
			ori = arg.ori.copy();
			entity = arg.entity.copy();
			return *this;
		}
		Node & operator=(rrv<Node> arg)
		{
			pos = std::move(arg.pos);
			ori = std::move(arg.ori);
			entity = std::move(arg.entity);
			return *this;
		}
	};
	using SceneNode = Node<ZCGEntity>;
	using CGSceneNode = SceneNode;
	template<typename type>
	class ZNode :
		my_extends ZObject
	{
		using T = Node<type>;
		TCCDefault(ZNode)
		TCCCopyDefault(ZNode)
		TCCBackDoor(ZNode)
	};
	using ZSceneNode = ZNode<ZCGEntity>;
	using ZCGSceneNode = ZSceneNode;
	using CGParticleNode = Node<ZCGParticleEntity>;
	using ZCGParticleNode = ZNode<ZCGParticleEntity>;
}