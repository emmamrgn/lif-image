dofile "gkit.lua"

 -- description des projets		 
projects = {
	"projet",
}

for i, name in ipairs(projects) do
    project(name)
        language "C++"
        kind "ConsoleApp"
        targetdir "bin"
		links { "libgkit3" }
		includedirs { ".", "src", "projet" }
		
        files { "projet/" .. name .. ".cpp" }
end
