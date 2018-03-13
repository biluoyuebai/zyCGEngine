#include "zyCGSimpleGeometry.h"
#include <stb/stb_image.hpp>
namespace zyLib
{
	template<typename type>
	PixelLine<type>::PixelLine(crv<PixelColor<type> *> data)
		: data{ data } {}
	template<typename type>
	lrv<PixelColor<type> *> PixelLine<type>::get_data()
	{
		return data;
	}
	template<typename type>
	lrv<PixelColor<type>> PixelLine<type>::operator[](size_t index)
	{
		return data[index];
	}
	template<typename type>
	crv<PixelColor<type> *> PixelLine<type>::get_data() const
	{
		return data;
	}
	template<typename type>
	crv<PixelColor<type>> PixelLine<type>::operator[](size_t index) const
	{
		return data[index];
	}
	template<typename type>
	PixelImage<type>::PixelImage(const char *const path)
	{
		int channels = 0;
		stbi_set_flip_vertically_on_load(true);
		auto data = stbi_load(path, &width, &height, &channels, 0);
		if (channels == 1 || channels == 4)
			throw std::runtime_error("rgb only!");
		this->data = new PixelLine<type>[width] {new PixelColor<type>[height]};

	}
}