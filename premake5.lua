workspace "Unify"
	architecture "x64"

	configurations {
		"Debug",
		"Release",
		"Dist"
	}


outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


project "Unify"
	location "Unify"
	kind "SharedLib"
	language "C++"
	cppdialect "C++20"
	buildoptions{
		"/utf-8"
	}

	targetdir ("bin/" .. outputDir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputDir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"%{prj.name}/vendor/spdlog/include"
	}

	filter "system:windows"
		staticruntime "On"
		systemversion "latest"

		defines {
			"UN_PLATFORM_WINDOWS",
			"UN_BUILD_DLL"
		}

		postbuildcommands {
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputDir .. "/Editor")
		}

	filter "configurations:Debug"
		defines "UN_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "UN_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "UN_DIST"
		symbols "On"


project "Editor"
	location "Editor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	buildoptions{
		"/utf-8"
	}

	targetdir ("bin/" .. outputDir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputDir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"Unify/vendor/spdlog/include",
		"Unify/src"
	}

	links {
		"Unify"
	}

	filter "system:windows"
		staticruntime "On"
		systemversion "latest"

		defines {
			"UN_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "UN_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "UN_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "UN_DIST"
		symbols "On"
