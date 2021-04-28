#pragma once


namespace Hydron {

	enum class RendererAPI
	{
		None = 0,	// headless, test
		OpenGL = 1,
		DirectX = 2
	};

	class Renderer
	{
	private:
		static RendererAPI s_RendererAPI;
	public:
		inline static RendererAPI GetAPI() { return s_RendererAPI; }
	};


}