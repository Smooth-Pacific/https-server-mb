#ifndef AUTHORIZATION_HEADER
#define AUTHORIZATION_HEADER

#include <string>

class Authorization {
private: // Member variables
    const std::string username;
    const std::string password;
    const std::string opaque;
public: // Constructors
    Authorization()
        : username(LoadUsername())
        , password(LoadPassword())
        , opaque(GenerateOpaque())
    {
        ValidateUsername();
        ValidatePassword();
    }
    ~Authorization()
    {
    }
private: // Helpers
    std::string LoadUsername();
    std::string LoadPassword();
    std::string GenerateOpaque(size_t size = 256);
    void ValidateUsername();
    void ValidatePassword();
public: // Constant functions
    const std::string Username() const { return username; }
    const std::string Password() const { return password; }
    const std::string Opaque()   const { return opaque;   }
};

#endif // AUTHORIZATION_HEADER
