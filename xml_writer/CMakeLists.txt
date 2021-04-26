add_subdirectory(https)
set(COMPONENT_NAME dcm)
add_executable(announcer main.cpp announce_xml.cpp abstract_command.cpp) 
target_link_libraries(app LINK_PUBLIC https cea2045 Boost::boost OpenSSL::SSL pthread)
target_include_directories(announcer PUBLIC
        ${cea2045_SOURCE_DIR}/cea2045
        ${Boost_INCLUDE_DIRS}
        ${SEP_INCLUDE_DIRS}
        ${https_INCLUDE_DIRS})
