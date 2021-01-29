add_compile_definitions(USE_DEBUG) # uncomment this for debugging
#set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_EXTENSIONS OFF)
#set(gtest_disable_pthreads OFF)
FILE(GLOB Sources ../src/CTA2045Translator.cpp ../src/DCMImpl.cpp ../src/UCMImpl.cpp)
add_executable(all-tests main.cpp ${Sources} CTA2045TranslatorTest.cpp)
target_link_libraries(all-tests gtest gmock gtest_main cea2045 )
add_test(all-tests all-tests)