workspace "Kareeem"
    architecture "x64"
    staticruntime "on"

    configurations 
    {
        "Debug", 
        "Release"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.architecture}"

startproject "Client"

IncludeDir = {}
IncludeDir["GLFW"] = "vendor/GLFW/include"

project "Client"
    location "Client"
    language  "C++"
    cppdialect  "C++20"
    systemversion "latest"
    staticruntime "on"

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
        "%{IncludeDir.GLFW}"
    }

    filter "configurations:Debug"
        kind  "ConsoleApp"
        defines { "_DEBUG" }
        symbols "On"
        runtime "Debug"

    filter "configurations:Release"
        kind  "WindowedApp"
        defines { "NDEBUG" }
        optimize "On"
        runtime "Release"

project "Engine"
    location "Engine"
    language  "C++"
    kind  "StaticLib"
    cppdialect  "C++20"
    systemversion "latest"
    staticruntime "on"

    pchheader "Core/KRMpch.h"
	pchsource "%{prj.name}/src/Core/KRMpch.cpp"

    targetdir  ("bin/" .. outputdir.. "-%{prj.name}")
    objdir  ("bin-int/" .. outputdir .. "-%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    links 
    {
        "GLFW"
    }
    
    includedirs
    {
        "Engine/src",
        "%{IncludeDir.GLFW}"
    }

    filter "configurations:Debug"
        defines { "_DEBUG" }
        symbols "On"
        runtime "Debug"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
        runtime "Release"

group "Dependencies"
    include "vendor/GLFW"