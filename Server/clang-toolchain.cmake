# Set standards
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 20)

# Set compilers
set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

# Set compile flags
set(CMAKE_C_FLAGS "-std=c99 -O2 -s -static -Wall -Wextra -Werror -Wpedantic -Wshadow")
set(CMAKE_CXX_FLAGS "-std=c++2a -O2 -g -Wall -Wextra -Werror -Wshadow -Wpedantic -Wconversion")
