#pragma once

#include <numeric>
#include <ostream>

namespace fraction {
    template <class _Tp, std::size_t ..._Nms>
    class tensor;

    template <class _Tp>
    class tensor<_Tp> {
    public:
        using value_type = _Tp;

        tensor() = default;

        template <class _vTp>
        tensor(const _vTp &other) {
            this->operator=(other);
        }
        
        template <class _vTp, class _Fn>
        tensor &inplace_binary(const _vTp &other, const _Fn &functor) {
            functor(this->operator value_type &(), other);
            return *this;
        }

        template <class _vTp, class _Fn>
        tensor &inplace_binary(const tensor<_vTp> &other, const _Fn &functor) {
            functor(this->operator value_type &(), (const _vTp &) other);
            return *this;
        }

        template <class _vTp, class _Fn>
        tensor &inplace_unary(const _Fn &functor) {
            return functor(this->operator value_type &()), *this;
        }

        operator value_type &() {
            return __values[0];
        }

        operator const value_type &() const {
            return __values[0];
        }

    protected:
        value_type __values[1] {};
    };

    template <class _Tp, std::size_t _Nm, std::size_t ..._Nms>
    class tensor<_Tp, _Nm, _Nms...> {
    public:
        using value_type = tensor<_Tp, _Nms...>;

        using size_type = std::size_t;

        tensor() = default;

        template <class _vTp>
        tensor(const _vTp &other) {
            this->operator=(other);
        }

        template <class _vTp, class _Fn>
        tensor &inplace_binary(const _vTp &other, const _Fn &functor) {
            for (size_type i = 0; i < _Nm; ++i) {
                this->operator[](i).inplace_binary(other, functor);
            }
            return *this;
        }

        template <class _vTp, class _Fn>
        tensor &inplace_binary(const tensor<_vTp, _Nm, _Nms...> &other, const _Fn &functor) {
            for (size_type i = 0; i < _Nm; ++i) {
                this->operator[](i).inplace_binary(other[i], functor);
            }
            return *this;
        }

        template <class _vTp, class _Fn>
        tensor &inplace_unary(const _Fn &functor) {
            for (size_type i = 0; i < _Nm; ++i) {
                this->operator[](i).inplace_unary(functor);
            }
            return *this;
        }

        _Tp sum() const {
            _Tp ret {0};

            for (std::size_t i = 0; i < _Nm; ++i) {
                ret += this->operator[](i);
            }
            
            return ret;
        }

        template <class _vTp>
        tensor<_vTp, _Nm, _Nms...> cast() {
            return *this;
        }

        template <class _vTp>
        tensor &operator=(const _vTp &other) {
            return this->inplace_binary(other, [] (auto &a, const auto &b) { a = b; });
        }

        template <class _vTp>
        tensor &operator+=(const _vTp &other) {
            return this->inplace_binary(other, [] (auto &a, const auto &b) { a += b; });
        }

        template <class _vTp>
        tensor &operator-=(const _vTp &other) {
            return this->inplace_binary(other, [] (auto &a, const auto &b) { a -= b; });
        }

        template <class _vTp>
        tensor &operator*=(const _vTp &other) {
            return this->inplace_binary(other, [] (auto &a, const auto &b) { a *= b; });
        }

        template <class _vTp>
        tensor &operator/=(const _vTp &other) {
            return this->inplace_binary(other, [] (auto &a, const auto &b) { a /= b; });
        }

        value_type &operator[](const size_type &i) {
            return this->__values[i];
        }

        const value_type &operator[](const size_type &i) const {
            return this->__values[i];
        }
    
    protected:
        value_type __values[_Nm] {};
    };

    template <class _Tp, _Tp _Begin, _Tp _End>
    auto arange() {
        tensor<_Tp, _End - _Begin> t(_Begin);

        for (std::size_t i = 0; i < _End - _Begin; ++i) {
            t[i] += i;
        }

        return t;
    }
}

template <class _Tp>
std::ostream &operator<<(std::ostream &os, const fraction::tensor<_Tp> &tensor) {
    return os << (const _Tp &) tensor;
}

template <class _Tp, std::size_t _Nm, std::size_t ..._Nms>
std::ostream &operator<<(std::ostream &os, const fraction::tensor<_Tp, _Nm, _Nms...> &tensor) {
    os << "{";

    if (_Nm > 0)
        os << tensor[0];

    for (std::size_t i = 1; i < _Nm; ++i)
        os << ", " << tensor[i];

    return os << "}";
}