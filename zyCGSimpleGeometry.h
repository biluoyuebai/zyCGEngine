#pragma once
#include "zyCGMath.h"
#include "zyVector.hpp"
namespace zyLib
{
	extern Vector<Vector3D> * cube_pos;// = new Vector<Vector3D>{ _0,_1,_3,_3,_1,_2,_3,_2,_7,_7,_2,_6,_7,_6,_4,_4,_6,_5,_4,_5,_0,_0,_5,_1,_0,_3,_4,_4,_3,_7,_2,_1,_6,_6,_1,_5 };
	extern Vector<TexCoord> * cube_tex;// = new Vector<TexCoord>{ _9, _7, _3, _3, _7, _1, _9, _7, _3, _3, _7, _1, _9, _7, _3, _3, _7, _1, _9, _7, _3, _3, _7, _1, _9, _7, _3, _3, _7, _1, _9, _7, _3, _3, _7, _1 };
	extern Vector<Vector3D> * sphere_pos;
	template<typename type>
	using PixelColor = glm::tvec3<type>;
	template<typename type>
	class PixelLine
	{
	protected:
		PixelColor<type> * data;
	public:
		PixelLine(crv<PixelColor<type>*> data);
		lrv<PixelColor<type> *> get_data();
		lrv<PixelColor<type>> operator[](size_t index);
		crv<PixelColor<type> *> get_data() const;
		crv<PixelColor<type>> operator[](size_t index) const;
	};
	template<typename type>
	class PixelImage
	{
	protected:
		PixelLine<type> * data;
		size_t width, height;
	public:
		PixelImage(const char *const path);
	};
}