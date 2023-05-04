rm -rf build
mkdir build
git submodule init
git submodule update --init --recursive
cd inc/paho.mqtt.cpp/
eval "./install_paho_mqtt_c.sh"
cd ../../build
cmake ..
make