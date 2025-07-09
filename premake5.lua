
workspace "OpenGLTetris"
    configurations {"Debug","Release"}
    

project "OpenGLTetris"
    kind "ConsoleApp"

    language "C++"
    cppdialect "C++latest"
    targetdir "bin/%{cfg.buildcfg}"

    architecture ("x64")

    includedirs { "libs/sdl3/include", "src/Game", "libs/glad/glad/include" }

    libdirs { "libs/sdl3/lib/x64" }

    links { "SDL3.dll","SDL3.lib" }

   files { "src/Game/**.h", "src/Game/**.cpp", "src/Game/**.c" }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

      postbuildcommands { "{COPY} libs/sdl3/lib/x64/SDL3.dll bin/Debug" }

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"

      postbuildcommands { "{COPY} libs/sdl3/lib/x64/SDL3.dll bin/Release" }

    