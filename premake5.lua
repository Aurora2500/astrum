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

targetdir("bin/" .. outputdir)
objdir("obj/" .. outputdir)

files { "src/**.cpp", "src/**.hpp" }
links { "SDL2", "GL", "GLEW" }
includedirs { "src" }

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
        os.rmdir("./bin")
        os.rmdir("./bin-int")
        os.remove("./Makefile")
        os.remove("./Astrum.make")
        print("done.")
    end
}
