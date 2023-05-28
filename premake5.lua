workspace "Kareeem"
    architecture "x64"
    staticruntime "off"

    configurations 
    {
        "Debug", 
        "Release"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.architecture}"

startproject "Client"

IncludeDir = {}
IncludeDir["GLFW"] = "vendor/GLFW/include"
IncludeDir["GLEW"] = "vendor/GLEW/include"
IncludeDir["spdlog"] = "vendor/spdlog/include"
IncludeDir["glm"] = "vendor/glm"
IncludeDir["stb_image"] = "vendor/stb_image"

project "Client"
    location "Client"
    language  "C++"
    cppdialect  "C++20"
    systemversion "latest"
    staticruntime "off"

    targetdir  ("bin/" .. outputdir.. "-%{prj.name}")
    objdir  ("bin-int/" .. outputdir .. "-%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }
    
    links
    {
        "Engine"
    }

    includedirs
    {
        "Engine/src",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.GLEW}",
        "%{IncludeDir.spdlog}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.stb_image}"
    }

    filter "configurations:Debug"
        kind  "ConsoleApp"
        defines { "_DEBUG", "KRM_ENABLE_LOG" }
        runtime "Debug"

    filter "configurations:Release"
        -- kind  "ConsoleApp"
        kind  "WindowedApp"
        defines { "NDEBUG" }
        runtime "Release"

project "Engine"
    location "Engine"
    language  "C++"
    kind  "StaticLib"
    cppdialect  "C++20"
    systemversion "latest"
    staticruntime "off"

    pchheader "Core/KRMpch.h"
	pchsource "%{prj.name}/src/Core/KRMpch.cpp"

    targetdir  ("bin/" .. outputdir.. "-%{prj.name}")
    objdir  ("bin-int/" .. outputdir .. "-%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    libdirs
    {
        "vendor/GLFW/lib",
        "vendor/GLEW/lib"
    }

    links 
    {
        "opengl32.lib",
        "glfw3.lib",
        "glew32s.lib"
    }
    
    includedirs
    {
        "Engine/src",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.GLEW}",
        "%{IncludeDir.spdlog}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.stb_image}"
    }

    filter "configurations:Debug"
        defines { "_DEBUG", "KRM_ENABLE_LOG" }
        runtime "Debug"

    filter "configurations:Release"
        defines { "NDEBUG" }
        runtime "Release"
