#include <Hydron.h>

#include <imgui/imgui.h>


class ExampleLayer : public Hydron::Layer
{
private:
	float t = 0;

	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 1;
	
	Hydron::OrthographicCamera m_Camera;

	std::shared_ptr<Hydron::Shader> m_Shader;
	std::shared_ptr<Hydron::VertexArray> m_VertexArray;

	std::shared_ptr<Hydron::Shader> m_BlueShader;
	std::shared_ptr<Hydron::VertexArray> m_SquareVertexArray;

public:
	ExampleLayer() : Layer("Example Layer"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition({0,0,0})
	{
		m_VertexArray.reset(Hydron::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
			0.0f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
		};

		std::shared_ptr<Hydron::VertexBuffer> triangleVertexBuffer;
		triangleVertexBuffer.reset(Hydron::VertexBuffer::Create(vertices, sizeof(vertices)));
		Hydron::BufferLayout layout = {
			{Hydron::ShaderDataType::Float3, "a_Position" },
			{Hydron::ShaderDataType::Float4, "a_Color" }
		};
		triangleVertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(triangleVertexBuffer);



		unsigned int indices[3] = {
			0, 1, 2
		};
		std::shared_ptr<Hydron::IndexBuffer> triangleIndexBuffer;
		triangleIndexBuffer.reset(Hydron::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(triangleIndexBuffer);


		// ---------------------------------

		m_SquareVertexArray.reset(Hydron::VertexArray::Create());
		float sqVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};
		std::shared_ptr<Hydron::VertexBuffer> squareVertexBuffer;
		squareVertexBuffer.reset(Hydron::VertexBuffer::Create(sqVertices, sizeof(sqVertices)));
		squareVertexBuffer->SetLayout({
			{Hydron::ShaderDataType::Float3, "a_Position" }
			});
		m_SquareVertexArray->AddVertexBuffer(squareVertexBuffer);

		unsigned int sqIndices[6] = {
			0, 1, 2, 2, 3, 0
		};
		std::shared_ptr<Hydron::IndexBuffer> squareIndexBuffer;
		squareIndexBuffer.reset(Hydron::IndexBuffer::Create(sqIndices, sizeof(sqIndices) / sizeof(uint32_t)));
		m_SquareVertexArray->SetIndexBuffer(squareIndexBuffer);


		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location=0) in vec3 a_Position;
			layout(location=1) in vec4 a_Color;
			
			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location=0) out vec4 color;
			
			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = v_Color;
			}
		)";


		m_Shader.reset(new Hydron::Shader(vertexSrc, fragmentSrc));


		std::string blueVertexShaderSrc = R"(
			#version 330 core
			
			layout(location=0) in vec3 a_Position;
			
			uniform mat4 u_ViewProjection;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position =  u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";

		std::string blueFragmentShaderSrc = R"(
			#version 330 core
			
			layout(location=0) out vec4 color;
			
			in vec3 v_Position;

			void main()
			{
				color = vec4(0.0, 0.3, 1.0, 1.0);
			}
		)";

		m_BlueShader.reset(new Hydron::Shader(blueVertexShaderSrc, blueFragmentShaderSrc));
	}

	~ExampleLayer() {}

	void ExampleLayer::OnEvent(Hydron::Event& event) override
	{


	}

	void CameraMovement(Hydron::Timestep ts)
	{
		
		if (Hydron::Input::IsKeyPressed(Hydron::Key::Up))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		else if(Hydron::Input::IsKeyPressed(Hydron::Key::Down))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;

		if (Hydron::Input::IsKeyPressed(Hydron::Key::Left))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		else if (Hydron::Input::IsKeyPressed(Hydron::Key::Right))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;

	}

	void ExampleLayer::OnImGuiRender()
	{
		// Sample 
		static bool show = true;
		ImGui::ShowDemoWindow(&show);
	}

	void ExampleLayer::OnUpdate(Hydron::Timestep ts)
	{

		CameraMovement(ts);

		Hydron::RenderCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1));
		Hydron::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);

		Hydron::Renderer::BeginScene(m_Camera);
		{
			Hydron::Renderer::Submit(m_BlueShader, m_SquareVertexArray);
			Hydron::Renderer::Submit(m_Shader, m_VertexArray);
		}
		Hydron::Renderer::EndScene();

	}

};


class Sandbox : public Hydron::Application {
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
	}

	~Sandbox() {

	}
};


Hydron::Application* Hydron::CreateApplication() {
	return new Sandbox();
}