#include "polska_calc.h"
#include <iostream>

int main(void) {
    std::string inp = "30 + 4 * 2 / (5 - 1)";
    PolskaCalc* polska = new PolskaCalc(inp);

    std::cout << "orig: " << inp << std::endl;
    std::cout << "polska: " << polska->get_expr() << std::endl;
    std::cout << "polska result: " << polska->eval() << std::endl;

    return 0;
}
