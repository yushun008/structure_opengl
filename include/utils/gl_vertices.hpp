//
// Created by 禹舜 on 2023/11/28.
//

#ifndef STRUCTURED_OPENGL_GL_VERTICES_HPP
#define STRUCTURED_OPENGL_GL_VERTICES_HPP

#include "glad/glad.h"
#include "iostream"

namespace Utils {

    class GLVertices {
    public:
        GLVertices() : _vao_num(1), _vbo_num(2) {
            std::cout << "vertices structure\n";
            _vao = (unsigned int *) malloc(sizeof(unsigned int) * _vao_num);
            _vbo = (unsigned int *) malloc(sizeof(unsigned int) * _vbo_num);
            glGenVertexArrays(_vao_num, _vao);
            glBindVertexArray(_vao[0]);
            glGenBuffers(_vbo_num, _vbo);
        }

        GLVertices(unsigned int vao_num, unsigned int vbo_num) : _vao_num(vao_num), _vbo_num(vbo_num) {
            glGenVertexArrays(_vao_num, _vao);
        }

        ~GLVertices() {
            std::cout << "destroy GLVertices" << std::endl;
            if (_vao) {
                free(_vao);
                _vao = nullptr;
            }
            if (_vbo) {
                free(_vbo);
                _vbo = nullptr;
            }
        }

        void set_vertex_data(float *data, unsigned int size) {
            glBindBuffer(GL_ARRAY_BUFFER, _vbo[0]);
            glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, NULL);
            glEnableVertexAttribArray(0);
        }

        void set_indices(unsigned int *indices, unsigned int size) {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vbo[1]);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
        }

        void bindBuffer(unsigned int index) {
            glBindBuffer(GL_ARRAY_BUFFER, _vbo[index]);
        }

        void bindVertexArray(unsigned int index) {
            glBindVertexArray(_vao[index]);
        }

    public:
        unsigned int *_vao = nullptr;
        unsigned int *_vbo = nullptr;
    private:
        int _vao_num;
        int _vbo_num;
    };

} // Utils

#endif //STRUCTURED_OPENGL_GL_VERTICES_HPP
