group "3rdparty"
-- dofile "3rdparty/pstl.lua"

project "entcosy"
  	language "C++"
    kind     "ConsoleApp"
    defines {
        -- "ENTCOSY_NO_RTTI",
        "ENTRY_CONFIG_USE_SDL=1",
        "SDL_VIDEO_DRIVER_X11=1",
        -- "USE_INTEL_PSTL",
        -- "DISABLE_RTTI=-fno-rtti -fno-exceptions"
    }

    ENTCOSY_SRC_DIR = path.join(PROJECT_DIR, "src") 
    ENTCOSY_INC_DIR = path.join(PROJECT_DIR, "include") 

    includedirs {
        "/usr/include",
        -- ENTCOSY_INC_DIR,
        ENTCOSY_SRC_DIR,
        -- PSTL_INC_DIR,
    }
    
    links {
        -- "xbgi",
        -- "pstl",
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
    
