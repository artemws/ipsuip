cmake_minimum_required(VERSION 3.20)

project(ipsuip VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_STATIC "Link everything statically (Linux musl)" OFF)

if(BUILD_STATIC AND UNIX AND NOT APPLE)
    set(OPENSSL_USE_STATIC_LIBS ON)
    set(Boost_USE_STATIC_LIBS ON)
    # musl-gcc или обычный gcc со статическими либами
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
endif()

find_package(OpenSSL REQUIRED)

# boost_system стал header-only начиная с Boost 1.75 — не запрашиваем его
find_package(Boost REQUIRED COMPONENTS regex)

set(IPSUIP_BOOST_INCLUDE_DIRS ${Boost_INCLUDE_DIRS})
set(IPSUIP_BOOST_LIBRARIES    Boost::regex)
set(IPSUIP_OPENSSL_LIBRARIES  OpenSSL::SSL OpenSSL::Crypto)

add_subdirectory(src)
