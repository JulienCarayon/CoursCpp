sudo rm -rf

sudo apt install qtbase5-private-dev

git clone git@github.com:qt/qtmqtt.git

cd qtmqtt/

git checkout 5.15.2

sudo qmake

sudo make

sudo make install