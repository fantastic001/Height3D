cmake_minimum_required (VERSION 2.6)

project (Height3D)

enable_testing()

SET(core_source_files 
	src/core/Buffer.cpp
	src/core/Program.cpp
	src/core/Vector.cpp
	src/core/Matrix.cpp
	src/core/Texture.cpp
	src/core/AbstractModel.cpp
	src/core/Shader.cpp
	src/core/Scene.cpp
	src/core/SceneObject.cpp
	src/core/Loop.cpp
	src/core/Event.cpp
	src/core/Light.cpp
)

SET(gui_source_files 
	src/gui/Window.cpp
	src/loops/SDLLoop.cpp
	src/loops/SDLEvent.cpp
)

find_package(OpenGL)
find_package(GLEW)
find_package(SDL2)
include_directories(${GLEW_INCLUDE_DIRS} src/)



add_executable(Tutorial
	try.cpp
	${core_source_files}
	${gui_source_files}
	
)
target_link_libraries(Tutorial ${GLEW_LIBRARIES})
target_LINK_LIBRARIES(Tutorial ${OPENGL_LIBRARIES})
target_link_libraries(Tutorial SDL2)



add_executable(unittest
	tests/test_vector.cpp
	tests/test_matrix.cpp
	${core_source_files}
	${gui_source_files}
)
target_link_libraries(unittest ${GLEW_LIBRARIES})
target_LINK_LIBRARIES(unittest ${OPENGL_LIBRARIES})
target_link_libraries(unittest SDL2)
target_link_libraries(unittest boost_unit_test_framework)
add_test(NAME unittest COMMAND unittest)



add_executable(test_functional
	functional/basic.cpp
	functional/textures.cpp
	functional/scene.cpp
	functional/scene_loop.cpp
	${core_source_files}
	${gui_source_files}
)
include_directories(functional/)
target_link_libraries(test_functional ${GLEW_LIBRARIES})
target_LINK_LIBRARIES(test_functional ${OPENGL_LIBRARIES})
target_link_libraries(test_functional SDL2)
target_link_libraries(test_functional boost_unit_test_framework)
add_custom_target(functional test_functional)
