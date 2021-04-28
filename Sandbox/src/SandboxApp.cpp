#include <Hydron.h>

#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Platform/OpenGL/OpenGLShader.h"

#include "Hydron/Renderer/Shader.h"

class ExampleLayer : public Hydron::Layer
{
private:
	float t = 0;

	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 1;
	glm::vec4 m_Color;
	
	Hydron::OrthographicCamera m_Camera;

	Hydron::Ref<Hydron::Texture2D> m_Texture, m_AlphaTexture;
	Hydron::Ref<Hydron::VertexArray> m_SquareVertexArray;

	Hydron::ShaderLibrary m_ShaderLibrary;

public:
	ExampleLayer() : Layer("Example Layer"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition({ 0,0,0 }), m_Color({0,1,1,1})
	{

		m_SquareVertexArray.reset(Hydron::VertexArray::Create());
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
		});
		m_SquareVertexArray->AddVertexBuffer(squareVertexBuffer);


		unsigned int sqIndices[6] = {
			0, 1, 2, 2, 3, 0
		};
		Hydron::Ref<Hydron::IndexBuffer> squareIndexBuffer;
		squareIndexBuffer.reset(Hydron::IndexBuffer::Create(sqIndices, sizeof(sqIndices) / sizeof(uint32_t)));
		m_SquareVertexArray->SetIndexBuffer(squareIndexBuffer);


		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");
		auto flatShader = m_ShaderLibrary.Load("assets/shaders/FlatColor.glsl");

		m_Texture = Hydron::Texture2D::Create("assets/textures/rgb.png");
		m_AlphaTexture = Hydron::Texture2D::Create("assets/textures/rgba.png");

		std::dynamic_pointer_cast<Hydron::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<Hydron::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
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

		ImGui::Begin("Color");
		ImGui::ColorPicker4("Square Color", glm::value_ptr(m_Color));
		ImGui::End();
	}

	void ExampleLayer::OnUpdate(Hydron::Timestep ts)
	{

		CameraMovement(ts);

		/*Hydron::Material material = new Hydron::Material(m_BlueShader);
		Hydron::MaterialInstance mi = new Hydron::MaterialInstance(material);
		mi->Set("u_Color", redColor);
		mesh->SetMaterial(mi);*/

		Hydron::RenderCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1));
		Hydron::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);

		Hydron::Renderer::BeginScene(m_Camera);
		{

			glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

			auto textureShader = m_ShaderLibrary.Get("Texture");
			auto flatShader = m_ShaderLibrary.Get("FlatColor");

			std::dynamic_pointer_cast<Hydron::OpenGLShader>(flatShader)->Bind();
			std::dynamic_pointer_cast<Hydron::OpenGLShader>(flatShader)->UploadUniformFloat4("u_Color", m_Color);

			for (int y = 0; y < 20; y++)
			{
				for (int x = 0; x < 20; x++)
				{
					glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
					glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
					Hydron::Renderer::Submit(flatShader, m_SquareVertexArray, transform);
				}
			}
			
			m_Texture->Bind();
			Hydron::Renderer::Submit(textureShader, m_SquareVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

			m_AlphaTexture->Bind();
			Hydron::Renderer::Submit(textureShader, m_SquareVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
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