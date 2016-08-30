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
	src/core/TextureFactory.cpp
)

SET(gui_source_files 
	src/gui/Window.cpp
	src/loops/SDLLoop.cpp
	src/loops/SDLEvent.cpp

	src/models/SurfaceModel.cpp
	src/models/FilledSurfaceModel.cpp
	src/models/VoxeledModel.cpp

	src/textures/GradientTextureFactory.cpp

	src/noise/perlin/Perlin.cpp
	src/noise/perlin/PerlinImageAdapter.cpp
	src/noise/perlin/PerlinSurfaceModel.cpp
	src/noise/perlin/PerlinFilledSurfaceModel.cpp
	src/noise/perlin/PerlinSignal.cpp

	src/interpolation/AbstractInterpolation.cpp
	src/interpolation/BilinearInterpolation.cpp

	src/structures//octree/Octree.cpp
	src/structures/octree/Array3DOctreeAdapter.cpp
	src/structures/octree/ImplicitOctreeGenerator.cpp
	src/structures/octree/OctreeModel.cpp
	src/structures/octree/OctreeFileStorage.cpp

	src/structures/heightfield/Heightfield.cpp
	src/structures/heightfield/LayeredHeightfield.cpp
	src/structures/heightfield/LayeredHeightfieldModel.cpp
	src/structures/heightfield/Array3DLayeredHeightfieldAdapter.cpp

	src/voxel/VoxeledHeightfield.cpp

	src/morphology/erode.cpp
	src/morphology/CaveGenerator.cpp
	src/morphology/kernels/SphericalKernel.cpp
	src/morphology/kernels/PerlinSphericalKernel.cpp
)

add_compile_options(-std=c++11)

find_package(OpenGL)
find_package(GLEW)
find_package(SDL2)
find_package( OpenCV REQUIRED )
include_directories(${GLEW_INCLUDE_DIRS} src/)



link_libraries(${OpenCV_LIBS})

add_executable(unittest
	tests/test_vector.cpp
	tests/test_matrix.cpp
	tests/test_3darray.cpp
	tests/test_array_octree_adapter.cpp
	tests/test_octree_file_storage.cpp
	tests/test_lhf_file.cpp
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
	functional/phong.cpp
	functional/dynamic_scene_object.cpp
	functional/surface.cpp
	functional/noise.cpp
	functional/perlin_surface.cpp
	functional/voxel.cpp
	functional/voxeled_terrain.cpp
	functional/octree_terrain.cpp
	functional/filled_surface.cpp
	functional/layered_heightfield.cpp
	functional/cave_generator.cpp
	functional/array_to_layered_heightfield.cpp
	${core_source_files}
	${gui_source_files}
)
include_directories(functional/)
target_link_libraries(test_functional ${GLEW_LIBRARIES})
target_LINK_LIBRARIES(test_functional ${OPENGL_LIBRARIES})
target_link_libraries(test_functional SDL2)
target_link_libraries(test_functional boost_unit_test_framework)
add_custom_target(functional test_functional)
