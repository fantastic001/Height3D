
#ifndef HEIGHT3D_MORPHOLOGY_ERODE_HPP
#define HEIGHT3D_MORPHOLOGY_ERODE_HPP

#include <core/Array3D.hpp>

void make_hole(Array3D<bool>& arr);

Array3D<bool> erode(Array3D<bool> &arr);

#endif // HEIGHT3D_MORPHOLOGY_ERODE_HPP
