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
IncludeDir["GLFW"] = "%{wks.location}/vendor/GLFW/include"
IncludeDir["GLEW"] = "%{wks.location}/vendor/GLEW/include"
IncludeDir["spdlog"] = "%{wks.location}/vendor/spdlog/include"
IncludeDir["glm"] = "%{wks.location}/vendor/glm"
IncludeDir["stb_image"] = "%{wks.location}/vendor/stb_image"
IncludeDir["imgui"] = "%{wks.location}/vendor/imgui"

project "Client"
    location "Client"
    debugdir "%{wks.location}/Assets"
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
    
    includedirs
    {
        "Engine/src",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.GLEW}",
        "%{IncludeDir.spdlog}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.stb_image}",
        "%{IncludeDir.imgui}"
    }

    links 
    {
        "Imgui",
        "Engine"
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
        "imgui",
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
        "%{IncludeDir.stb_image}",
        "%{IncludeDir.imgui}"
    }

    filter "configurations:Debug"
        defines { "_DEBUG", "KRM_ENABLE_LOG", "GLEW_STATIC" }
        runtime "Debug"

    filter "configurations:Release"
        defines { "NDEBUG", "GLEW_STATIC" }
        runtime "Release"

group "Dependencies"
    include "vendor/imgui"