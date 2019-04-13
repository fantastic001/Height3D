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
	src/core/TextureAtlas.cpp
)

SET(gui_source_files 
	src/gui/Window.cpp
	src/loops/SDLLoop.cpp
	src/loops/SDLEvent.cpp

	src/models/SurfaceModel.cpp
	src/models/VoxeledModel.cpp

	src/textures/GradientTextureFactory.cpp

	src/noise/perlin/Perlin.cpp
	src/noise/perlin/PerlinImageAdapter.cpp
	src/noise/perlin/PerlinSurfaceModel.cpp
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

	src/terrain/TerrainPart.cpp
)
SET(header_files
	src/gui/Window.hpp
	src/noise/perlin/PerlinSurfaceModel.hpp
	src/noise/perlin/PerlinImageAdapter.hpp
	src/noise/perlin/PerlinSignal.hpp
	src/noise/perlin/Perlin.hpp
	src/interpolation/BilinearInterpolation.hpp
	src/interpolation/AbstractInterpolation.hpp
	src/textures/GradientTextureFactory.hpp
	src/voxel/VoxeledHeightfield.hpp
	src/morphology/CaveGenerator.hpp
	src/morphology/erode.hpp
	src/morphology/kernels/PerlinSphericalKernel.hpp
	src/morphology/kernels/Kernel.hpp
	src/morphology/kernels/SphericalKernel.hpp
	src/core/TextureAtlas.hpp
	src/core/Shader.hpp
	src/core/Loop.hpp
	src/core/Material.hpp
	src/core/TextureFactory.hpp
	src/core/AbstractModel.hpp
	src/core/Array3D.hpp
	src/core/Matrix.hpp
	src/core/Scene.hpp
	src/core/Buffer.hpp
	src/core/Vector.hpp
	src/core/common.hpp
	src/core/Program.hpp
	src/core/Light.hpp
	src/core/Texture.hpp
	src/core/DynamicSceneObject.hpp
	src/core/Color.hpp
	src/core/SceneObject.hpp
	src/core/Event.hpp
	src/models/SurfaceModel.hpp
	src/models/VoxeledModel.hpp
	src/terrain/TerrainPart.hpp
	src/structures/octree/OctreeFileStorage.hpp
	src/structures/octree/ImplicitOctreeGenerator.hpp
	src/structures/octree/Octree.hpp
	src/structures/octree/OctreeModel.hpp
	src/structures/octree/Array3DOctreeAdapter.hpp
	src/structures/heightfield/Array3DLayeredHeightfieldAdapter.hpp
	src/structures/heightfield/LayeredHeightfieldModel.hpp
	src/structures/heightfield/Heightfield.hpp
	src/structures/heightfield/LayeredHeightfield.hpp
	src/loops/SDLEvent.hpp
	src/loops/SDLLoop.hpp

)

add_compile_options(-std=c++11)

find_package(OpenGL)
find_package(GLEW)
find_package(SDL2)
find_package( OpenCV REQUIRED )
include_directories(${GLEW_INCLUDE_DIRS} src/)
link_libraries(${OpenCV_LIBS})
link_libraries(noise)
link_libraries(SDL2)
link_librarieS(${OPENGL_LIBRARIES})
link_libraries(${GLEW_LIBRARIES})

add_library(height3d_core SHARED
	${core_source_files}
)
add_library(height3d_gui SHARED
	${gui_source_files}
)

add_executable(unittest
	tests/test_vector.cpp
	tests/test_matrix.cpp
	tests/test_3darray.cpp
	tests/test_array_octree_adapter.cpp
	tests/test_octree_file_storage.cpp
	tests/test_lhf_file.cpp
)
target_link_libraries(unittest height3d_core)
target_LINK_LIBRARIES(unittest height3d_gui)
target_link_libraries(unittest boost_unit_test_framework)
add_test(NAME unittest COMMAND unittest)



add_executable(test_functional
	functional/basic.cpp
	functional/textures.cpp
	functional/scene.cpp
	functional/scene_loop.cpp
	functional/atlas.cpp
	functional/phong.cpp
	functional/dynamic_scene_object.cpp
	functional/surface.cpp
	functional/layered_heightfield.cpp
	functional/noise.cpp
	functional/perlin_surface.cpp
	functional/voxel.cpp
	functional/voxeled_terrain.cpp
	functional/octree_terrain.cpp
	functional/cave_generator.cpp
	functional/big_terrain.cpp
	functional/array_to_layered_heightfield.cpp
)
target_link_libraries(test_functional height3d_core)
target_LINK_LIBRARIES(test_functional height3d_gui)
include_directories(functional/)
target_link_libraries(test_functional boost_unit_test_framework)
add_custom_target(functional test_functional)


install(
	TARGETS height3d_core height3d_gui 
	RUNTIME DESTINATION bin 
	LIBRARY DESTINATION lib 
)

install(DIRECTORY src/ DESTINATION include/Height3D
	FILES_MATCHING PATTERN "*.hpp"
)

# first we can indicate the documentation build as an option and set it to ON by default
option(BUILD_DOC "Build documentation" ON)

# check if Doxygen is installed
find_package(Doxygen)
if (DOXYGEN_FOUND)
    # set input and output files
    set(DOXYGEN_IN Doxyfile.in)
    set(DOXYGEN_OUT Doxyfile.out)
    string(REPLACE ";" " " DOXYGEN_HEADER_INPUT "${header_files}")
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT})


    # note the option ALL which allows to build the docs together with the application
    add_custom_target( doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY .
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM )
else (DOXYGEN_FOUND)
  message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)

