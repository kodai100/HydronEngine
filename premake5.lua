workspace "Hydron"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution dir)
IncludeDir = {}
IncludeDir["GLFW"] = "Hydron/vendor/GLFW/include"
IncludeDir["Glad"] = "Hydron/vendor/Glad/include"
IncludeDir["ImGui"] = "Hydron/vendor/imgui"
IncludeDir["glm"] = "Hydron/vendor/glm"

group "Dependencies"
	include "Hydron/vendor/GLFW"
	include "Hydron/vendor/Glad"
	include "Hydron/vendor/imgui"
group ""

project "Hydron"
	location "Hydron"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "Hydron/src/pch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"HYDRON_PLATFORM_WINDOWS",
			"_CRT_SECURE_NO_WARNINGS",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "HYDRON_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "HYDRON_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "HYDRON_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Hydron/vendor/spdlog/include",
		"Hydron/src",
		"Hydron/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Hydron"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"HYDRON_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "HYDRON_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "HYDRON_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "HYDRON_DIST"
		runtime "Release"
		optimize "on"