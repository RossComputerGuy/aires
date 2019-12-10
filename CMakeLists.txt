cmake_minimum_required(VERSION 3.15)
set(AIRES_VERSION "0.1.0")
project(aires VERSION "${AIRES_VERSION}" LANGUAGES CXX)

# Options
option(AIRES_API_GL3 "Enable OpenGL 3.0 support" ON)
option(AIRES_BACKEND_GLFW "Enable the GLFW backend" ON)
option(ENABLE_TESTING "Enable tests" ON)

## Dependencies
find_package(PkgConfig)
find_package(Threads)

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
	"${PROJECT_SOURCE_DIR}/src/graphics/api.cpp" "${PROJECT_SOURCE_DIR}/src/graphics/backend.cpp" "${PROJECT_SOURCE_DIR}/src/graphics/object.cpp" "${PROJECT_SOURCE_DIR}/src/graphics/texture.cpp" "${PROJECT_SOURCE_DIR}/src/graphics/shader.cpp"
	"${PROJECT_SOURCE_DIR}/src/graphics/window.cpp" "${PROJECT_SOURCE_DIR}/src/graphics/vertex.cpp"
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
