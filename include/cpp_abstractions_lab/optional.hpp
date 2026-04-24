#pragma once


struct nullopt_t{
    constexpr explicit nullopt_t(int) {};
};

inline constexpr nullopt_t nullopt{0};

//TODO template<typename T>
class Optional{
private:
    int val;
    bool has_val;
public:
    Optional() : has_val(false) {}
    Optional(nullopt_t) : has_val(false) {}
    Optional(int val) : has_val(true), val(val) {}
    Optional(const Optional& other);
    Optional(Optional&& other) noexcept;

    Optional& operator=(const Optional& other) = default;
    Optional& operator=(Optional&& other) = default;

    bool operator==(const Optional& other) const;
    bool operator==(int other) const;
    bool operator!=(const Optional& other) const;
    bool operator!=(int other) const;

    bool has_value() const;
    int value() const;
    int value_or(int default_value) const;

    void reset() noexcept {has_val = false;}
};