#pragma once
#include <exception>
#include <utility>
#include <cstddef>
#include <algorithm>
#include <type_traits>


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


template<typename T>
static void erase_storage(void* storage_ptr) {
    T* ptr = std::launder(reinterpret_cast<T*>(storage_ptr));
    ptr->~T();
}


inline constexpr size_t variant_npos = -1;


template<typename... Types>
class Variant{
private:
    static constexpr size_t num_types = sizeof...(Types);
    static constexpr size_t invalid_type = num_types;
    static constexpr size_t max_size = std::max({sizeof(Types)...});
    static constexpr size_t max_align = std::max({alignof(Types)...});

    size_t type_index;

    alignas(max_align) std::byte storage[max_size];

    template<typename T>
    void assign_new_value_type(const T& val) noexcept { 
        try{
            new (storage) T(val); 
            type_index = index_of<T, Types...>::value;
        }
        catch(std::exception& e){
            type_index = variant_npos;
        }
    }
    template<typename T>
    void assign_new_value_type(T&& val) noexcept { 
        try{
            new (storage) T(std::move(val)); 
            type_index = index_of<T, Types...>::value; 
        }
        catch(std::exception& e){
            type_index = variant_npos;
        }
    }

    template<typename T> // assumes correct type
    void assign_value(const T& val){
        T* storage_ptr = std::launder(reinterpret_cast<T*>(storage));
        *storage_ptr = val;
    }
    template<typename T>
    void assign_value(T&& val){ 
        T* storage_ptr = std::launder(reinterpret_cast<T*>(storage));
        *storage_ptr = std::move(val);
    }


    using destroy_fn = void(*)(void*);

    static constexpr destroy_fn destroy_table[] = {
        &erase_storage<Types>...
    };

public:
    Variant() {}
    template<typename T>
    Variant(const T& value) { assign_new_value_type<T>(value); }
    template<typename T>
    Variant(T&& value) { 
        using U = std::remove_cvref_t<T>;
        assign_new_value_type<U>(std::forward<T>(value)); 
    }

    ~Variant(){ 

        destroy_table[type_index](storage);
        type_index = variant_npos;
    }

    template<typename T>
    Variant& operator=(const T& value){
        constexpr size_t index = index_of<T, Types...>::value;
        if(index != type_index){
            destroy_table[type_index](storage);
            assign_new_value_type<T>(value);
        }
        else{
            assign_value<T>(value);
        }

        return *this;
    }

    template<typename T>
    Variant& operator=(T&& value){
        using U = std::remove_cvref_t<T>;
        constexpr size_t index = index_of<U, Types...>::value;
        if(index != type_index){
            destroy_table[type_index](storage);
            assign_new_value_type<U>(std::forward<T>(value));
        }
        else{
            assign_value<U>(std::forward<T>(value));
        }

        return *this;
    }

    template<size_t I>
    auto& get(){
        using Type = typename type_at<I, Types...>::type;

        if(type_index != I)
            throw bad_variant_access();

        
        return *std::launder(reinterpret_cast<Type*>(storage));
    }

    template<size_t I>
    constexpr auto* get_if() const{
        using Type = typename type_at<I, Types...>::type;

        if(type_index != I)
            return nullptr;

        
        return std::launder(reinterpret_cast<Type*>(storage));
    }
    template<size_t I>
    constexpr const auto* get_if() const{
        using Type = typename type_at<I, Types...>::type;

        if(type_index != I)
            return nullptr;

        return std::launder(reinterpret_cast<const Type*>(storage));
    }

    template<typename T>
    auto& get(){
        constexpr size_t index = index_of<T, Types...>::value;
        return get<index>();
    }

    template<typename T>
    constexpr T* get_if() const{
        constexpr size_t index = index_of<T, Types...>::value;

        if(type_index != index)
            return nullptr;

        return std::launder(reinterpret_cast<T*>(storage));
    }

    template<typename T>
    constexpr const T* get_if() const{
        constexpr size_t index = index_of<T, Types...>::value;

        if(type_index != index)
            return nullptr;

        return std::launder(reinterpret_cast<const T*>(storage));
    }

    constexpr bool valueless_by_exception() const noexcept{ return variant_npos == type_index; }
    constexpr size_t index() const { return type_index; }
};