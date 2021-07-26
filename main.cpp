#include <iostream>
#include <exception>
#include "IoC.hpp"

class X {
public:
    int GetZ() const noexcept {
        return z;
    }
    float GetA() const noexcept {
        return a;
    }

private:
    int z;
    float a;
};

class Z {
public:
    X m_x;
    std::string m_name;
};

int main() {
    try {
        IoC<X> xContainer;
        xContainer.RegisterArguments(55);
        xContainer.RegisterArguments(9.9f, 4u);

        IoC<Z> zContainer;
        zContainer.RegisterArguments(xContainer.ResolvePtr());
        zContainer.RegisterArguments(std::string("Terry"), sizeof(X));

        Z z = zContainer.Resolve();

        std::cout << z.m_name << " " << z.m_x.GetA();
    }
    catch (std::exception& e) {
        std::cout << e.what();
    }

    return 0;
}