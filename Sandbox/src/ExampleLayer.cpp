#include "ExampleLayer.h"

#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

#include "Hydron/Util/FBXImporter.h"



ExampleLayer::ExampleLayer() : Layer("Example Layer"), m_Color({ 0,1,1,1 })
{

	// Frame Buffer Initialization
	Hydron::FrameBufferSpecification fbSpec;
	fbSpec.Attachments = { Hydron::FrameBufferTextureFormat::RGBA8, Hydron::FrameBufferTextureFormat::RED_INTEGER, Hydron::FrameBufferTextureFormat::Depth };
	fbSpec.Width = 1280;
	fbSpec.Height = 720;
	m_FrameBuffer = Hydron::FrameBuffer::Create(fbSpec);

	m_EditorCamera = std::make_shared<Hydron::EditorCamera>(30.0f, 1.778f, 0.1f, 1000.0f);

	auto textureShader = m_ShaderLibrary.Load("assets/shaders/TextureShaded.glsl");

	m_Texture = Hydron::Texture2D::Create("assets/textures/bunny.png");

	m_Material = std::make_shared<Hydron::Material>(textureShader);
	
	m_Mesh.reset(Hydron::FBXImporter::Load("assets/fbx/bunny.fbx"));
	m_Mesh->SetMaterial(m_Material);

}

void ExampleLayer::OnUpdate(Hydron::Timestep ts)
{

	// Resize
	if (Hydron::FrameBufferSpecification spec = m_FrameBuffer->GetSpecification();
		m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f && // zero sized framebuffer is invalid
		(spec.Width != m_ViewportSize.x || spec.Height != m_ViewportSize.y))
	{
		m_FrameBuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
		m_EditorCamera->SetViewportSize(m_ViewportSize.x, m_ViewportSize.y);
	}

	m_EditorCamera->OnUpdate(ts);

	m_FrameBuffer->Bind();

	Hydron::RenderCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1));
	Hydron::RenderCommand::Clear();

	m_FrameBuffer->ClearAttachment(1, -1);

	Hydron::Renderer::BeginScene(m_EditorCamera);

	{
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(10.0f));

		m_Material->SetTexture("u_Texture", *m_Texture.get(), 0);

		Hydron::Renderer::Submit(m_Mesh, scale);
	}

	Hydron::Renderer::EndScene();

	m_FrameBuffer->Unbind();
}

void ExampleLayer::OnEvent(Hydron::Event& e)
{
	m_EditorCamera->OnEvent(e);
}

void ExampleLayer::OnImGuiRender()
{

	// Note: Switch this to true to enable dockspace
	static bool dockspaceOpen = true;
	static bool opt_fullscreen_persistant = true;
	bool opt_fullscreen = opt_fullscreen_persistant;
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

	// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
	// because it would be confusing to have two docking targets within each others.
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
	if (opt_fullscreen)
	{
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->GetWorkPos());
		ImGui::SetNextWindowSize(viewport->GetWorkSize());
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	}

	// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
	// and handle the pass-thru hole, so we ask Begin() to not render a background.
	if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
		window_flags |= ImGuiWindowFlags_NoBackground;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
	ImGui::PopStyleVar();

	if (opt_fullscreen)
		ImGui::PopStyleVar(2);

	// DockSpace
	ImGuiIO& io = ImGui::GetIO();
	ImGuiStyle& style = ImGui::GetStyle();
	float minWinSizeX = style.WindowMinSize.x;
	style.WindowMinSize.x = 370.0f;
	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
	{
		ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
	}

	style.WindowMinSize.x = minWinSizeX;

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			// Disabling fullscreen would allow the window to be moved to the front of other windows, 
			// which we can't undo at the moment without finer window depth/z control.
			//ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);1
			if (ImGui::MenuItem("New", "Ctrl+N")) {}

			if (ImGui::MenuItem("Open...", "Ctrl+O")) {}

			if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S")) {}

			if (ImGui::MenuItem("Exit")) Hydron::Application::Get().Close();
			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
	}

	ImGui::End();


	// Sample
	static bool show = true;
	ImGui::ShowDemoWindow(&show);

	ImGui::Begin("Color");
	ImGui::ColorPicker4("Square Color", glm::value_ptr(m_Color));
	ImGui::End();


	ImGui::Begin("Viewport");
	auto viewportMinRegion = ImGui::GetWindowContentRegionMin();
	auto viewportMaxRegion = ImGui::GetWindowContentRegionMax();
	auto viewportOffset = ImGui::GetWindowPos();
	m_ViewportBounds[0] = { viewportMinRegion.x + viewportOffset.x, viewportMinRegion.y + viewportOffset.y };
	m_ViewportBounds[1] = { viewportMaxRegion.x + viewportOffset.x, viewportMaxRegion.y + viewportOffset.y };

	m_ViewportFocused = ImGui::IsWindowFocused();
	m_ViewportHovered = ImGui::IsWindowHovered();
	Hydron::Application::Get().GetImGuiLayer()->BlockEvents(!m_ViewportFocused && !m_ViewportHovered);

	ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
	m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };

	uint64_t textureID = m_FrameBuffer->GetColorAttachmentRendererID();
	ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2{ m_ViewportSize.x, m_ViewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

	ImGui::End();

}