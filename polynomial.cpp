#include <iostream>
#include <vector>
#include <string>
#include <cmath>
 // Include the json library
#include "json.hpp"

using json = nlohmann::json;

// Function to calculate the product of all elements in a vector
double product_of_roots(const std::vector<double>& roots) {
    double product = 1.0;
    for (double root : roots) {
        product *= root;
    }
    return product;
}

// Function to find the constant term of the polynomial
double find_constant_term(const std::string& json_input) {
    // Parse the JSON input
    json data = json::parse(json_input);
    int degree = data["degree"];
    double leading_coefficient = data.value("leading_coefficient", 1.0);  // Default to 1 if not provided
    std::vector<double> roots = data["roots"];

    // Check if the number of roots matches the degree
    if (roots.size() != degree) {
        throw std::invalid_argument("The number of roots must match the degree of the polynomial.");
    }

    // Calculate the product of the roots
    double root_product = product_of_roots(roots);

    // Calculate the constant term: c = a_m * (-1)^m * (r_1 * r_2 * ... * r_m)
    double constant_term = leading_coefficient * std::pow(-1, degree) * root_product;

    return constant_term;
}

int main() {
    // Example JSON input
    std::string json_input = R"({
        "degree": 3,
        "leading_coefficient": 2,
        "roots": [1, -2, 3]
    })";

    try {
        double constant_term = find_constant_term(json_input);
        std::cout << "The constant term is: " << constant_term << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
