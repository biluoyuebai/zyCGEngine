#include "zyCGCamera.h"
using namespace zyLib;
CGCamera::CGCamera(crv<Vector3D> pos /* = Vector3D */, crv<Vector3D> up /* = Vector3D */, crv<Vector3D> front /* = Vector3D */, crv<ZGLCameraListener> _listener, crv<glm::mat4> perspective)
	: params{ _listener }, up{ glm::normalize(up) }, front{ glm::normalize(front) }, pos{ pos }, right{ glm::normalize(glm::cross(front, up)) }, perspective{ perspective } {}
Vector3D CGCamera::get_pos() const
{
	return pos;
}
glm::mat4 zyLib::CGCamera::get_look_at() const
{
	return glm::lookAt(pos, pos + front, up);
}
void CGCamera::pitch(crv<float> angle)
{
	auto mat4_tmp = glm::rotate(glm::mat4{}, angle, right);
	auto vec4_tmp = mat4_tmp * glm::vec4{ up, 1.0f };
	up.x = vec4_tmp.x;
	up.y = vec4_tmp.y;
	up.z = vec4_tmp.z;
	vec4_tmp = mat4_tmp * glm::vec4{ front ,1.0f };
	front.x = vec4_tmp.x;
	front.y = vec4_tmp.y;
	front.z = vec4_tmp.z;
}
void CGCamera::yaw(crv<float> angle)
{
	auto mat4_tmp = glm::rotate(glm::mat4{}, angle, up);
	auto vec4_tmp = mat4_tmp * glm::vec4{ right, 1.0f };
	right.x = vec4_tmp.x;
	right.y = vec4_tmp.y;
	right.z = vec4_tmp.z;
	vec4_tmp = mat4_tmp * glm::vec4{ front, 1.0f };
	front.x = vec4_tmp.x;
	front.y = vec4_tmp.y;
	front.z = vec4_tmp.z;
}
void CGCamera::roll(crv<float> angle)
{
	auto mat4_tmp = glm::rotate(glm::mat4{}, angle, front);
	auto vec4_tmp = mat4_tmp * glm::vec4{ up, 1.0f };
	up.x = vec4_tmp.x;
	up.y = vec4_tmp.y;
	up.z = vec4_tmp.z;
	vec4_tmp = mat4_tmp * glm::vec4{ right, 1.0f };
	right.x = vec4_tmp.x;
	right.y = vec4_tmp.y;
	right.z = vec4_tmp.z;
}
void CGCamera::move_x(crv<float> distance)
{
	pos += distance * right;
}
void CGCamera::move_y(crv<float> distance)
{
	pos += distance * up;
}
void CGCamera::move_z(crv<float> distance)
{
	pos += distance * front;
}
crv<glm::mat4> CGCamera::get_perspective() const
{
	return perspective;
}
GLCameraParameters::GLCameraParameters(crv<float> _vx, crv<float> _vy, crv<float> _vz,
	crv<int> _kx, crv<int> _mkx,
	crv<int> _ky, crv<int> _mky,
	crv<int> _kz, crv<int> _mkz,
	crv<float> _vpitch, crv<float> _vyaw, crv<float> _vroll,
	crv<int> _kpitch, crv<int> _mkpitch,
	crv<int> _kyaw, crv<int> _mkyaw,
	crv<int> _kroll, crv<int> _mkroll)
	: vx{ _vx }, vy{ _vy }, vz{ _vz },
	kx{ _kx }, mkx{ _mkx },
	ky{ _ky }, mky{ _mky },
	kz{ _kz }, mkz{ _mkz },
	vpitch{ _vpitch }, vyaw{ _vyaw }, vroll{ _vroll },
	kpitch{ _kpitch }, mkpitch{ _mkpitch },
	kyaw{ _kyaw }, mkyaw{ _mkyaw },
	kroll{ _kroll }, mkroll{ _mkroll } {}