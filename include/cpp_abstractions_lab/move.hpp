#pragma once

#include <type_traits>

template<typename T>
[[nodiscard]] constexpr std::remove_reference_t<T>&& my_move(T&& val) noexcept{
    return static_cast<std::remove_reference_t<T>&&>(val); 
}

// std::move uses 
// std::remove_reference<T>::type&&
// which forces it to add a 'typename' keyword in the return value