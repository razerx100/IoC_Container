#ifndef __INVERSION_OF_CONTROL_HPP__
#define __INVERSION_OF_CONTROL_HPP__
#include <memory>
#include <cstring>

template<typename T>
class IoC {
public:
    IoC() {
        m_pData = std::unique_ptr<std::uint8_t>(new std::uint8_t[sizeof(T)]);
    }
    virtual ~IoC() = default;

    template<typename U>
    void RegisterArguments(U* arg, std::uint64_t offSet = 0u)
        noexcept {
        memcpy(m_pData.get() + offSet, arg, sizeof(U));
    }
    
    template<typename U>
    void RegisterArguments(const U& arg, std::uint64_t offSet = 0u)
        noexcept {
        memcpy(m_pData.get() + offSet, &arg, sizeof(U));
    }

    T& Resolve() noexcept {
        return *reinterpret_cast<T*>(m_pData.get());
    }

    T* ResolvePtr() noexcept {
        return reinterpret_cast<T*>(m_pData.get());
    }

    void Release() noexcept {}

protected:
    std::unique_ptr<std::uint8_t> m_pData;
};
#endif