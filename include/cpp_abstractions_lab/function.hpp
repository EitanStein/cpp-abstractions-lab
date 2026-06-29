#pragma once
#include <utility>
#include <exception>

// TODO
// add stack allocation option

// make sure this works with 
// lambdas
// free functions
// member functions
// static functions

// upgrade to support
// constexpr functions
// implement small function optimiziation

class bad_function_access : public std::exception{
public:
    bad_function_access() {}

    const char* what() const noexcept override {
        return "bad function access";
    }
};

template<typename>
class Function;

template<typename ReturnType, typename... Args>
class Function<ReturnType(Args...)> {
private:
    void* object;
    ReturnType(*invoke)(void*, Args&&...);
    void(*destroy)(void*);
    void*(*copy)(void*);

    template<typename Func>
    static ReturnType invoke_fn(Args&&... args){
        return (*static_cast<Func*>(object))(std::forward<Args>(args)...);
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

    template<typename Func>
    Function(Func&& func) {
        object = new Func(std::move(func));
        invoke = &invoke_fn<Func>;
        destroy = &delete_fn<Func>;
        copy = &copy_fn<Func>;
    }
    template<typename Func>
    Function(const Func& func) {
        object = new Func(func);
        invoke = &invoke_fn<Func>;
        destroy = &delete_fn<Func>;
        copy = &copy_fn<Func>;
    }
    ~Function() {
        destroy(object);
    }

    ReturnType operator()(Args... args){
        if(object == nullptr)
            throw bad_function_access();

        return invoke(std::forward<Args>(args)...);
    }

    Function& operator=(const Function& other){
        destroy(object);

        
        object = other.copy(other.object);

        invoke = other.invoke;
        destroy = other.destroy;
        copy = other.copy;

        return *this;
    }

    Function& operator=(Function&& other) noexcept{
        destroy(object);

        object = std::move(other.object);
        other.object = nullptr;

        invoke = other.invoke;
        destroy = other.destroy;
        copy = other.copy;

        return *this;
    }

    template<typename Func>
    Function& operator=(Func&& func){
        destroy(object);

        using DecayedFunc = std::decay_t<Func>;
        object = new DecayedFunc(std::forward<func>(func));

        invoke = &invoke_fn<DecayedFunc>;
        destroy = &delete_fn<DecayedFunc>;
        copy = &copy_fn<DecayedFunc>;

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
