sudo apt install doxygen graphviz libssl-dev build-essential gcc make cmake cmake-gui cmake-curses-gui

git submodule init
git submodule update --init --recursive
cd Base/src/app/lib/paho.mqtt.cpp/
eval "./install_paho_mqtt_c.sh"
cmake -Bbuild -H. -DPAHO_BUILD_STATIC=ON \
    -DPAHO_BUILD_DOCUMENTATION=TRUE -DPAHO_BUILD_SAMPLES=TRUE
cmake --build build/ --target install
cmake -Bbuild -H. -DPAHO_WITH_SSL=ON -DPAHO_ENABLE_TESTING=OFF -DPAHO_BUILD_DEB_PACKAGE=ON
cmake --build build
sudo ldconfig
