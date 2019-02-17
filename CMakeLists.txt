cmake_minimum_required(VERSION 3.0)

project(MafClub)

# Configure required libraries ...
if(UNIX) # Darwing or Linux

	find_package(Boost REQUIRED COMPONENTS system thread log program_options chrono)
	find_package(Threads REQUIRED)

	find_package(OpenSSL 1.0.1 REQUIRED)
	set(OPENSSL_VERSION "1.0.1")

elseif(WIN32) # Windows systems including Win64.
	message(FATAL_ERROR "-- Windows is not supported for now.")
else()
	message(FATAL_ERROR "-- Unsupported platform sorry! :( ")
endif()

# Configure compiler options ...
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")

    message("-- configuring clang options")
    set(CMAKE_CXX_FLAGS "-arch x86_64 -std=c++11 -stdlib=libc++ -DBOOST_LOG_DYN_LINK -Wno-deprecated-declarations")

elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")

    message("-- configuring gcc options")

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -DBOOST_LOG_DYN_LINK")

endif()

# Project construction ...

# source files ...
add_executable("external"		./external/source/main.cpp
				./external/source/microsvc_controller.cpp
				./external/source/foundation/network_utils.cpp
				./external/source/foundation/basic_controller.cpp)

add_executable("router" 		./services/src/router/main.cpp
				./services/src/router/router.cpp
				./external/source/foundation/network_utils.cpp
				./external/source/foundation/basic_controller.cpp)

# headers search paths ...
set(CPPRESTSDK_INCLUDE_DIR "./external/include")
set(EXTERNAL_INCLUDE_DIR "./external/source/foundation/include")
set(SERVICES_INCLUDE_DIR "./services/include")
message(EXTERNAL " ${EXTERNAL_INCLUDE_DIR}")
message(SERVICES " ${SERVICES_INCLUDE_DIR}")
set(HEADER_SEARCH_PATHS ${CPPRESTSDK_INCLUDE_DIR} ${EXTERNAL_INCLUDE_DIR} ${SERVICES_INCLUDE_DIR} ${Boost_INCLUDE_DIR} ${OPENSSL_INCLUDE_DIR})

# library search paths ...
set(OPENSSL_LIBS "${OPENSSL_LIBRARIES}")
set(CPPRESTSDK_LIBRARY "${PROJECT_SOURCE_DIR}/external/lib/libcpprest.a")

set(LIBRARIES_SEARCH_PATHS ${CPPRESTSDK_LIBRARY} ${OPENSSL_LIBS} ${Boost_LIBRARIES})

message(BOOST_LIBS " ${Boost_LIBRARIES}")
message(OPENSSL_LIBS " ${OPENSSL_LIBRARIES}")
message(CPPRESTSDK_LIBRARY " ${CPPRESTSDK_LIBRARY}")
message(LIBRARIES_SEARCH_PATHS " ${LIBRARIES_SEARCH_PATHS}")

include_directories(${HEADER_SEARCH_PATHS})

target_link_libraries("external" ${LIBRARIES_SEARCH_PATHS})

target_link_libraries("router" ${LIBRARIES_SEARCH_PATHS})
