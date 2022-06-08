#include "Rational.hpp"
#include "BigInteger.hpp"
#include <iostream>

using namespace std;

int main()
{
    Rational<int> x(100, 1);
    Rational<int> y(1, 2);

    cout << x * y << "\n";

    return 0;
}