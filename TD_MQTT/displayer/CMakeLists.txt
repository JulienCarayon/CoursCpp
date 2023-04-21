cmake_minimum_required(VERSION 3.8)

project(MQTT-Receiver)

# Ajouter le répertoire inc/mqtt à la liste des chemins d'inclusion
add_subdirectory(inc/paho.mqtt.cpp)
# include(inc/paho.mqtt.c/CMakeLists.txt)
# PAHO_CPP_LIB="./inc/paho.mqtt.cpp/CMakeLists.txt"

# include(./inc/paho.mqtt.cpp/CMakeLists.txt)


set(CMAKE_CXX_STANDARD 17)

# add_library(mqtt_lib STATIC inc/paho.mqtt.cpp/src/mqtt/client.h inc/paho.mqtt.cpp/src/client.cpp)
# Ajouter tous les fichiers sources de projet/src au projet
file(GLOB_RECURSE SOURCES "src/*.cpp")

# add_subdirectory(./inc/paho.mqtt.cpp)

# Créer l'exécutable à partir des fichiers sources
add_executable(MQTT-Receiver ${SOURCES})
# target_link_libraries(MQTT-Receiver PUBLIC ./inc/paho.mqtt.cpp/CMakeLists.txt)

target_link_libraries(MQTT-Receiver PRIVATE paho-mqttpp3)

# Définir une dépendance entre la cible mon_programme et la bibliothèque paho-mqttpp3
add_dependencies(MQTT-Receiver paho-mqttpp3)

# add_dependencies(MQTT-Reveiver mqtt_lib)


