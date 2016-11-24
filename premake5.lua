workspace "Compiler-Tools"
	configurations {"DebugShared", "ReleaseShared", "DebugStatic", "ReleaseStatic"}
	platforms {"x86", "x86_64"}
	location "build"
	startproject "Compiler-Test"


project "Compiler-Test"
	language "C++"
	kind "ConsoleApp"
	targetdir "bin/%{cfg.platform}/%{cfg.buildcfg}"
	location "Compiler-Test"

	files {"Compiler-Test/inc/**.h", "Compiler-Test/src/**.cpp"}

	includedirs {"Compiler-Tools/inc/", "Compiler-Test/inc/", "deps/cereal-1.2.1/include/"}

	links {"Compiler-Tools"}

	configuration {"gmake", "linux"}
		buildoptions{"-std=c++11"}

	filter "configurations:DebugShared"
		defines {"DEBUG"}
		flags {"Symbols"}

	filter "configurations:ReleaseShared"
		defines {"NDEBUG"}
		optimize "On"

	filter "configurations:DebugStatic"
		defines {"DEBUG", "STATIC_LIB"}
		flags {"Symbols"}

	filter "configurations:ReleaseStatic"
		defines {"NDEBUG", "STATIC_LIB"}
		optimize "On"

	filter "platforms:x86"
		architecture "x32"
		
	filter "platforms:x86_64"
		architecture "x64"

project "Chalcedony"
	language "C++"
	kind "ConsoleApp"
	targetdir "bin/%{cfg.platform}/%{cfg.buildcfg}"
	location "Chalcedony"

	files {"Chalcedony/inc/**.h", "Chalcedony/src/**.cpp"}

	includedirs {"Compiler-Tools/inc/", "Chalcedony/inc/", "deps/cereal-1.2.1/include/"}

	links {"Compiler-Tools"}

	configuration {"gmake", "linux"}
		buildoptions{"-std=c++11"}

	filter "configurations:DebugShared"
		defines {"DEBUG"}
		flags {"Symbols"}

	filter "configurations:ReleaseShared"
		defines {"NDEBUG"}
		optimize "On"

	filter "configurations:DebugStatic"
		defines {"DEBUG", "STATIC_LIB"}
		flags {"Symbols"}

	filter "configurations:ReleaseStatic"
		defines {"NDEBUG", "STATIC_LIB"}
		optimize "On"

	filter "platforms:x86"
		architecture "x32"
		
	filter "platforms:x86_64"
		architecture "x64"

project "Compiler-Tools"
	language "C++"
	targetdir "bin/%{cfg.platform}/%{cfg.buildcfg}"
	location "Compiler-Tools"

	files {"Compiler-Tools/inc/**.h", "Compiler-Tools/inc/**.hpp", 
		   "Compiler-Tools/src/**.cpp"}

	includedirs {"Compiler-Tools/inc/", "deps/cereal-1.2.1/include/"}

	configuration {"gmake", "linux"}
		buildoptions{"-std=c++11"}

	filter "configurations:DebugShared"
		kind "SharedLib"
		defines {"DEBUG", "COMPILE_DYNAMIC_LIB"}
		flags {"Symbols"}

	filter "configurations:ReleaseShared"
		kind "SharedLib"
		defines {"NDEBUG", "COMPILE_DYNAMIC_LIB"}
		optimize "On"

	filter "configurations:DebugStatic"
		kind "StaticLib"
		defines {"DEBUG", "STATIC_LIB"}
		flags {"Symbols"}

	filter "configurations:ReleaseStatic"
		kind "StaticLib"
		defines {"NDEBUG", "STATIC_LIB"}
		optimize "On"

	filter "platforms:x86"
		architecture "x32"

	filter "platforms:x86_64"
		architecture "x64"

	configuration "*Static"
		kind "StaticLib"

	configuration "*Shared"
		kind "SharedLib"


