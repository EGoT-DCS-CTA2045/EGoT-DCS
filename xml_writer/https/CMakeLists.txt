set(COMPONENT_NAME https)

add_library(${COMPONENT_NAME} STATIC
  https_client.cpp
)

target_link_libraries(${COMPONENT_NAME} PUBLIC 
  Boost::boost
  OpenSSL::SSL
  pthread
)

target_include_directories(${COMPONENT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
  ${Boost_INCLUDE_DIRS}
  ${OpenSSL_INCLUDE_DIRS}
)