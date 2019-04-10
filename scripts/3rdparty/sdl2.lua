sdl2 = dependency(nil, "SDL2")
    language "C"
    kind "StaticLib"

	configuration { "linux-*" }
        defines { 
            "_GLIBCXX_USE_CXX11_ABI=0",
            "SDL_TIMER_UNIX=1",
            "SDL_HAPTIC_LINUX=1",
            "SDL_FILESYSTEM_UNIX=1",
            "SDL_USE_LIBUDEV=1",
            "SDL_LOADSO_DLOPEN=1",
            "SDL_RENDER_DISABLED=0",
            "SDL_VIDEO_RENDER_OGL=1",
            "SDL_VIDEO_RENDER_OGL_ES2=1",
            "SDL_VIDEO_OPENGL=1",
            "SDL_VIDEO_OPENGL_ES=1",
            "SDL_VIDEO_OPENGL_ES2=1",
            "SDL_VIDEO_OPENGL_BGL=1",
            "SDL_VIDEO_OPENGL_CGL=1",
            "SDL_VIDEO_OPENGL_GLX=1",
            "SDL_VIDEO_OPENGL_WGL=1",
            "SDL_VIDEO_OPENGL_EGL=1",
            "SDL_VIDEO_OPENGL_OSMESA=1",
            "SDL_VIDEO_OPENGL_OSMESA_DYNAMIC=1",
            "SDL_VIDEO_OPENGL_GLX=1",
            "SDL_VIDEO_OPENGL=1",
            "SDL_VIDEO_DRIVER_X11=1",
            "SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS=1",
            -- "SDL_VIDEO_DRIVER_X11_DYNAMIC=1",
            "HAVE_LIBUDEV_H=1",
            "HAVE_STDIO_H=1",
        }
    
    SDL2_DIR = path.join(ENTCOSY_3RDPARTY_DIR, "sdl2")
    SDL2_INC_DIR = path.join(SDL2_DIR, "include")
	
	-- defaultConfigurations()
	files { 
        path.join( SDL2_DIR, "src/*.*"),
        path.join( SDL2_DIR, "src/atomic/*"),
        path.join( SDL2_DIR, "src/audio/*"),
        path.join( SDL2_DIR, "src/audio/directsound/*"),
        path.join( SDL2_DIR, "src/audio/disk/*"),
        path.join( SDL2_DIR, "src/audio/dummy/*"),
        path.join( SDL2_DIR, "src/audio/xaudio2/SDL_xaudio2.*"),
        path.join( SDL2_DIR, "src/audio/winmm/*"),
        path.join( SDL2_DIR, "src/cpuinfo/*"),
        path.join( SDL2_DIR, "src/dynapi/*"),
        path.join( SDL2_DIR, "src/events/*"),
        path.join( SDL2_DIR, "src/file/*"),
        path.join( SDL2_DIR, "src/haptic/*"),
        path.join( SDL2_DIR, "src/joystick/*"),
        path.join( SDL2_DIR, "src/joystick/dummy/*"),
        path.join( SDL2_DIR, "src/libm/*"),
        path.join( SDL2_DIR, "src/power/*"),
        path.join( SDL2_DIR, "src/render/*"),
        path.join( SDL2_DIR, "src/render/direct3d/*"),
        path.join( SDL2_DIR, "src/render/direct3d11/SDL_render_d3d11.c"),
        path.join( SDL2_DIR, "src/render/opengl/*"),
        path.join( SDL2_DIR, "src/render/opengles2/*"),
        path.join( SDL2_DIR, "src/render/software/*"),
        path.join( SDL2_DIR, "src/stdlib/*"),
        path.join( SDL2_DIR, "src/sensor/**"),
        path.join( SDL2_DIR, "src/thread/*"),
        path.join( SDL2_DIR, "src/thread/generic/SDL_syscond.c"),
        path.join( SDL2_DIR, "src/timer/*"),
        path.join( SDL2_DIR, "src/video/*"),
        path.join( SDL2_DIR, "src/video/yuv2rgb/*"),
        path.join( SDL2_DIR, "src/video/dummy/*"),
    }
        
	configuration { "vs*" }
		files { path.join( SDL2_DIR, "src/**/windows/*") }

	configuration { "linux-*" }
		files { 
            path.join( SDL2_DIR, "src/video/x11/*"),
            path.join( SDL2_DIR, "src/audio/dsp/*"),
            path.join( SDL2_DIR, "src/loadso/dlopen/*"),
            path.join( SDL2_DIR, "src/**/linux/*"),
            path.join( SDL2_DIR, "src/**/dlopen/*"),
            path.join( SDL2_DIR, "src/**/pthread/*"),
            path.join( SDL2_DIR, "src/**/unix/*"),
        }
	    excludes { path.join( SDL2_DIR, "src/hidapi/**") }
	configuration { }
		
	defines { "_CRT_SECURE_NO_WARNINGS", "HAVE_LIBC" }
    
    excludes { path.join( SDL2_DIR, "src/main/**") }
    
    includedirs { 
        SDL2_INC_DIR,
        include_files(sdl2, os.matchfiles(SDL2_INC_DIR .. "/*.h")),
    }