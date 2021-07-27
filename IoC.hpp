#ifndef __INVERSION_OF_CONTROL_HPP__
#define __INVERSION_OF_CONTROL_HPP__
#include <memory>
#include <cstring>

template<typename T>
class IoC {
public:
    IoC() : m_initFunc(nullptr) {
        m_pInstance = std::unique_ptr<T>(
            reinterpret_cast<T*>(new std::uint8_t[sizeof(T)])
            );
    }

    template<typename U>
    void RegisterArguments(const U& arg, std::uint64_t offSet = 0u)
        noexcept {
        *reinterpret_cast<U*>(
            reinterpret_cast<std::uint8_t*>(m_pInstance.get()) + offSet) = arg;
    }

    void RegisterInitFunction(void(T::* func)()) {
        m_initFunc = func;
    }

    T& Resolve() noexcept {
        T* ptr = m_pInstance.get();
        if (m_initFunc)
            (ptr->*(m_initFunc))();
        return *ptr;
    }

    T* ResolvePtr() noexcept {
        T* ptr = m_pInstance.get();
        if (m_initFunc)
            (ptr->*(m_initFunc))();
        return ptr;
    }

protected:
    std::unique_ptr<T> m_pInstance;
    void(T::* m_initFunc)();
};
#endif