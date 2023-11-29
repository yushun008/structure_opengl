//
// Created by 禹舜 on 2023/11/28.
//

#ifndef STRUCTURED_OPENGL_MULTI_DIMENSION_DATA_HPP
#define STRUCTURED_OPENGL_MULTI_DIMENSION_DATA_HPP

#include "memory"
#include "vector"
#include "iostream"

namespace Utils {

    template<typename T, unsigned int _D>
    class MultiDimensionData {
    public:
        MultiDimensionData() {}

        MultiDimensionData(unsigned int element_num) {
            _element_num = element_num;
            _size = element_num * _D;
            _data = (T *) malloc(sizeof(T) * _size);
        }

        ~MultiDimensionData() {
            if (_data) {
                free(_data);
                _data = nullptr;
            }
        }

        void push_back(std::vector<T> value) {
            if (value.size() != _D) {
                std::cerr << "insert value dimension failed:insert " << value.size() << " dimension,but except " << _D
                          << std::endl;
            }
            for (int i = 0; i < _D; i++) {
                _data[_len] = value[i];
                _len++;
            }
        }

        T *data() {
            return _data;
        }

        void print(const std::string &info) const {
            std::cout << "++++++++++++" << info << "++++++++++++" << std::endl;
            for (int i = 0; i < _element_num; i++) {
                for (int j = 0; j < _D; j++) {
                    std::cout << _data[i * _D + j] << "  ";
                }
                std::cout << std::endl;
            }
        }

    private:
        unsigned int _element_num;
        unsigned int _size;
        unsigned int _len = 0;
        T *_data = nullptr;
    };

} // Utils

#endif
