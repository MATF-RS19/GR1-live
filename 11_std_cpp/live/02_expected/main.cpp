#include <iostream>
#include <algorithm>
#include <string>

#include <pwd.h>

//#include "expected/tl/expected.hpp"
#include <tl/expected.hpp>

enum class user_error_t {
    USER_NOT_FOUND,
    UNKNOWN_ERROR
};

std::ostream& operator<<(std::ostream& out, user_error_t error)
{
    return out <<
        (error == user_error_t::UNKNOWN_ERROR
            ?  "Unknown error"
            : "User not found!");
}

tl::expected<std::string, user_error_t> username_for_id(uid_t user_id)
{
    auto pw = getpwuid(user_id);

    if (pw) {
        return std::string(pw->pw_name);
    } else {
        return tl::unexpected(user_error_t::USER_NOT_FOUND);
    }
}

template <class T, class E, class F>
auto transform(const tl::expected<T, E>& exp, F trafo) ->
    tl::expected<decltype(std::invoke(trafo, *exp)), E>
{
    if (exp) {
        return std::invoke(trafo, *exp);
    } else {
        return tl::unexpected(exp.error());
    }
}

std::string string_to_upper(std::string s)
{
    std::transform(s.cbegin(), s.cend(), s.begin(), toupper);
    return s;
}

template <class T, class E>
T get_or_throw(const tl::expected<T, E>& exp)
{
    if (!exp) {
        throw exp.error();
    } else {
        return exp.value();
    }
}

template <class T>
T get_or_throw(const tl::expected<T, std::exception_ptr>& exp)
{
    if (!exp) {
        std::rethrow_exception(exp.error());
    } else {
        return exp.value();
    }
}

template <class F>
auto expected_try(F f) ->
    tl::expected<decltype(std::invoke(f)), std::exception_ptr>
{
    try {
        return std::invoke(f);
    } catch (...) {
        return tl::unexpected(std::current_exception());
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2) std::terminate();

    auto uid = atoi(argv[1]);
    auto username = username_for_id(uid);
    if (username) {
        std::cout << *username << std::endl;
    } else {
        std::cout << username.error() << std::endl;
    }

    auto username_upper = transform(username, string_to_upper);
    if (username_upper) {
        std::cout << *username_upper << std::endl;
    } else {
        std::cout << username.error() << std::endl;
    }

    auto wrapped = expected_try([&] {
        auto real_username = get_or_throw(username);
        std::cout << real_username << std::endl;
        return 42;
    });

    if (wrapped) {
        std::cout << *wrapped << std::endl;
    } else {
        std::cout << "ISPALJEN JE IZUZETAK!" << std::endl;
        //auto fun = get_or_throw(wrapped);
    }

    return 0;
}
