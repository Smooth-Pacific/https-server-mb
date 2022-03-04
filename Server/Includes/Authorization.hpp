#ifndef AUTHORIZATION_HEADER
#define AUTHORIZATION_HEADER

#include <string>

class Authorization {
private: // Member variables
    const std::string username;
    const std::string password;
private: // Helpers
    std::string LoadUsername();
    std::string LoadPassword();
    void ValidateUsername();
    void ValidatePassword();
public: // Constructors
    Authorization()
        : username(LoadUsername())
        , password(LoadPassword())
    {
        ValidateUsername();
        ValidatePassword();
    }
    ~Authorization()
    {
    }
public: // Constant functions
    const std::string Username() const { return username; }
    const std::string Password() const { return password; }
};

#endif // AUTHORIZATION_HEADER
