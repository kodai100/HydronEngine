#pragma once

#include "VertexArray.h"

namespace Hydron {

	class Mesh
	{

	public:
		Mesh();

		void SetIndices(uint32_t* indices);

	private:
		Ref<VertexArray> m_VertexArray;
	};

}