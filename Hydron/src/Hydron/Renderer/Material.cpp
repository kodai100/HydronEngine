#include "pch.h"
#include "Material.h"

#include <glm/glm.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

namespace Hydron {

	Material::Material(Ref<Shader> shader)
		: m_Shader(shader)
	{

	}

	void Material::Bind(const Ref<Camera>& camera, glm::mat4& transform)
	{
		Set("u_ModelMatrix", transform);
		Set("u_InvModelMatrix", glm::inverse(transform));

		Set("u_ViewMatrix", camera->GetViewMatrix());
		Set("u_ProjectionMatrix", camera->GetProjection());
		Set("u_ViewProjectionMatrix", camera->GetViewProjection());

		Set("u_LightDirection", glm::normalize(glm::vec3(-0.5f, -0.5f, -0.5f)));
		Set("u_LightColor", glm::normalize(glm::vec3(1.0f, 1.0f, 1.0f)));

		Set("u_CameraPos", camera->GetPosition());
		Set("u_AmbientColor", glm::vec4(0.01f, 0.01f, 0.01f, 1.0f));
	}

	void Material::Set(const std::string& name, const int value)
	{
		m_Shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(m_Shader)->UploadUniformInt(name, value);
	}

	void Material::Set(const std::string& name, const glm::mat3& matrix)
	{
		m_Shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(m_Shader)->UploadUniformMat3(name, matrix);
	}

	void Material::Set(const std::string& name, const glm::mat4& matrix)
	{
		m_Shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(m_Shader)->UploadUniformMat4(name, matrix);
	}

	void Material::Set(const std::string& name, const float value)
	{
		m_Shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(m_Shader)->UploadUniformFloat(name, value);
	}

	void Material::Set(const std::string& name, const glm::vec2& value)
	{
		m_Shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(m_Shader)->UploadUniformFloat2(name, value);
	}

	void Material::Set(const std::string& name, const glm::vec3& value)
	{
		m_Shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(m_Shader)->UploadUniformFloat3(name, value);
	}

	void Material::Set(const std::string& name, const glm::vec4& value)
	{
		m_Shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(m_Shader)->UploadUniformFloat4(name, value);
	}

}