pstl = dependency(nil, "pstl")
    language "C"
    kind "StaticLib"
    defines {
        "USE_INTEL_PSTL",
    }

    PSTL_DIR = path.join(ECS_3RDPARTY_DIR, "pstl")
    PSTL_INC_DIR = path.join(PSTL_DIR, "include")

    includedirs { 
        PSTL_INC_DIR,
    }