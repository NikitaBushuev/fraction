# Fraction Framework
The Machine Learning Framework

Fraction Framework is a C++17 library that provides a simple and easy-to-use interface for machine learning tasks. It includes various machine learning models, data manipulation tools, and utilities to make your machine learning projects efficient and enjoyable.

## Getting Started

Before you begin, make sure you have Fraction Framework installed and set up in your C++ development environment.

## Example: Linear Regression

Let's walk through a simple example of linear regression using Fraction Framework. In this example, we'll generate some sample data, perform linear regression, and make predictions.

## Building the Example

To build and run the example, follow these steps:

1. Clone this repository to your local machine:

   ```bash
   git clone https://github.com/nikitabushuev/fraction-framework.git
   cd fraction-framework
    ```

2. Create a build directory:

    ```bash
    mkdir build
    cd build
    ```

3. Use CMake to configure the project and generate build files:

    ```bash
    cmake ..
    ```

4. Build the project:

    ```bash
    make
    ```

## Running the Example

After building the project, you can run the linear regression example:

```bash
examples/linear_regression
```

## Example source

```cpp
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
```

This code demonstrates how to use Fraction Framework to perform linear regression. You can adapt and extend this example for your own machine learning projects. Enjoy using Fraction Framework!