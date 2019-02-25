#!/bin/bash

SERVICE_NAME=$1

CONFIG_FILE=$2

SERVICES_DIR=$3

COMMAND=`basename $0`

if [[ $# -ne 3 ]]; then
    echo "Usage : $COMMAND <service name> <config file path>"
    exit 4
fi

S_PID=0

check_service_name () {
	pid=`pidof $1`
	if [ "$pid" != "" ]; then 
		kill -0 $pid
		echo $?
		return
	fi
	echo -1
}

start_service () {
	running=`check_service_name $1`
	if [[ $running -ne 0 ]]; then
		./$SERVICES_DIR/$SERVICE_NAME $CONFIG_FILE &
		S_PID=$!
		echo "Started with $S_PID PID"
	else
		echo "Already running"
	fi
}

stop_service () {
	echo "Stop"
}

restart_service () {
	echo "Restart"
}


start_service $SERVICE_NAME
