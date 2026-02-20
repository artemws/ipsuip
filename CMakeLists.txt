cmake_minimum_required(VERSION 3.20)

project(ipsuip VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ── Статическая сборка на Linux ───────────────────────────────────────────────
# Передаётся из CI через -DBUILD_STATIC=ON
option(BUILD_STATIC "Link everything statically" OFF)

if(BUILD_STATIC AND UNIX AND NOT APPLE)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++")
    set(OPENSSL_USE_STATIC_LIBS ON)
    set(Boost_USE_STATIC_LIBS ON)
endif()

# ── Поиск зависимостей ────────────────────────────────────────────────────────
find_package(OpenSSL REQUIRED)
find_package(Boost REQUIRED COMPONENTS regex system)

# Делаем Boost и OpenSSL доступными для всех поддиректорий
set(IPSUIP_BOOST_INCLUDE_DIRS ${Boost_INCLUDE_DIRS})
set(IPSUIP_BOOST_LIBRARIES    Boost::regex Boost::system)
set(IPSUIP_OPENSSL_LIBRARIES  OpenSSL::SSL OpenSSL::Crypto)

add_subdirectory(src)
