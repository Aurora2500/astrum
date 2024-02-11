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
toolset "clang"
warnings "Extra"

targetdir(".")
objdir("obj/" .. outputdir)

files { "src/**.cpp", "src/**.hpp" }
links { "SDL2", "GL", "GLEW", "freetype", "lodepng" }
includedirs { "src", "/usr/include/freetype2" }

filter "configurations:Debug"
defines { "DEBUG" }
symbols "On"

filter "configurations:Release"
defines { "NDEBUG" }
optimize "On"

newaction {
    trigger     = "clean",
    description = "clean the project",
    execute     = function()
        print("clean the build...")
        os.remove("./Astrum")
        os.rmdir("./obj")
        os.remove("./Makefile")
        os.remove("./Astrum.make")
        print("done.")
    end
}
