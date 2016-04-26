cmake_minimum_required (VERSION 2.6)

project (Height3D)

enable_testing()

add_executable(Tutorial
	try.cpp core/Buffer.cpp
	core/Program.cpp
	core/Vector.cpp
	core/Matrix.cpp
	core/Texture.cpp
	core/AbstractModel.cpp
	core/Shader.cpp
	gui/Window.cpp
)
find_package(OpenGL)
find_package(GLEW)
find_package(SDL2)
include_directories(${GLEW_INCLUDE_DIRS})
target_link_libraries(Tutorial ${GLEW_LIBRARIES})
target_LINK_LIBRARIES(Tutorial ${OPENGL_LIBRARIES})
target_link_libraries(Tutorial SDL2)

add_executable(unittest
	core/Buffer.cpp
	core/Program.cpp
	core/Vector.cpp
	core/Matrix.cpp
	core/Texture.cpp
	core/AbstractModel.cpp
	core/Shader.cpp
	
	gui/Window.cpp

	tests/test_vector.cpp
	tests/test_matrix.cpp
)
include_directories(${GLEW_INCLUDE_DIRS})
include_directories(.)
target_link_libraries(unittest ${GLEW_LIBRARIES})
target_LINK_LIBRARIES(unittest ${OPENGL_LIBRARIES})
target_link_libraries(unittest SDL2)
target_link_libraries(unittest boost_unit_test_framework)
add_test(NAME unittest COMMAND unittest)

add_executable(test_functional
	core/Buffer.cpp
	core/Program.cpp
	core/Vector.cpp
	core/Matrix.cpp
	core/Texture.cpp
	core/AbstractModel.cpp
	core/Shader.cpp
	
	gui/Window.cpp

	functional/basic.cpp
	functional/textures.cpp
)
include_directories(${GLEW_INCLUDE_DIRS})
target_link_libraries(test_functional ${GLEW_LIBRARIES})
target_LINK_LIBRARIES(test_functional ${OPENGL_LIBRARIES})
target_link_libraries(test_functional SDL2)
target_link_libraries(test_functional boost_unit_test_framework)
add_custom_target(functional test_functional)
