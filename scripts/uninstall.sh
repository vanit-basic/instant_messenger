#!/bin/bash

uninstall_mongo() {
	echo "Uninstalling mongoc and bson ..."
	/usr/local/share/mongo-c-driver/uninstall.sh

	echo "Uninstalling mongocxx and bsoncxx ..."

	rm -rf /usr/local/include/bsoncxx
	rm -rf /usr/local/include/mongocxx
	rm -rf /usr/local/lib/cmake/libbsoncxx-3.4.0
	rm -rf /usr/local/lib/cmake/libmongocxx-3.4.0
	rm -rf /usr/local/lib/libbsoncxx.so
	rm -rf /usr/local/lib/libbsoncxx.so.3.4.0
	rm -rf /usr/local/lib/libbsoncxx.so._noabi
	rm -rf /usr/local/lib/libmongocxx.so
	rm -rf /usr/local/lib/libmongocxx.so.3.4.0
	rm -rf /usr/local/lib/libmongocxx.so._noabi
	rm -rf /usr/local/lib/pkgconfig/libbsoncxx.pc
	rm -rf /usr/local/lib/pkgconfig/libmongocxx.pc
}

uninstall_standard () {
	packages="libcpprest-dev libcpprest2.10 cmake libssl-dev libsasl2-dev"
	apt remove $packages
}

uninstall_mongo
uninstall_standard
