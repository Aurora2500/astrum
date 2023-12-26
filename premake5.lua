-- premake5.lua

workspace "Astrum"
    architecture "x86_64"
    configurations { "Debug", "Release" }

-- Define common output directory for all configurations
outputdir = "%{cfg.buildcfg}"

-- Project configuration
project "Astrum"
    kind "WindowedApp"
    language "C++"
    cppdialect "C++20"

    targetdir ("bin/" .. outputdir)
    objdir ("bin-int/" .. outputdir)

    files { "src/**.cpp", "src/**.hpp" }
		links { "SDL2" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
