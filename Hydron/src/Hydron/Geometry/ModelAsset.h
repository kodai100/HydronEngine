#pragma once

#include "Vertex.h"

namespace Hydron
{

	struct ModelAsset
	{
		Vertex* vertices;
		size_t vertices_count;
		uint32_t* indices;
		size_t indices_count;
	};

}

