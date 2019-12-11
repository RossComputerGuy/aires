cmake_minimum_required(VERSION 3.15)
set(AIRES_VERSION "0.1.0")
project(aires VERSION "${AIRES_VERSION}" LANGUAGES CXX)

# Options
option(AIRES_API_GL3 "Enable OpenGL 3.0 support" ON)
option(AIRES_BACKEND_GLFW "Enable the GLFW backend" ON)
option(ENABLE_TESTING "Enable tests" ON)
option(COMPILE_SHADERS "Compile the GLSL shaders" ON)

# Functions
include(CMakeParseArguments)

if(COMPILE_SHADERS)
	find_program(GLSLC glslc)
	function(add_glsl)
		set(options_ova TARGET)
		set(options_mva SOURCES)
		cmake_parse_arguments(PARSED_ARGS "" ${options_ova} ${options_mva} ${ARGN})
		if(NOT PARSED_ARGS_TARGET)
			message(FATAL_ERROR "Target name is required")
		endif()
		foreach(src IN LISTS PARSED_ARGS_SOURCES)
			string(REPLACE "${PROJECT_SOURCE_DIR}/" "" out1 "${src}")
			set(out "${PROJECT_BINARY_DIR}/CMakeFiles/${PARSED_ARGS_TARGET}.dir/${out1}.spv")
			get_filename_component(dir ${out} DIRECTORY)
			execute_process(COMMAND mkdir -p ${dir})
			add_custom_command(OUTPUT "${out}"
				COMMAND ${GLSLC} -c ${COMPILE_OPTIONS} -o "${out}" "${src}"
				SOURCE "${src}"
				COMMENT "Building GLSL object ${out1}")
			list(APPEND sources "${out}")
		endforeach()
		add_custom_target(${PARSED_ARGS_TARGET} ALL DEPENDS ${sources})
	endfunction()
endif()

## Dependencies
find_package(PkgConfig)
find_package(Threads)
include(GNUInstallDirs)

if(ENABLE_TESTING)
	find_package(GTest)
	include(GoogleTest)
	enable_testing()
endif()

## GLFW
if(AIRES_BACKEND_GLFW)
	pkg_check_modules(GLFW REQUIRED glfw3)
	include_directories(${GLFW_INCLUDE_DIRS})
	link_libraries(${GLFW_LIBRARIES})
	add_compile_options(${GLFW_CFLAGS_OTHER})
	list(APPEND EXTRA_SOURCES "${PROJECT_SOURCE_DIR}/src/graphics/backends/glfw.cpp")
endif()

## OpenGL
if(AIRES_API_GL3)
	find_package(OpenGL)
	include_directories(${OPENGL_INCLUDE_DIR})
	link_libraries(${OPENGL_LIBRARIES})
	list(APPEND EXTRA_SOURCES "${PROJECT_SOURCE_DIR}/src/graphics/apis/gl3.cpp")
	set(COMPILE_OPTIONS --target-env=opengl_compat -fauto-map-locations)
	if(COMPILE_SHADERS)
		add_glsl(TARGET gl3-shaders
			SOURCES ${PROJECT_SOURCE_DIR}/data/shaders/graphics-object/gl3/texture2d.frag
			${PROJECT_SOURCE_DIR}/data/shaders/graphics-object/gl3/texture3d.frag
			${PROJECT_SOURCE_DIR}/data/shaders/graphics-object/gl3/untextured.frag
			${PROJECT_SOURCE_DIR}/data/shaders/graphics-object/gl3/shader.vert)
	endif()
endif()

## GLM
set(BUILD_SHARED_LIBS ON)
add_subdirectory("${PROJECT_SOURCE_DIR}/deps/glm")
include_directories("${glm_SOURCE_DIR}")
link_libraries("${glm_BINARY_DIR}/glm/libglm_shared.so")

## sigslot
include_directories("${PROJECT_SOURCE_DIR}/deps/sigslot/src")
list(APPEND EXTRA_SOURCES "${PROJECT_SOURCE_DIR}/deps/sigslot/src/signal.cpp")

# Aires
configure_file("${PROJECT_SOURCE_DIR}/data/config.h.in" "${PROJECT_BINARY_DIR}/include/aires/config.h")
include_directories("${PROJECT_SOURCE_DIR}/include" "${PROJECT_BINARY_DIR}/include")
add_library(aires SHARED
## Graphics
	"${PROJECT_SOURCE_DIR}/src/graphics/api.cpp" "${PROJECT_SOURCE_DIR}/src/graphics/backend.cpp" "${PROJECT_SOURCE_DIR}/src/graphics/camera.cpp" "${PROJECT_SOURCE_DIR}/src/graphics/object.cpp" "${PROJECT_SOURCE_DIR}/src/graphics/texture.cpp"
	"${PROJECT_SOURCE_DIR}/src/graphics/shader.cpp" "${PROJECT_SOURCE_DIR}/src/graphics/window.cpp" "${PROJECT_SOURCE_DIR}/src/graphics/vertex.cpp"
## Utils
	"${PROJECT_SOURCE_DIR}/src/utils/file.cpp"
## Main
	"${PROJECT_SOURCE_DIR}/src/graphics.cpp"
## Extra sources
	${EXTRA_SOURCES})
add_dependencies(aires glm_shared)

# Testing

if(ENABLE_TESTING)
	if(AIRES_API_GL3)
		add_executable(test-gl3-graphics-object "${PROJECT_SOURCE_DIR}/tests/src/graphics/gl3/graphics-object.cpp")
		add_dependencies(test-gl3-graphics-object aires)
		target_link_libraries(test-gl3-graphics-object "${PROJECT_BINARY_DIR}/libaires.so" ${GTEST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
		gtest_add_tests(TARGET test-gl3-graphics-object SOURCES "${PROJECT_SOURCE_DIR}/tests/src/graphics/gl3/graphics-object.cpp"
			WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/tests")
		
		add_executable(test-gl3-rendering "${PROJECT_SOURCE_DIR}/tests/src/graphics/gl3/rendering.cpp")
		add_dependencies(test-gl3-rendering aires)
		target_link_libraries(test-gl3-rendering "${PROJECT_BINARY_DIR}/libaires.so" ${GTEST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
		gtest_add_tests(TARGET test-gl3-rendering SOURCES "${PROJECT_SOURCE_DIR}/tests/src/graphics/gl3/rendering.cpp"
			WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/tests")

		add_executable(test-gl3-shaders "${PROJECT_SOURCE_DIR}/tests/src/graphics/gl3/shaders.cpp")
		add_dependencies(test-gl3-shaders aires)
		target_link_libraries(test-gl3-shaders "${PROJECT_BINARY_DIR}/libaires.so" ${GTEST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
		gtest_add_tests(TARGET test-gl3-shaders SOURCES "${PROJECT_SOURCE_DIR}/tests/src/graphics/gl3/shaders.cpp"
			WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/tests")

		add_executable(test-gl3-textures "${PROJECT_SOURCE_DIR}/tests/src/graphics/gl3/textures.cpp")
		add_dependencies(test-gl3-textures aires)
		target_link_libraries(test-gl3-textures "${PROJECT_BINARY_DIR}/libaires.so" ${GTEST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
		gtest_add_tests(TARGET test-gl3-textures SOURCES "${PROJECT_SOURCE_DIR}/tests/src/graphics/gl3/textures.cpp"
			WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/tests")
	endif()
endif()
