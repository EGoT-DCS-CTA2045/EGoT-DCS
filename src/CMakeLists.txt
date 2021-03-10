if(USE_DEBUG)
    MESSAGE(STATUS "SRC: USING USE_DEBUG flag")
	add_compile_definitions(USE_DEBUG)
endif()
add_executable(app DCM.cpp DCMImpl.cpp CTA2045Translator.cpp UCMImpl.cpp)
target_link_libraries(app LINK_PUBLIC cea2045 Boost::boost pthread)
target_include_directories(app PUBLIC 
	${cea2045_SOURCE_DIR}/cea2045
	${Boost_INCLUDE_DIRS} 
	${SEP_INCLUDE_DIRS})	
