workspace "Compiler-Tools"
	configurations {"DebugShared", "ReleaseShared", "DebugStatic", "ReleaseStatic"}
	platforms {"x86", "x86_64"}
	location "build"

project "Compiler-Tools"
	language "C++"
	targetdir "bin/%{cfg.buildcfg}"
	location "Compiler-Tools"

	files {"Compiler-Tools/inc/**.h", "Compiler-Tools/inc/**.hpp", 
		   "Compiler-Tools/src/**.cpp"}

	includedirs {"Compiler-Tools/inc/"}

	configuration {"linux", "gmake"}
		buildoptions{"-std=c++11"}

	filter "configurations:DebugShared"
		kind "SharedLib"
		defines {"DEBUG", "COMPILE_LIB"}
		flags {"Symbols"}

	filter "configurations:ReleaseShared"
		kind "SharedLib"
		defines {"NDEBUG", "COMPILE_LIB"}
		optimize "On"

	filter "configurations:DebugStatic"
		kind "StaticLib"
		defines {"DEBUG", "COMPILE_LIB"}
		flags {"Symbols"}

	filter "configurations:ReleaseStatic"
		kind "StaticLib"
		defines {"NDEBUG", "COMPILE_LIB"}
		optimize "On"

	filter "platforms:x86"
		architecture "x32"

	filter "platforms:x86_64"
		architecture "x64"

project "Compiler-Test"
	language "C++"
	kind "ConsoleApp"
	targetdir "bin/%{cfg.buildcfg}"
	location "Compiler-Tools"

	files {"Compiler-Test/inc/**.h", "Compiler-Test/src/**.cpp"}

	includedirs {"Compiler-Tools/inc/", "Compiler-Test/inc/"}

	links {"Compiler-Tools"}

	configuration {"linux", "gmake"}
		buildoptions{"-std=c++11"}

	filter "configurations:DebugShared"
		defines {"DEBUG"}
		flags {"Symbols"}

	filter "configurations:ReleaseShared"
		defines {"NDEBUG"}
		optimize "On"

	filter "configurations:DebugStatic"
		defines {"DEBUG"}
		flags {"Symbols"}

	filter "configurations:ReleaseStatic"
		kind "StaticLib"
		defines {"NDEBUG"}
		optimize "On"

	filter "platforms:x86"
		architecture "x32"
		
	filter "platforms:x86_64"
		architecture "x64"
