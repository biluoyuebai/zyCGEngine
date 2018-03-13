#pragma once
#include "zyCGPrerequisites.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
namespace zyLib
{
	using Vector3D = glm::vec3;
	using Vector4D = glm::vec4;
	using Color3D = Vector3D;
	using Color4D = Vector4D;
	using Normal = Vector3D;
	using Quaternion = glm::quat;
	using TexCoord = glm::vec2;
	inline std::ostream & operator<<(std::ostream & os, crv<Vector3D> vector)
	{
		return os << vector.x << " " << vector.y << " " << vector.z << " ";
	}
	class ZVector3D :
		my_extends ZObject
	{
		using T = Vector3D;
		TCCDefault(ZVector3D)
		TCCCopyDefault(ZVector3D)
		TCCBackDoor(ZVector3D)
		TCCIndex(ZVector3D, size_t)
	};
	class ZVector4D :
		my_extends ZObject
	{
		using T = Vector4D;
		TCCDefault(ZVector4D)
		TCCCopyDefault(ZVector4D)
		TCCBackDoor(ZVector4D)
		TCCIndex(ZVector4D, size_t)
	};
	using ZColor3D = ZVector3D;
	using ZColor4D = ZVector4D;
	using ZNormal = ZVector3D;
	class ZQuaternion :
		my_extends ZObject
	{
		using T = Quaternion;
		TCCDefault(ZQuaternion)
		TCCCopyDefault(ZQuaternion)
		TCCBackDoor(ZQuaternion)
		TCCIndex(ZQuaternion, size_t)
	};
}