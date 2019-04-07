function initX11()
    if os.is("Linux") then
        if (os.isdir("/usr/include") and os.isfile("/usr/include/X11/X.h")) then
            links{
                "dl",
                "X11",
                "Xrandr",
                "Xinerama",
                "Xi",
                "Xv",
                "Xt",
                "Xext",
                "Xmu",
                "Xtst",
                "Xxf86vm",
                "Xcursor",
                "pthread",
            }
        else
            print("No X11/X.h found, using dynamic loading of X11")
            defines {"DYNAMIC_LOAD_X11_FUNCTIONS"}	
            links {"dl","pthread"}
        end
    end
end

function dependency(namespace, name, cppmodule, usage_decl, deps)
    local m = {
        project = nil,
        cppmodule = cppmodule,
        namespace = namespace,
        name = name,
        dotname = string.gsub(name, "-", "."),
        idname = string.gsub(name, "-", "_"),
        usage_decl = usage_decl,
        deps = deps,
    }
    
    if namespace then
        m.dotname = namespace .. "." .. m.dotname
        m.idname = namespace .. "_" .. m.idname
    end
    
    m.project = project(m.idname)
    m.lib = {
        name = project().name,
        links = {},
        kind = "StaticLib",
    }
    
    if cppmodule then
        modules(m)
    end
    
    return m
end

function modules(m)
    if not _OPTIONS["cpp-modules"] then
        return
    end
    
    removeflags { "Cpp17" }
    flags {
        "CppLatest",
        --"CppModules",
    }
    
    defines { "_CRT_NO_VA_START_VALIDATION" }

    if _ACTION == "vs2015"
	or _ACTION == "vs2017" then
        files {
            path.join(m.path, m.dotname .. ".ixx"),
        }
    else
        files {
            path.join(m.path, m.dotname .. ".mxx"),
        }
        
        links {
            "std_core",
            "std_io",
            "std_threading",
            "std_regex",
        }
    end
end

function include_files(dependency, files) 
    local name;
    if(type(dependency) == "string") then
        name = dependency
    else
        name = dependency.idname
    end

    local inc_dir = path.join(PROJECT_DIR, "include")
    if not os.isdir(inc_dir) then
        os.mkdir(inc_dir)
    end

    local dir = path.join(inc_dir, name)
    if not os.isdir(dir) then
        os.mkdir(dir)
    end

    for _, file in ipairs(files) do
        os.copyfile(file, dir)    
    end
    return inc_dir
end