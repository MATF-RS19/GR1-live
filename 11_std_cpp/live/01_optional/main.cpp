#include <iostream>
#include <optional>
#include <string>
#include <functional>

#include <pwd.h>

std::optional<std::string> username_for_id(uid_t user_id)
{
    auto pw = getpwuid(user_id);
    if (pw) {
        return std::string(pw->pw_name);
    } else {
        return {};
    }
}

class user {
public:
    const std::string& username() const
    {
        return m_username;
    }

    const std::string& info() const
    {
        return m_info;
    }

    const std::string& dir() const
    {
        return m_dir;
    }

    const std::string& shell() const
    {
        return m_shell;
    }


private:
    user(uid_t id,
        std::string username,
        std::string info,
        std::string dir,
        std::string shell)
        : m_id(id)
        , m_username(std::move(username))
        , m_info(std::move(info))
        , m_dir(std::move(dir))
        , m_shell(std::move(shell))
    {}

    friend std::optional<user> user_for_id(uid_t user_id);

    uid_t m_id;
    std::string m_username;
    std::string m_info;
    std::string m_dir;
    std::string m_shell;
};

std::optional<user> user_for_id(uid_t user_id)
{
    auto pw = getpwuid(user_id);
    if (pw) {
        return user(
            user_id,
            std::string(pw->pw_name),
            std::string(pw->pw_gecos),
            std::string(pw->pw_dir),
            std::string(pw->pw_shell)
        );
    } else {
        return {};
    }
}

template <class T, class F>
auto transform(const std::optional<T> &opt, F trafo) ->
    decltype(std::make_optional(std::invoke(trafo, *opt)))
{
    if (opt) {
        return std::make_optional(std::invoke(trafo, *opt));
        //return std::make_optional(trafo(*opt));
    } else {
        return std::nullopt;
        //return {};
    }
}

std::string string_to_upper(std::string s)
{
    std::transform(s.cbegin(), s.cend(), s.begin(), toupper);
    return s;
}

int main(int argc, char *argv[])
{
    if (argc < 2) std::terminate();

    auto uid = atoi(argv[1]);
    auto username = username_for_id(uid);

    if (username) {
        //std::cout << "username: " << *username << std::endl;
        std::cout << "username: " << username.value() << std::endl;
    } else {
        std::cout << "No such user!" << std::endl;
    }
    //std::cout << "username: ";
    //std::cout << (username ? "user: " + *username : "No such user") << std::endl;
    // ------------------------------------------------
    auto user_object = user_for_id(uid);
    auto user_info = transform(user_object, &user::info);
    auto user_info_uppercased = transform(user_info, string_to_upper);
    std::cout << user_info.value_or("No user info") << std::endl;
    std::cout << user_info_uppercased.value_or("NO USER INFO") << std::endl;

    return 0;
}
