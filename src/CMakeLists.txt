set(SOURCES main.cpp)

# set(Boost_USE_STATIC_LIBS ON) # only find static libs set(Boost_USE_DEBUG_LIBS
# ON) # ignore debug libs and set(Boost_USE_RELEASE_LIBS OFF) # only find
# release libs set(Boost_USE_MULTITHREADED ON) set(Boost_USE_STATIC_RUNTIME ON)
# find_package( Boost COMPONENTS # thread REQUIRED)

add_subdirectory(choose_your_fate)
add_subdirectory(functions)
add_subdirectory(http_client)
add_subdirectory(parallel_parsing)
add_subdirectory(timer)

add_executable(ipsuip ${SOURCES} ${HEADERS})
target_link_libraries(ipsuip PRIVATE choose_your_fate -lpthread -lm -static-libgcc -static-libstdc++)

# target_link_libraries(ipsuip PRIVATE ${Boost_LIBRARIES} )
message("Boost_libraries: ${Boost_LIBRARIES}")
message("Openssl_libraries: ${OPENSSL_LIBRARIES}")
