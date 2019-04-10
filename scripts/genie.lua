solution "ENTCOSY_sln"

	configurations {
		"Debug",
		"Release",
	}
	platforms {
		"native",
	}

	language "C++"
	-- flags {
	-- 	"RTTI",
	-- }

	
PROJECT_DIR = path.getabsolute("..")
BUILD_DIR = path.join(PROJECT_DIR, "build")
ENTCOSY_3RDPARTY_DIR = path.join(PROJECT_DIR, "3rdparty")

dofile "options.lua"
dofile "toolchain.lua"
toolchain(BUILD_DIR, ENTCOSY_3RDPARTY_DIR)
dofile "utils/module.lua"

group "bin"
dofile "tests.lua"

