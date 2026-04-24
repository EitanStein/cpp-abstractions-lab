// #include "cpp_abstractions_lab/optional.hpp"
// #include <exception>
// #include <utility>

// template<typename T>
// Optional<T>::Optional(const Optional<T>& other): has_val(other.has_val) {
//     assign_new_storage(*(other.get_storage_ptr()));
// }
// template<typename T>
// Optional<T>::Optional(Optional<T>&& other) noexcept: has_val(std::move(other.has_val)){
//     assign_new_storage(std::move(*other.get_storage_ptr()));
//     other.has_val = false;
// }

// template<typename T>
// bool Optional<T>::operator==(const Optional<T>& other) const{
//     if(has_val != other.has_val)
//         return false;

//     if(!has_val)
//         return true;

//     return (*get_storage_ptr() == *other.get_storage_ptr());
// }
// template<typename T>
// bool Optional<T>::operator==(const T& other) const{
//     if(!has_val)
//         return false;

//     return (*get_storage_ptr() == other);
// }

// template<typename T>
// bool Optional<T>::operator!=(const Optional<T>& other) const {return !(*this==other);}
// template<typename T>
// bool Optional<T>::operator!=(const T& other) const {return !(*this==other);};

// template<typename T>
// Optional<T>& Optional<T>::operator=(const Optional<T>& other){
//     if(!other.has_val)
//         reset();

//     if(!has_val){
//         assign_new_storage(*other.get_storage_ptr());
//         has_val = true;  
//     }
//     else{
//         *get_storage_ptr() = *other.get_storage_ptr();
//     }

//     return *this;
// }
// template<typename T>
// Optional<T>& Optional<T>::operator=(Optional<T>&& other){
//     if(!other.has_val)
//         reset();

//     if(!has_val){
//         assign_new_storage(std::move(*other.get_storage_ptr()));
//         has_val = true;  
//     }
//     else{
//         *get_storage_ptr() = std::move(*other.get_storage_ptr());
//     }

//     other.has_val = false;
//     return *this;
// }


// template<typename T>
// bool Optional<T>::has_value() const {return has_val;}
// template<typename T>
// const T& Optional<T>::value() const {
//     if(!has_val)
//         throw bad_optional_access();
    
//     return *get_storage_ptr();
// }

// template<typename T>
// const T& Optional<T>::value_or(const T& default_value) const{
//     if(!has_val)
//         return default_value;
    
//     return *get_storage_ptr();
// }