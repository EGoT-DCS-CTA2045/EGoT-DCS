add_executable(app DCM.cpp DCMImpl.cpp CTA2045Translator.cpp UCMImpl.cpp)
add_definitions(-lwiringPi)
find_library(WIRINGPI_LIBRARIES NAMES wiringPi)

target_link_libraries(app LINK_PUBLIC ${WIRINGPI_LIBRARIES} cea2045 Boost::boost pthread)
target_include_directories(app PUBLIC 
	${cea2045_SOURCE_DIR}/cea2045
	${Boost_INCLUDE_DIRS} 
	${SEP_INCLUDE_DIRS})	
