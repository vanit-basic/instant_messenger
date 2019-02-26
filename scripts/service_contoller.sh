#!/bin/bash

POSITIONAL=()
while [[ $# -gt 0 ]]
do
key="$1"

case $key in
    -c|--config)
    CONFIG_FILE="$2"
    shift # past argument
    shift # past value
    ;;
    -s|--services)
    SERVICES_DIR="$2"
    shift # past argument
    shift # past value
    ;;
    -a|--action)
    ACTION="$2"
    shift # past argument
    shift # past value
    ;;
    -n|--name)
    SERVICE_NAME="$2"
    shift # past argument
    shift # past value
    ;;
    --default)
    DEFAULT=YES
    shift # past argument
    ;;
    *)    # unknown option
    POSITIONAL+=("$1") # save it in an array for later
    shift # past argument
    ;;
esac
done
set -- "${POSITIONAL[@]}" # restore positional parameters

echo DEFAULT     = "${DEFAULT}"
echo CONFIG FILE = "${CONFIG_FILE}"
echo ACTION      = "${ACTION}"
echo SERVICE NAME= "${SERVICE_NAME}"
echo SERVICES DIR= "${SERVICES_DIR}"

COMMAND=`basename $0`

if [[ !($CONFIG_FILE && $ACTION && $SERVICE_NAME && $SERVICES_DIR) ]]; then
    echo "Usage : $COMMAND -n <router|account|game|messaging|search|tokendb|dbservice> -c <config file path> -s <services directory> -a <start|stop|restart>"
    exit 4
fi

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
		./$SERVICES_DIR/$SERVICE_NAME $CONFIG_FILE
		S_PID=$!
		echo "Started with $S_PID PID"
	else
		echo "Already running"
	fi
}

stop_service () {
	name=$1
	pid=`pidof $name`
	if [ "$pid" != "" ]; then
		kill -9 $pid
	fi
}

restart_service () {
	stop_service $1
	start_service $1
}

execute=""$ACTION"_service $SERVICE_NAME"
`$execute`
