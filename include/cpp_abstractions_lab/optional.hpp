#pragma once
#include <exception>
#include <utility>


class bad_optional_access : public std::exception{
public:
    bad_optional_access() {}

    const char* what() const noexcept override {
        return "bad optional access";
    }
};


struct nullopt_t{
    constexpr explicit nullopt_t(int) {};
};

inline constexpr nullopt_t nullopt{0};

template<typename T>
class Optional{
private:
    alignas(T) unsigned char storage[sizeof(T)];
    bool has_val;

    void assign_new_storage(const T& val) { new (storage) T(val); }
    void assign_new_storage(T&& val) { new (storage) T(val); }

    T* get_storage_ptr() { return reinterpret_cast<T*>(storage);}
    const T* get_storage_ptr() const { return reinterpret_cast<const T*>(storage);}
public:
    Optional() : has_val(false) {}
    Optional(nullopt_t) : has_val(false) {}
    Optional(const T& val) : has_val(true)
    {
        assign_new_storage(val);
    }
    Optional(const Optional& other): has_val(other.has_val) 
    {
        assign_new_storage(*(other.get_storage_ptr()));
    }
    Optional(Optional&& other) noexcept: has_val(std::move(other.has_val))
    {
        assign_new_storage(std::move(*other.get_storage_ptr()));
        other.has_val = false;
    }

    ~Optional() noexcept {
        reset();
    }

    Optional& operator=(const Optional& other)
    {
        if(!other.has_val)
            reset();

        if(!has_val){
            assign_new_storage(*other.get_storage_ptr());
            has_val = true;  
        }
        else{
            *get_storage_ptr() = *other.get_storage_ptr();
        }

        return *this;
    }
    Optional<T>& operator=(Optional<T>&& other)
    {
        if(!other.has_val)
            reset();

        if(!has_val){
            assign_new_storage(std::move(*other.get_storage_ptr()));
            has_val = true;  
        }
        else{
            *get_storage_ptr() = std::move(*other.get_storage_ptr());
        }

        other.has_val = false;
        return *this;
    }

    bool operator==(const Optional& other) const
    {
        if(has_val != other.has_val)
            return false;

        if(!has_val)
            return true;

        return (*get_storage_ptr() == *other.get_storage_ptr());
    }
    bool operator==(const T& other) const
    {
        if(!has_val)
            return false;

        return (*get_storage_ptr() == other);
    }

    bool operator!=(const Optional& other) const { return !(*this==other); };
    bool operator!=(const T& other) const { return !(*this==other); };


    bool has_value() const { return has_val; }
    const T& value() const
    {
        if(!has_val)
            throw bad_optional_access();
        
        return *get_storage_ptr();
    }
    const T& value_or(const T& default_value) const
    {
        if(!has_val)
            return default_value;
        
        return *get_storage_ptr();
    }


    void reset() noexcept {
        if(!has_val)
            return;

        T* ptr = get_storage_ptr();
        ptr->~T();
        has_val = false;
    }
};