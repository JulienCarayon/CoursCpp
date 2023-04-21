rm -rf build
mkdir build
git submodule init
git submodule update --init --recursive
eval "./inc/paho.mqtt.cpp/install_paho_mqtt_c.sh"
cd build
cmake ..
make