group "3rdparty"
dofile "3rdparty/sdl2.lua"
dofile "3rdparty/pstl.lua"

project "ecs"
  	language "C++"
    kind     "ConsoleApp"
    defines {
        -- "ECS_NO_RTTI",
        "ENTRY_CONFIG_USE_SDL=1",
        "SDL_VIDEO_DRIVER_X11=1",
        "USE_INTEL_PSTL",
        "DISABLE_RTTI=-fno-rtti -fno-exceptions"
    }

    ECS_SRC_DIR = path.join(PROJECT_DIR, "src") 
    ECS_INC_DIR = path.join(PROJECT_DIR, "include") 

    includedirs {
        "/usr/include",
        ECS_INC_DIR,
        ECS_SRC_DIR,
        PSTL_INC_DIR,
    }
    
    files {
        path.join(ECS_SRC_DIR, "**"),
        -- path.join(PROJECT_DIR, "include/**.h"),
    }
    links {
        -- "xbgi",
        "SDL2",
        "pstl",
    }
    
    buildoptions {
        "-std=c++17",
        "-fopenmp-simd",
        -- "-fno-rtti",
        -- "-fno-exceptions",
    }

    configuration "linux or bsd"
        linkoptions { "-fPIC" }
        initX11()
        links {
            "GL",
            "GLU",
            "glut",
            "tbb",
            "EGL",
            "GLESv2",
        }
    
