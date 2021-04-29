#include "pch.h"
#include "Mesh.h"


namespace Hydron{
	
	Mesh::Mesh()
	{

		// Create Vertex Array
		m_VertexArray.reset(Hydron::VertexArray::Create());
		float sqVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};
		Hydron::Ref<Hydron::VertexBuffer> squareVertexBuffer;
		squareVertexBuffer.reset(Hydron::VertexBuffer::Create(sqVertices, sizeof(sqVertices)));
		squareVertexBuffer->SetLayout({
			{Hydron::ShaderDataType::Float3, "a_Position" },
			{Hydron::ShaderDataType::Float2, "a_TexCoord" }
			// , {Hydron::ShaderDataType::Float3, "a_Normal" }
		});
		m_VertexArray->AddVertexBuffer(squareVertexBuffer);


		// Create index array
		unsigned int sqIndices[6] = {
			0, 1, 2, 2, 3, 0
		};
		SetIndices(sqIndices);

	}

	void Mesh::SetIndices(uint32_t* indices)
	{
		Hydron::Ref<Hydron::IndexBuffer> squareIndexBuffer;
		squareIndexBuffer.reset(Hydron::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(squareIndexBuffer);
	}

}