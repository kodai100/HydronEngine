#pragma once

#include "glm/glm.hpp"
#include "Hydron/Renderer/VertexArray.h"

namespace Hydron {

	class Mesh
	{

	public:
		Mesh();

		void PushPosition(const glm::vec3& position);
		void PushNormal(const glm::vec3& normal);
		void PushUv(const glm::vec2& uv);

		void PushTriangle(uint32_t v1, uint32_t v2, uint32_t v3);
		
		Ref<VertexArray> ConstructVertexArray();

		bool Validate();

	private:
		std::vector<glm::vec3> m_Positions;
		std::vector<glm::vec3> m_Normals;
		std::vector<glm::vec2> m_Uvs;

		std::vector<uint32_t> m_Indices;

		bool m_AlreadyConstruct = false;
		Ref<VertexArray> m_VertexArray;
	};

}