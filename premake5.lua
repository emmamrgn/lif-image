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
		includedirs { ".", "src", "projets" }
		
        files { "projets/" .. name .. ".cpp" }
end
