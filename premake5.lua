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

group "Dependencies"
	include "Hydron/vendor/GLFW"
	include "Hydron/vendor/Glad"
	include "Hydron/vendor/imgui"
group ""

project "Hydron"
	location "Hydron"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "Hydron/src/pch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"HYDRON_PLATFORM_WINDOWS",
			"HYDRON_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

	filter "configurations:Debug"
		defines "HYDRON_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "HYDRON_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "HYDRON_DIST"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

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
		"Hydron/src"
	}

	links
	{
		"Hydron"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"HYDRON_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "HYDRON_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "HYDRON_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "HYDRON_DIST"
		runtime "Release"
		optimize "On"