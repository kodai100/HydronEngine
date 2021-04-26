#pragma once

#ifdef HYDRON_PLATFORM_WINDOWS

extern Hydron::Application* Hydron::CreateApplication();

int main(int argc, char** argv)
{

	Hydron::Log::Init();

	auto app = Hydron::CreateApplication();

	app->Run();

	delete app;

}

#endif