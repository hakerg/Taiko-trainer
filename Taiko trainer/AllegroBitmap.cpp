#include "AllegroBitmap.h"

namespace uc
{

	AllegroBitmap::AllegroBitmap(const Vector2D<unsigned>& size_) : k_bitmap(al_create_bitmap(size_.x, size_.y))
	{
	}

	AllegroBitmap::~AllegroBitmap()
	{
		al_destroy_bitmap(k_bitmap);
	}

	Vector2D<unsigned> AllegroBitmap::size() const
	{
		return { (unsigned)al_get_bitmap_width(k_bitmap), (unsigned)al_get_bitmap_height(k_bitmap) };
	}

}