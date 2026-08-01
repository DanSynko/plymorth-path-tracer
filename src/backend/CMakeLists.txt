option(CPU_PROJECT_IMPLEMENTATION "Build CPU-version of project" ON)

if(CPU_PROJECT_IMPLEMENTATION)
	add_executable(plymorth_main cpu/cpp/main.cpp)
endif()