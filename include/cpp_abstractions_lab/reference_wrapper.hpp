#pragma once

template<typename T>
class ReferenceWrapper{
private:
    T* ptr;
public:
    ReferenceWrapper(const T&) : ptr(&T) {}
    T& get() const noexcept {return *ptr;}
    operator T&() const noexcept {return get();}
};