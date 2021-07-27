#include <iostream>
#include <exception>
#include "IoC.hpp"

class X {
public:
    ~X() {
        std::cout << "Xout\n";
    }

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
    Z() {
        std::cout << "Ctor?\n";
    }
    ~Z() {
        std::cout << "Good bye\n";
    }

    void Init() {
        m_name = "Sora";
        std::cout << m_name << " " << m_x.GetA() << "\n";
    }

    X m_x;
    std::string m_name;
};

struct A {
    Z z;
};

int main() {
    try {
        IoC<X> xContainer;
        xContainer.RegisterArguments(55);
        xContainer.RegisterArguments(9.9f, 4u);

        X x = xContainer.Resolve();
        X y = xContainer.Resolve();

        IoC<Z> zContainer;
        zContainer.RegisterArguments(xContainer.Resolve());
        zContainer.RegisterArguments(std::string("Terry"), sizeof(X));
        zContainer.RegisterInitFunction(&Z::Init);

        Z z = zContainer.Resolve();
        Z a = zContainer.Resolve();

        IoC<A> aContainer;
        aContainer.RegisterArguments(zContainer.Resolve());
    }
    catch (std::exception& e) {
        std::cout << e.what();
    }

    return 0;
}