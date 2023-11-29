//
// Created by 禹舜 on 2023/11/27.
//

#ifndef STRUCTURED_OPENGL_CAMERA_HPP
#define STRUCTURED_OPENGL_CAMERA_HPP

#include "type.hpp"

namespace Utils {

    class Camera {
        enum Direction {
            RIGHT,
            LEFT,
            UP,
            DOWN,
            FORWARD,
            BACKWARD
        };
    public:
        Camera() {
            _camera_coordinate = Vec3f(0, 2, 8);
            _camera_g = Vec3f(0, 0, 1);
            _camera_up = Vec3f(0, 1, 0);
            _camera_right = _camera_up.cross(_camera_g);
            create_view_mat();
            create_projection_matrix(-0.05773502691896256, 0.05773502691896256, 0.05773502691896256,
                                     -0.05773502691896256, 0.1f, 1000);
        }

        Camera(Vec3f &coordinate, Vec3f &g, Vec3f &up) : _camera_coordinate(coordinate), _camera_up(up), _camera_g(g) {
            _camera_right = _camera_up.cross(_camera_g);
            create_view_mat();
        }

        Mat4f view_mat() {
            return _view_mat;
        }

        Mat4f projection_mat() {
            return _projection_mat;
        }
        void translation_camera(Direction direction, float delta_time) {
            switch (direction) {
                case RIGHT:
                    _camera_coordinate.x() += (delta_time * _velocity);
                    break;
                case LEFT:
                    _camera_coordinate.x() -= (delta_time * _velocity);
                    break;
                case UP:
                    _camera_coordinate.y() += (delta_time * _velocity);
                    break;
                case DOWN:
                    _camera_coordinate.y() -= (delta_time * _velocity);
                    break;
                case FORWARD:
                    _camera_coordinate.z() += (delta_time * _velocity);
                    break;
                case BACKWARD:
                    _camera_coordinate.z() -= (delta_time * _velocity);
                    break;
            }
        }

    private:
        void create_view_mat() {
            _view_mat << _camera_right.transpose(), (-_camera_coordinate.x()),
                    _camera_up.transpose(), (-_camera_coordinate.y()),
                    _camera_g.transpose(), (-_camera_coordinate.z()),
                    0, 0, 0, 1;
        }

        void create_projection_matrix(float left, float right, float top, float bottom, float near, float far) {
            std::cout << "create projection matrix" << std::endl;
            _projection_mat << 2 * near / (right - left), 0, (left + right) / (right - left), 0,
                    0, 2 * near / (top - bottom), (top + bottom) / (top - bottom), 0,
                    0, 0, (near + far) / (near - far), 2 * far * near / (near - far),
                    0, 0, -1, 0;
            std::cout << "_projection_mat:\n" << _projection_mat << std::endl;
        }

    private:
        Vec3f _camera_coordinate;
        Vec3f _camera_g;
        Vec3f _camera_up;
        Vec3f _camera_right;
        Mat4f _view_mat;
        Mat4f _projection_mat;
        float _velocity = 0.1;

    };

} // Utils

#endif //STRUCTURED_OPENGL_CAMERA_HPP
