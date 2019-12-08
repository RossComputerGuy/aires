cmake_minimum_required(VERSION 3.15)
set(AIRES_VERSION "0.1.0")
project(aires VERSION "${AIRES_VERSION}" LANGUAGES CXX)

find_package(PkgConfig)
find_package(GTest)
include(GoogleTest)

enable_testing()

# Options
option(API_GL3 "Enable OpenGL 3.0 support" ON)
option(BACKEND_GLFW "Enable the GLFW backend" ON)

## Dependencies

## GLFW
if(BACKEND_GLFW)
	pkg_check_modules(GLFW REQUIRED glfw3)
	include_directories(${GLFW_INCLUDE_DIRS})
	link_libraries(${GLFW_LIBRARIES})
	add_compile_options(${GLFW_CFLAGS_OTHER})
	list(APPEND EXTRA_SOURCES "${PROJECT_SOURCE_DIR}/src/graphics/backends/glfw.cpp")
endif()

## OpenGL
if(API_GL3)
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
include_directories("${PROJECT_SOURCE_DIR}/include")
add_library(aires SHARED "${PROJECT_SOURCE_DIR}/src/graphics/api.cpp" "${PROJECT_SOURCE_DIR}/src/graphics/backend.cpp" "${PROJECT_SOURCE_DIR}/src/graphics/shader.cpp" "${PROJECT_SOURCE_DIR}/src/graphics/window.cpp"
	${EXTRA_SOURCES})
add_dependencies(aires glm_shared)

# Testing

if(API_GL3)
	add_executable(gl3-shaders "${PROJECT_SOURCE_DIR}/tests/graphics/gl3/shaders.cpp")
	target_link_libraries(gl3-shaders "${PROJECT_BINARY_DIR}/libaires.so" ${GTEST_LIBRARIES})
	gtest_add_tests(TARGET gl3-shaders SOURCES "${PROJECT_SOURCE_DIR}/tests/graphics/gl3/shaders.cpp")
endif()
