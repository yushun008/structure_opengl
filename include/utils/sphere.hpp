//
// Created by 禹舜 on 2023/11/28.
//

#ifndef STRUCTURED_OPENGL_SPHERE_HPP
#define STRUCTURED_OPENGL_SPHERE_HPP

#include "base_shape.hpp"

namespace Utils {

    class Sphere : public BaseShape {
    public:

        Sphere() :
                _slice_num(2), _slice_vertices_num(4), _radius(1) {
            _triangle_num = 2 * _slice_vertices_num + (_slice_num - 2) * 2;
            _vertices_num = (_slice_num - 1) * _slice_vertices_num + 2;
            _vertices_coordinate = std::make_shared<PointsCoordinate>(_vertices_num);
            _indices = std::make_shared<TrianglesIndices>(_triangle_num);
        }

        Sphere(unsigned int slice_num, unsigned int slice_vertices_num, unsigned int radius) :
                _slice_num(slice_num), _slice_vertices_num(slice_vertices_num), _radius(radius) {
            std::cout << "init Sphere" << std::endl;
            _triangle_num = 2 * _slice_vertices_num + (_slice_num - 1) * _slice_vertices_num * 2;
            _vertices_num = (_slice_num - 1) * _slice_vertices_num + 2;
            _vertices_coordinate = std::make_shared<PointsCoordinate>(_vertices_num);
            _indices = std::make_shared<TrianglesIndices>(_triangle_num);
        }

        [[nodiscard]] unsigned int triangle_num() const override {
            return _triangle_num;
        }

        [[nodiscard]] unsigned int vertices_num() const override {
            return _vertices_num;
        }

        [[nodiscard]] unsigned int vertices_size() const {
            return _vertices_num * 3 * sizeof(float);
        }

        [[nodiscard]] unsigned int indices_size() const {
            return _triangle_num * 3 * sizeof(unsigned int);
        }

        [[nodiscard]] int triangle_vertices_num() const {
            return _triangle_num * 3;
        }

        void init() {
            std::cout << "calculate vertices coordinate" << std::endl;
            calculate_vertices_coordinate();
            std::cout << "calculate indices" << std::endl;
            calculate_triangle_indices();
        }

        void print_attr() const {
            std::cout << "_slice_num:" << _slice_num << std::endl;
            std::cout << "_slice_vertices_num:" << _slice_vertices_num << std::endl;
            std::cout << "_triangle_num:" << _triangle_num << std::endl;
            std::cout << "_vertices_num:" << _vertices_num << std::endl;
            std::cout << "_triangle_vertices_num:" << triangle_vertices_num() << std::endl;
            std::cout << "indices_size:" << indices_size() << std::endl;
            std::cout << "vertices_size:" << vertices_size() << std::endl;
            _indices->print("indices");
            _vertices_coordinate->print("vertices coordinate");
        }

    private:
        void calculate_vertices_coordinate() override {
            float base_theta = M_PI / _slice_num;
            float base_phi = 2 * M_PI / _slice_vertices_num;
            std::vector<float> first_vertices = {0, -(float) _radius, 0};
            _vertices_coordinate->push_back(first_vertices);
            for (int i = 1; i < _slice_num; i++) {
                float theta = -(M_PI / 2) + base_theta * i;
                for (int j = 0; j < _slice_vertices_num; j++) {
                    float phi = j * base_phi;
                    std::vector<float> coordinate = calculate_coordinate(theta, phi);
                    _vertices_coordinate->push_back(coordinate);
                }
            }
            std::vector<float> last_vertices = {0, (float) _radius, 0};
            _vertices_coordinate->push_back(last_vertices);
        }

        void calculate_triangle_indices() override {
            for (unsigned int i = 1; i <= _slice_vertices_num; i++) {
                if (i == _slice_vertices_num) {
                    std::vector<unsigned int> value = {0, i, 1};
                    _indices->push_back(value);
                } else {
                    std::vector<unsigned int> value = {0, i, i + 1};
                    _indices->push_back(value);
                }
            }
            for (int i = 0; i < _slice_num - 2; i++) {
                for (int j = 0; j < _slice_vertices_num; j++) {
                    unsigned int a = i * _slice_vertices_num + 1 + j;
                    unsigned int b = (i + 1) * _slice_vertices_num + 1 + j;
                    unsigned int c = b + 1;
                    unsigned int d = a + 1;
                    if (a % _slice_vertices_num == 0) {
                        d = i * _slice_vertices_num + 1;
                        c = (i + 1) * _slice_vertices_num + 1;
                    }
                    std::vector<unsigned int> triangle_one = {a, b, c};
                    std::vector<unsigned int> triangle_two = {a, c, d};
                    _indices->push_back(triangle_one);
                    _indices->push_back(triangle_two);
                }
            }
            unsigned int last_slice_index_start = _vertices_num - _slice_vertices_num - 1;
            for (int i = 0; i < _slice_vertices_num; i++) {
                if (i == _slice_vertices_num - 1) {
                    std::vector<unsigned int> value = {last_slice_index_start + i, _vertices_num - 1,
                                                       last_slice_index_start};
                    _indices->push_back(value);
                } else {
                    std::vector<unsigned int> value = {last_slice_index_start + i, _vertices_num - 1,
                                                       last_slice_index_start + i + 1};
                    _indices->push_back(value);
                }
            }
        }

        virtual void calculate_texture_coordinate() override {
        }

    private:
        [[nodiscard]] std::vector<float> calculate_coordinate(float theta, float phi) const {
            float x = (float) _radius * cos(theta) * cos(phi);
            float y = (float) _radius * sin(theta);
            float z = (float) _radius * cos(theta) * sin(phi);
            std::vector<float> coordinate = {x, y, z};
            return coordinate;
        }

    private:
        unsigned int _vertices_num;
        unsigned int _triangle_num;
        unsigned int _slice_num;
        unsigned int _slice_vertices_num;
        unsigned int _radius;
    };

} // Utils

#endif //STRUCTURED_OPENGL_SPHERE_HPP
