#pragma once

#include "Hydron/Core/Base.h"
#include "Camera.h"
#include "Shader.h"
#include "Texture.h"

namespace Hydron {

	class Material
	{
	public:
		Material(Ref<Shader> shader);

		void Bind(const Ref<Camera>& camera, glm::mat4& transform);

		void SetTexture(const std::string& name, const Texture& texture, const int index);
		void Set(const std::string& name, const int value);
		void Set(const std::string& name, const glm::mat3& matrix);
		void Set(const std::string& name, const glm::mat4& matrix);
		void Set(const std::string& name, const float value);
		void Set(const std::string& name, const glm::vec2& value);
		void Set(const std::string& name, const glm::vec3& value);
		void Set(const std::string& name, const glm::vec4& value);

	private:

		Ref<Shader> m_Shader;

	};

}