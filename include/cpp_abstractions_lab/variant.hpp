#pragma once
#include <exception>
#include <utility>
#include <cstddef>
#include <algorithm>

template<typename T, typename... Types>
struct index_of;


template<typename T, typename... Rest>
struct index_of<T, T, Rest...>{
    static constexpr std::size_t value = 0;
};

template<typename T, typename U, typename... Rest>
struct index_of<T, U, Rest...>{
    static constexpr std::size_t value = 1 + index_of<T, Rest...>::value;
};


template <size_t I, typename... Types>
struct type_at;

template <typename T, typename... Rest>
struct type_at<0, T, Rest...> {
    using type = T;
};

template <size_t I, typename T, typename... Rest>
struct type_at<I, T, Rest...> {
    using type = typename type_at<I - 1, Rest...>::type;
};


class bad_variant_access : public std::exception{
public:
    bad_variant_access() {}

    const char* what() const noexcept override {
        return "bad variant access";
    }
};


template<typename... Types>
class Variant{
private:
    static constexpr size_t num_types = sizeof...(Types);
    static constexpr size_t max_size = std::max({sizeof(Types)...});
    static constexpr size_t max_align = std::max({alignof(Types)...});

    size_t type_index;

    alignas(max_align) std::byte storage[max_size];

    template<typename T> // TODO catch failed assignment to default to invalid type
    void assign_value(const T& val){ new (storage) T(val); type_index = index_of<T, Types...>::value; }
    template<typename T>
    void assign_value(T&& val){ new (storage) T(std::move(val)); type_index = index_of<T, Types...>::value; }

    template<typename T>
    void erase_storage() noexcept {
        T* storage_ptr = std::launder(reinterpret_cast<T*>(storage));
        storage_ptr->~T();

        type_index = num_types;
    }

public:
    Variant() {}
    template<typename T>
    Variant(const T& value) { assign_value(value); } // TODO
    template<typename T>
    Variant(T&& value) { assign_value(std::move(value)); } // TODO

    template<size_t I>
    auto& get(){
        using Type = typename type_at<I, Types...>::type;

        if(type_index != I)
            throw bad_variant_access();

        
        return *std::launder(reinterpret_cast<Type*>(storage));
    }

    template<typename T>
    auto& get(){
        constexpr size_t index = index_of<T, Types...>::value;
        return get<index>();
    }
};