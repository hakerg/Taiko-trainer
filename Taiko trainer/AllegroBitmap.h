#pragma once
#include <allegro5\allegro.h>
#include "Vector2D.h"

namespace uc
{

	class AllegroBitmap
	{
	public:

		ALLEGRO_BITMAP * const k_bitmap;

		AllegroBitmap(const Vector2D<unsigned>& size_);
		virtual ~AllegroBitmap();

		Vector2D<unsigned> size() const;
	};

}