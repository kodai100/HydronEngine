#pragma once

// For use by Hydron applications
#include "Hydron/Core/Base.h"

#include "Hydron/Core/Application.h"
#include "Hydron/Core/Layer.h"
#include "Hydron/Core/Log.h"
#include "Hydron/Core/Timestep.h"

#include "Hydron/Core/Input.h"
#include "Hydron/Core/KeyCodes.h"
#include "Hydron/Core/MouseCodes.h"

#include "Hydron/Events/Event.h";
#include "Hydron/Events/ApplicationEvent.h";
#include "Hydron/Events/KeyEvent.h";
#include "Hydron/Events/MouseEvent.h";

#include "Hydron/ImGui/ImGuiLayer.h";

// Renderer ----------------------------------------------
#include "Hydron/Renderer/Renderer.h"
#include "Hydron/Renderer/RenderCommand.h"
#include "Hydron/Renderer/Shader.h"
#include "Hydron/Renderer/Texture.h"
#include "Hydron/Renderer/Buffer.h"
#include "Hydron/Renderer/VertexArray.h"
#include "Hydron/Renderer/FrameBuffer.h"

#include "Hydron/Renderer/EditorCamera.h"

// Utility -----------------------------------------------
#include "Hydron/Geometry/Mesh.h"
