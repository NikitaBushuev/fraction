#include <fraction/core/tensor.hpp>

#include <gtest/gtest.h>

namespace fc = fraction;

TEST(Tensor, Create) {
    fc::tensor<int, 3, 2, 1> t;
}