cmake_minimum_required(VERSION 3.0)

project(MafClub)

# Configure required libraries ...
if(UNIX) # Darwing or Linux

	find_package(Boost REQUIRED COMPONENTS system thread log program_options chrono)
	find_package(Threads REQUIRED)
	find_package(libmongocxx REQUIRED)
	find_package(libbsoncxx REQUIRED)
	find_package(OpenSSL 1.0.1 REQUIRED)
	find_package(cpprestsdk REQUIRED)
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

add_executable("router" 		./services/src/router/main.cpp
	./services/src/router/router.cpp
	./external/source/foundation/network_utils.cpp
	./external/source/foundation/basic_controller.cpp)

add_executable("dbservice" 		./services/src/dbservice/main.cpp
	./services/src/dbservice/dbservice.cpp
	./external/source/foundation/network_utils.cpp
	./external/source/foundation/basic_controller.cpp)

add_executable("account" 		./services/src/account/main.cpp
	./services/src/account/account.cpp
	./external/source/foundation/network_utils.cpp
	./external/source/foundation/basic_controller.cpp)

add_executable("messaging" 		
	./services/src/messaging/main.cpp
	./services/src/messaging/messaging.cpp
	./external/source/foundation/network_utils.cpp
	./external/source/foundation/basic_controller.cpp
	)


# headers search paths ...
set(EXTERNAL_INCLUDE_DIR "./external/source/foundation/include")
set(SERVICES_INCLUDE_DIR "./services/include")
find_path(CPPRESTSDK_INCLUDE_DIR cpprest)
set(HEADER_SEARCH_PATHS ${CPPRESTSDK_INCLUDE_DIR} ${EXTERNAL_INCLUDE_DIR} ${SERVICES_INCLUDE_DIR} ${LIBMONGOCXX_INCLUDE_DIRS} ${Boost_INCLUDE_DIR} ${OPENSSL_INCLUDE_DIR})
message(bson ${LIBMONGOCXX_INCLUDE_DIRS})

# library search paths ...
find_library(CPPRESTSDK_LIBRARY cpprest)
set(OPENSSL_LIBS "${OPENSSL_LIBRARIES}")

set(LIBRARIES_SEARCH_PATHS ${CPPRESTSDK_LIBRARY} ${OPENSSL_LIBS} ${Boost_LIBRARIES} ${LIBMONGOCXX_LIBRARIES} ${LIBBSONCXX_LIBRARIES})

message(LIBRARIES_SEARCH_PATHS " ${LIBRARIES_SEARCH_PATHS}")

message(HEADER_SEARCH_PATHS " ${HEADER_SEARCH_PATHS}")

include_directories(${HEADER_SEARCH_PATHS})

target_link_libraries("router" ${LIBRARIES_SEARCH_PATHS})

target_link_libraries("dbservice" ${LIBRARIES_SEARCH_PATHS})

target_link_libraries("account" ${LIBRARIES_SEARCH_PATHS})

target_link_libraries("messaging" ${LIBRARIES_SEARCH_PATHS})
