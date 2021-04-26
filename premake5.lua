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

group "Dependencies"
	include "Hydron/vendor/GLFW"
group ""

include "Hydron/vendor/GLFW"

project "Hydron"
	location "Hydron"
	kind "SharedLib"
	language "C++"

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
		"%{IncludeDir.GLFW}"
	}

	links
	{
		"GLFW",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"HYDRON_PLATFORM_WINDOWS",
			"HYDRON_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		buildoptions "/MDd"
		defines "HYDRON_DEBUG"
		symbols "On"

	filter "configurations:Release"
		buildoptions "/MD"
		defines "HYDRON_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		buildoptions "/MD"
		defines "HYDRON_DIST"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

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
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"HYDRON_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		buildoptions "/MDd"
		defines "HYDRON_DEBUG"
		symbols "On"

	filter "configurations:Release"
		buildoptions "/MD"
		defines "HYDRON_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		buildoptions "/MD"
		defines "HYDRON_DIST"
		optimize "On"