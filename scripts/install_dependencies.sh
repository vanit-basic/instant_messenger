#!/bin/bash

execution_dir=`dirname $0`

find_query="dpkg-query --show --showformat='\${db:Status-Status}'"

pkg_query="pkg-config --exists"

mongo_packages="libbson-1.0 libbsoncxx libmongoc-1.0 libmongocxx"

packages="libcpprest-dev libcpprest2.10 cmake libssl-dev libsasl2-dev libboost-log-dev libboost-program-options-dev"

missing_packages=""

should_install_mongo=0

check_standard_packages() {
	for i in $packages; do 
		installed=`$find_query $i 2> /dev/null`
		if [ "$installed" != "'installed'" ]; then
			echo $i NOT OK
			missing_packages="$missing_packages $i"
		else
			echo $i OK
		fi
	done
}

check_mongo() {
	for i in $mongo_packages; do
		`$pkg_query $i`
		st=$?
		if [ $st != 0 ]; then
			echo $i NOT OK
			should_install_mongo=$(($should_install_mongo + $st))
		else
			echo $i OK
		fi
	done
	echo $should_install_mongo
}

check_all () {
	check_standard_packages
	check_mongo
}

install_missing_packages() {
	if [ "" != "$missing_packages" ]; then
		sudo apt install $missing_packages
	fi

	if [ $should_install_mongo != 0 ]; then
		./$execution_dir/mongo.sh
	fi
}

check_all

install_missing_packages
