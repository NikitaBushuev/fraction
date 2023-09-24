#pragma once

#include <fraction/core/tensor.hpp>

namespace fraction {
    template <class _Lr>
    class linear_regression {
    public:
        _Lr coeff {}, intercept {};

        template <class _Tp, std::size_t _Nm>
        linear_regression(const tensor<_Tp, _Nm> &x, const tensor<_Tp, _Nm> &y) {
            auto sum_x = x.sum();
            auto sum_y = y.sum();
        
            auto mean_x = sum_x / (float) _Nm;
            auto mean_y = sum_y / (float) _Nm;
            
            auto num = 0.0f;
            auto den = 0.0f;

            for (std::size_t i = 0; i < _Nm; i++) {
                num += (x[i] - mean_x) * (y[i] - mean_y);
                den += (x[i] - mean_x) * (x[i] - mean_x);
            }

            this->coeff = num / (float) den;

            this->intercept = mean_y - this->coeff * mean_x;
        }

        template <class _Tp, std::size_t _Nm>
        auto predict(const tensor<_Tp, _Nm> &x) {
            auto y = x;

            y *= this->coeff;
            y += this->intercept;

            return y;
        }
    };
}