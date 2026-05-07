#pragma once
#include <utility>
#include <exception>


class bad_function_access : public std::exception{
public:
    bad_function_access() {}

    const char* what() const noexcept override {
        return "bad optional access";
    }
};

template<typename>
class Function;

template<typename R, typename... Args>
class Function<R(Args...)> {
private:
    void* object;
    R(*invoke)(void*, Args&&...);
    void(*destroy)(void*);
    void*(*copy)(void*);

    template<typename Func>
    static R invoke_fn(void* obj, Args&&... args){
        return (*static_cast<Func*>(obj))(std::forward<Args>(args)...);
    }

    template<typename Func>
    static void delete_fn(void* obj){
        delete static_cast<Func*>(obj);
    }

    template<typename Func>
    static void* copy_fn(void* obj){
        return new Func(*static_cast<Func*>(obj));
    }


public:
    Function() { object = nullptr; }
    Function(nullptr_t) { object = nullptr; }

    // TODO add &&?
    template<typename Func>
    Function(Func func) {
        object = new Func(std::move(func));
        invoke = &invoke_fn<Func>;
        destroy = &delete_fn<Func>;
        copy = &copy_fn<Func>;
    }
    ~Function() {
        destroy(object);
    }

    R operator()(Args... args){
        if(object == nullptr)
            throw bad_function_access();

        return invoke(object, std::forward<Args>(args)...);
    }

    Function& operator=(const Function& other){
        destroy(object);

        object = copy(other.object);

        invoke = other.invoke;
        destroy = other.destroy;
        copy = other.copy;

        return *this;
    }

    Function& operator=(Function&& other){
        destroy(object);

        object = std::move(other.object);
        other.object = nullptr;

        invoke = other.invoke;
        destroy = other.destroy;
        copy = other.copy;

        return *this;
    }

    // TODO add &&?
    template<typename Func>
    Function& operator=(Func func){
        destroy(object);

        object = new Func(std::move(func));
        invoke = &invoke_fn<Func>;
        destroy = &delete_fn<Func>;
        copy = &copy_fn<Func>;

        return *this;
    }

    explicit operator bool() const{
        return object != nullptr;
    }

    void swap(Function& other) noexcept{
        std::swap(object, other.object);
        std::swap(invoke, other.invoke);
        std::swap(copy, other.copy);
        std::swap(destroy, other.destroy);
    }
};