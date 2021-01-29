add_compile_definitions(USE_DEBUG) # uncomment this for debugging
add_executable(app DCM.cpp DCMImpl.cpp CTA2045Translator.cpp UCMImpl.cpp)
target_link_libraries(app LINK_PUBLIC cea2045 Boost::boost IEEE2030-5 pthread)
target_include_directories(app PUBLIC 
	${cta2045_SOURCE_DIR}
	${Boost_INCLUDE_DIRS} 
	${IEEE2030-5_INCLUDE_DIRS})	
