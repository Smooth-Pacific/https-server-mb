#ifndef TEST_SUITE_HEADER
#define TEST_SUITE_HEADER

#define TEST(X) std::cout << "Testing: " << #X << std::endl; \
                if (X() == true) {                           \
                    passed++;                                \
                    std::cout << "Test passed.\n\n";         \
                } else {                                     \
                    failed++;                                \
                    std::cerr << "Test failed.\n\n";         \
                }

#endif // TEST_SUITE_HEADER
