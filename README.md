# instant_messenger
Instant messenger

## How to build


	$ ./scripts/install_dependencies.sh
	$ mkdir build
	$ cd build
	$ CMAKE_PREFIX_PATH=$CMAKE_PREFIX_PATH:/usr/lib/x86_64-linux-gnu/cmake
	$ cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug ..
	$ make




