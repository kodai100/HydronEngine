#include "pch.h"
#include "Mesh.h"


namespace Hydron{
	
	Mesh::Mesh()
	{

	}

	void Mesh::PushPosition(const glm::vec3& position)
	{

		m_Positions.push_back(position);

	}

	void Mesh::PushNormal(const glm::vec3& normal)
	{
		m_Normals.push_back(normal);
	}

	void Mesh::PushUv(const glm::vec2& uv)
	{
		m_Uvs.push_back(uv);
	}

	void Mesh::PushTriangle(uint32_t v1, uint32_t v2, uint32_t v3)
	{
		
		m_Indices.push_back(v1);
		m_Indices.push_back(v2);
		m_Indices.push_back(v3);

	}

	bool Mesh::Validate()
	{

		HYDRON_CORE_INFO("Pos : {0}", m_Positions.size());
		HYDRON_CORE_INFO("Normal : {0}", m_Normals.size());
		HYDRON_CORE_INFO("Uv : {0}", m_Uvs.size());

		HYDRON_CORE_INFO("Indices : {0}", m_Indices.size());
		HYDRON_CORE_INFO("Tris : {0}", m_Indices.size() / 3);

		return true;
		
	}

	Ref<VertexArray> Mesh::ConstructVertexArray()
	{
		if (m_AlreadyConstruct)
		{
			return m_VertexArray;
		}

		std::vector<float> vertexData;

		for (int i = 0; i < m_Positions.size(); i++)
		{
			vertexData.push_back(m_Positions[i].x);
			vertexData.push_back(m_Positions[i].y);
			vertexData.push_back(m_Positions[i].z);
			vertexData.push_back(m_Normals[i].x);
			vertexData.push_back(m_Normals[i].y);
			vertexData.push_back(m_Normals[i].z);
			vertexData.push_back(m_Uvs[i].x);
			vertexData.push_back(m_Uvs[i].y);
		}

		m_VertexArray.reset(Hydron::VertexArray::Create());
		Hydron::Ref<Hydron::VertexBuffer> meshVertexBuffer;
		meshVertexBuffer.reset(Hydron::VertexBuffer::Create(&vertexData[0], sizeof(float) * vertexData.size()));
		meshVertexBuffer->SetLayout({
			{Hydron::ShaderDataType::Float3, "a_Position" },
			{Hydron::ShaderDataType::Float3, "a_Normal" },
			{Hydron::ShaderDataType::Float2, "a_TexCoord" }
		});
		m_VertexArray->AddVertexBuffer(meshVertexBuffer);


		// Create index array
		Hydron::Ref<Hydron::IndexBuffer> squareIndexBuffer;
		squareIndexBuffer.reset(Hydron::IndexBuffer::Create(&m_Indices[0], m_Indices.size()));
		m_VertexArray->SetIndexBuffer(squareIndexBuffer);

		m_AlreadyConstruct = true;

		return m_VertexArray;

	}

}