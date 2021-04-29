

set(COMPONENT_NAME dcm)

add_executable(simple_client_exe simple_client.cpp) 
#re-add https_simple
target_link_libraries(simple_client_exe PUBLIC httplib::httplib cea2045 Boost::boost OpenSSL::SSL pthread)

target_include_directories(simple_client_exe PUBLIC
        ${cea2045_SOURCE_DIR}/cea2045
        ${Boost_INCLUDE_DIRS}
        ${SEP_INCLUDE_DIRS}
        ${https_INCLUDE_DIRS})
