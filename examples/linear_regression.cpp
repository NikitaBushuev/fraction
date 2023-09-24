#include <fraction/models/linear_regression.hpp>

#include <iostream>

int main(int argc, char **argv) {
    namespace fc = fraction;

    auto x = fc::arange<int, 16, 32>().cast<float>();
    auto y = fc::arange<int, 32, 48>().cast<float>();

    auto lr = fc::linear_regression<float>(x, y);

    std::cout
        << "x: " << x << "\n"
        << "y: " << y << "\n"
        << "\n";

    std::cout
        << "regression:" << " "
        << "coeff=" << lr.coeff << ", "
        << "intercept=" << lr.intercept << "\n"
        << "\n";
    
    std::cout
        << "prediction: " << lr.predict(x) << "\n"
        << "\n";

    return 0;
}