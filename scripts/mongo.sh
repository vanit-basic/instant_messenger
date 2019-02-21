#!/bin/bash

NEW_UUID=$(cat /dev/urandom | tr -dc 'a-zA-Z0-9' | fold -w 6 | head -n 1)

work_dir=/tmp/mongo_$NEW_UUID

checkStatus(){
	status=$?
	if [ $status != 0 ]; then
		echo STATUS : $status
		exit
	fi
}

mongoc() {
	wget https://github.com/mongodb/mongo-c-driver/releases/download/1.13.1/mongo-c-driver-1.13.1.tar.gz

	tar xzf mongo-c-driver-1.13.1.tar.gz

	cd mongo-c-driver-1.13.1

	mkdir cmake-build

	cd cmake-build

	cmake -DENABLE_AUTOMATIC_INIT_AND_CLEANUP=OFF -DCMAKE_BUILD_TYPE=Release .. || checkStatus

	make && sudo make install
}

mongocxx () {
	mkdir mongocxx && cd mongocxx

	git clone https://github.com/mongodb/mongo-cxx-driver.git \
		--branch releases/stable --depth 1

	cd mongo-cxx-driver/build

	cmake -DCMAKE_BUILD_TYPE=Release -DBSONCXX_POLY_USE_MNMLSTC=1 -DCMAKE_INSTALL_PREFIX=/usr/local .. || checkStatus

	sudo make EP_mnmlstc_core || checkStatus

	make && sudo make install
}

build() {
	cd $work_dir
	name=$1
	echo $name $PWD
	rm -rf $name
	mkdir $name
	cd $name
	$name
	cd $work_dir
	sudo rm -rf $name
}

build_all() {
	sudo ls > /dev/zero || checkStatus
	mkdir -p $work_dir
	build "mongoc"
	build "mongocxx"
	rm -rf $work_dir
}

build_all
