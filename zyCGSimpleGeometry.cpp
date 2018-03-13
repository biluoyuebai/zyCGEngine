#include "zyCGSimpleGeometry.h"
namespace zyLib
{
	#define _0 {0.5f, 0.5f, 0.5f}
	#define _1 {-0.5f, 0.5f, 0.5f}
	#define _2 {-0.5f,-0.5f,0.5f}
	#define _3 {0.5f,-0.5f,0.5f}
	#define _4 {0.5f,0.5f,-0.5f}
	#define _5 {-0.5f,0.5f,-0.5f}
	#define _6 {-0.5f,-0.5f,-0.5f}
	#define _7 {0.5f,-0.5f,-0.5f}
		Vector<Vector3D> * zyLib::cube_pos = new Vector<Vector3D>{ _0,_1,_3,_3,_1,_2,_3,_2,_7,_7,_2,_6,_7,_6,_4,_4,_6,_5,_4,_5,_0,_0,_5,_1,_0,_3,_4,_4,_3,_7,_2,_1,_6,_6,_1,_5 };
	#undef _0
	#undef _1
	#undef _2
	#undef _3
	#undef _4
	#undef _5
	#undef _6
	#undef _7
	#define _9 {1.0f, 1.0f}
	#define _7 {0.0f, 1.0f}
	#define _1 {0.0f, 0.0f}
	#define _3 {1.0f, 0.0f}
		Vector<TexCoord> * zyLib::cube_tex = new Vector<TexCoord>{ _9, _7, _3, _3, _7, _1, _9, _7, _3, _3, _7, _1, _9, _7, _3, _3, _7, _1, _9, _7, _3, _3, _7, _1, _9, _7, _3, _3, _7, _1, _9, _7, _3, _3, _7, _1 };
	#undef _9
	#undef _7
	#undef _1
	#undef _3
}