# CoursCpp

In these lessons, we had to do a few project : 
`TP_MQTT/displayer` and `TP_MQTT/message sender` are two MQTT client:


  `TP_MQTT/displayer` : Callback based topic watcher : It prints the messages from the topic in the terminal output. \
  `TP_MQTT/message_sender` : Sends a beautiful message in a topic.
  `TP_Steganography` : Python script that hide a message in a PNG image and a QT C++ project and/or a python script to reveal the message 
 
## TP_MQTT
### How to build
Each individual project can be build independently by following these commands:
  ```
  cd TP_MQTT/displayer
  chmod +x build.sh
  ./build.sh
  ```

  ```
  cd TP_MQTT/message_sender
  chmod +x build.sh
  ./build.sh
  ```

## How to run
To run these you need by following these commands:
```
cd TP_MQTT/displayer/build
./MQTT-Receiver
```

```
cd TP_MQTT/message_sender/build
./MQTT-Sender
```
## TP_Steganography`
  run `pip install -r requirements.txt` to install python dependencies.
  Then you can run these commands to run the encrypt script : 
  ```
  cd TP_Steganography/Encrypt_python
  python3 encrypt_png.py
  ```
  
  To run the python decrypt script :
  ```
  cd TP_Steganography/Decrypt_python
  python3 decrypt_png.py
  ```
  If you want to run the C++ script, use Qt to run the project

