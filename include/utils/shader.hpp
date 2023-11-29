//
// Created by 禹舜 on 2023/11/27.
//

#ifndef STRUCTURED_OPENGL_SHADER_HPP
#define STRUCTURED_OPENGL_SHADER_HPP

#include "glad/glad.h"
#include "iostream"
#include "string"
#include "fstream"
#include "sstream"

#include "type.hpp"

namespace Utils {

    class Shader {
    public:
        Shader(std::string &vertx_src_path, std::string &fragment_src_path) {
            GLuint vertex_shader_id = create_shader(vertx_src_path, GL_VERTEX_SHADER);
            GLuint fragment_shader_id = create_shader(fragment_src_path, GL_FRAGMENT_SHADER);
            render_program_id = glCreateProgram();
            glAttachShader(render_program_id, vertex_shader_id);
            glAttachShader(render_program_id, fragment_shader_id);
            glLinkProgram(render_program_id);
            int success;
            char info[512];
            glGetProgramiv(render_program_id, GL_LINK_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(render_program_id, 512, NULL, info);
                std::cerr << "link program failed!" << std::endl;
                std::cerr << info << std::endl;
            }
        }

        void Use() {
            glUseProgram(render_program_id);
        }

        void setMat4f(const std::string &value_name, Mat4f value) {
            std::cout << value_name << ":\n" << value << std::endl;
            std::cout << "render program id:" << render_program_id << std::endl;
            glUniformMatrix4fv(glGetUniformLocation(render_program_id, value_name.c_str()), 1, GL_FALSE, value.data());
        }

        void setMat3f(const std::string &value_name, Mat3f value) {
            glUniformMatrix3fv(glGetUniformLocation(render_program_id, value_name.c_str()), 1, GL_FALSE, value.data());
        }

        void setVec3f(const std::string &value_name, Vec3f value) {
            glUniform3f(glGetUniformLocation(render_program_id, value_name.c_str()), value.x(), value.y(), value.z());
        }

        void setVec4f(const std::string &value_name, Vec4f value) {
            glUniform4f(glGetUniformLocation(render_program_id, value_name.c_str()), value.x(), value.y(), value.z(),
                        value.w());
        }

        void setVec2f(const std::string &value_name, Vec2f value) {
            glUniform2f(glGetUniformLocation(render_program_id, value_name.c_str()), value.x(), value.y());
        }

    private:
        GLuint create_shader(std::string &src_path, GLenum type) {
            std::ifstream shader_stream;
            std::string context_str;
            const char *context_char;
            shader_stream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
            try {
                shader_stream.open(src_path);
                std::stringstream context_stream;
                context_stream << shader_stream.rdbuf();
                shader_stream.close();
                context_str = context_stream.str();
            } catch (std::ifstream::failure &e) {
                std::cerr << "ERROR:SHADER::FILE_NOT_SUCCESSFULLY_READ:" << e.what() << std::endl;
            }
            context_char = context_str.c_str();
            GLuint shader_id = glCreateShader(type);
            glShaderSource(shader_id, 1, &context_char, NULL);
            glCompileShader(shader_id);
            int success;
            char info[512];
            glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(shader_id, 512, NULL, info);
                std::cerr << "compile " << src_path << " failed!" << std::endl;
                std::cerr << info << std::endl;
            }
            return shader_id;
        }

    public:
        GLuint render_program_id;

    };
}


#endif //STRUCTURED_OPENGL_SHADER_HPP
