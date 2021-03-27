if(USE_DEBUG)
    MESSAGE(STATUS "TEST: USING USE_DEBUG flag")
	add_compile_definitions(USE_DEBUG) # uncomment this for debugging
endif()
FILE(GLOB Sources ../src/CTA2045Translator.cpp ../src/DCMImpl.cpp ../src/UCMImpl.cpp)
add_executable(all-tests main.cpp ${Sources} CTA2045TranslatorTest.cpp)
target_link_libraries(all-tests gtest gmock gtest_main cea2045 Boost::boost)
add_test(all-tests all-tests)