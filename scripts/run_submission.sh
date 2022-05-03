#!/usr/bin/env bash

TARGET_NAME=CST8703Lab0-HelloWorld
SUBFOLDER=HelloWorld

rm -rf ./build
cmake -DCMAKE_INSTALL_PREFIX=${HOME}/.local -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -S. -B./build
cmake --build ./build --target ${TARGET_NAME} -j 4 --

./build/${SUBFOLDER}/${TARGET_NAME} |& tee output.txt &

HELLO_PID=$(pgrep -f ${TARGET_NAME})
ps -F -p ${HELLO_PID} |& tee -a output.txt
read -t 4 -p "Press any key to send TERM signal to PID ${HELLO_PID} ..."
kill -s TERM ${HELLO_PID}
echo "Signalled."
