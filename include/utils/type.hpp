//
// Created by 禹舜 on 2023/11/27.
//

#ifndef STRUCTURED_OPENGL_TYPE_HPP
#define STRUCTURED_OPENGL_TYPE_HPP

#include "Eigen/Core"
#include "Eigen/Dense"
#include "mutil_dimasion_data.hpp"

typedef Eigen::Matrix4f Mat4f;
typedef Eigen::Matrix3f Mat3f;
typedef Eigen::Vector4f Vec4f;
typedef Eigen::Vector3f Vec3f;
typedef Eigen::Vector2f Vec2f;

typedef Utils::MultiDimensionData<float, 3> PointsCoordinate;
typedef Utils::MultiDimensionData<unsigned int, 3> TrianglesIndices;
typedef Utils::MultiDimensionData<float, 2> TextureCoordinate;


#endif //STRUCTURED_OPENGL_TYPE_HPP
