solution "ECS_sln"

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
ECS_3RDPARTY_DIR = path.join(PROJECT_DIR, "3rdparty")

dofile "options.lua"
dofile "toolchain.lua"
toolchain(BUILD_DIR, ECS_3RDPARTY_DIR)
dofile "utils/module.lua"

group "bin"
dofile "ecs.lua"

