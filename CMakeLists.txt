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

add_executable("router" 		
	./services/src/router/main.cpp
	./services/src/router/router.cpp
	./services/src/base/basic_controller.cpp
	./utilities/network_utils.cpp)

add_executable("executor" 		
	./services/src/executor/main.cpp
	./services/src/executor/executor.cpp
	./services/src/base/basic_controller.cpp
	./utilities/network_utils.cpp)

add_executable("dbservice" 		
	./services/src/dbservice/main.cpp
	./services/src/dbservice/dbservice.cpp
	./services/src/dbservice/mongoDb.cpp
	./services/src/base/basic_controller.cpp
	./utilities/network_utils.cpp)

add_executable("account" 		
	./services/src/account/main.cpp
	./services/src/account/account.cpp
	./services/src/base/basic_controller.cpp
	./utilities/network_utils.cpp)

add_executable("messaging" 		
	./services/src/messaging/main.cpp
	./services/src/messaging/messaging.cpp
	./services/src/base/basic_controller.cpp
	./utilities/network_utils.cpp)

add_executable("notification" 		
	./services/src/notification/main.cpp
	./services/src/notification/monogoDB.cpp
	./services/src/notification/notification.cpp
	./services/src/base/basic_controller.cpp
	./utilities/network_utils.cpp)

add_executable("porc" 		
	./services/src/porc/porc.cpp
	./services/src/base/basic_controller.cpp
	./utilities/network_utils.cpp)


add_executable("tokenDbService" 		
	./services/src/tokenDbService/main.cpp
	./services/src/tokenDbService/tokenDbService.cpp
	./services/src/tokenDbService/mongoTokenDb.cpp
	./services/src/base/basic_controller.cpp
	./utilities/network_utils.cpp)


add_executable("search" 		
	./services/src/search/main.cpp
	./services/src/search/search.cpp
	./services/src/search/mongocash.cpp
	./services/src/base/basic_controller.cpp
	./utilities/network_utils.cpp)

# headers search paths ...
set(SERVICES_INCLUDE_DIR "./services/include")
set(UTILITIES_INCLUDE_DIR "./utilities")
set(EXCEPTIONS_INCLUDE_DIR "exceptions")
find_path(CPPRESTSDK_INCLUDE_DIR cpprest)
set(HEADER_SEARCH_PATHS ${CPPRESTSDK_INCLUDE_DIR} ${SERVICES_INCLUDE_DIR} ${UTILITIES_INCLUDE_DIR} ${EXCEPTIONS_INCLUDE_DIR} ${LIBMONGOCXX_INCLUDE_DIRS} ${Boost_INCLUDE_DIR} ${OPENSSL_INCLUDE_DIR})
message(bson ${LIBMONGOCXX_INCLUDE_DIRS})

# library search paths ...
find_library(CPPRESTSDK_LIBRARY cpprest)
set(OPENSSL_LIBS "${OPENSSL_LIBRARIES}")

set(LIBRARIES_SEARCH_PATHS ${CPPRESTSDK_LIBRARY} ${OPENSSL_LIBS} ${Boost_LIBRARIES} ${LIBMONGOCXX_LIBRARIES} ${LIBBSONCXX_LIBRARIES})

message(LIBRARIES_SEARCH_PATHS " ${LIBRARIES_SEARCH_PATHS}")

message(HEADER_SEARCH_PATHS " ${HEADER_SEARCH_PATHS}")

include_directories(${HEADER_SEARCH_PATHS})

target_link_libraries("router" ${LIBRARIES_SEARCH_PATHS})

target_link_libraries("executor" ${LIBRARIES_SEARCH_PATHS})

target_link_libraries("dbservice" ${LIBRARIES_SEARCH_PATHS})

target_link_libraries("account" ${LIBRARIES_SEARCH_PATHS})

target_link_libraries("messaging" ${LIBRARIES_SEARCH_PATHS})

target_link_libraries("tokenDbService" ${LIBRARIES_SEARCH_PATHS})

target_link_libraries("porc" ${LIBRARIES_SEARCH_PATHS})

target_link_libraries("search" ${LIBRARIES_SEARCH_PATHS})

target_link_libraries("notification" ${LIBRARIES_SEARCH_PATHS})
