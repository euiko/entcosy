cereal =  dependency(nil, "rttr")
  	language "C++"
  	kind "StaticLib"
    -- defines {}

    RTTR_DIR = path.join(ENTCOSY_3RDPARTY_DIR, "rttr")
    RTTR_SRC_DIR = path.join(RTTR_DIR, "src")

    includedirs {
        RTTR_SRC_DIR,
    }

    files {
        path.join(RTTR_SRC_DIR, "rttr/**")
    }
