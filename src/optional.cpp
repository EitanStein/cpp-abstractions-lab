#include "cpp_abstractions_lab/optional.hpp"
#include <exception>
#include <utility>

Optional::Optional(const Optional& other): has_val(other.has_val), val(other.val) {}
Optional::Optional(Optional&& other) noexcept: has_val(std::move(other.has_val)), val(std::move(other.val)) {}

bool Optional::operator==(const Optional& other) const{
    if(has_val != other.has_val)
        return false;

    if(!has_val)
        return true;

    return (val == other.val);
}
bool Optional::operator==(int other) const{
    if(!has_val)
        return false;

    return (val == other);
}

bool Optional::operator!=(const Optional& other) const {return !(*this==other);}
bool Optional::operator!=(int other) const {return !(*this==other);};

bool Optional::has_value() const {return has_val;}
int Optional::value() const {
    if(!has_val)
        throw bad_optional_access();
    
    return val;
}
int Optional::value_or(int default_value) const{
    if(!has_val)
        return default_value;
    
    return val;
}