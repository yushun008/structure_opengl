//
// Created by 禹舜 on 2023/11/28.
//

#ifndef STRUCTURED_OPENGL_BASE_SHAPE_HPP
#define STRUCTURED_OPENGL_BASE_SHAPE_HPP

#include "type.hpp"

namespace Utils {

    class BaseShape {
    public:
        BaseShape() {}

        virtual void calculate_vertices_coordinate() = 0;

        virtual void calculate_triangle_indices() = 0;

        virtual void calculate_texture_coordinate() = 0;

        virtual unsigned int triangle_num() const = 0;

        virtual unsigned int vertices_num() const = 0;

        float *points_coordinate() {
            return _vertices_coordinate->data();
        }

        unsigned int *indices() {
            return _indices->data();
        }

        float *texture_coordinate() {
            return _texture_coordinate->data();
        }

    protected:
        std::shared_ptr<TrianglesIndices> _indices;
        std::shared_ptr<PointsCoordinate> _vertices_coordinate;
        std::shared_ptr<TextureCoordinate> _texture_coordinate;
    };

} // Utils

#endif //STRUCTURED_OPENGL_BASE_SHAPE_HPP
