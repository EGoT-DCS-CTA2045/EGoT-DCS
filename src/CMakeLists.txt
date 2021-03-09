add_executable(app DCM.cpp DCMImpl.cpp CTA2045Translator.cpp UCMImpl.cpp sample2_main.cpp)
target_link_libraries(app LINK_PUBLIC cea2045 Boost::boost pthread)
target_include_directories(app PUBLIC 
	${cea2045_SOURCE_DIR}/cea2045
	${Boost_INCLUDE_DIRS} 
	${SEP_INCLUDE_DIRS})	
