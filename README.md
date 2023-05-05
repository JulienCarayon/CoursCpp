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
Here a snapshot of the receiver :
 ![Capture d’écran du 2023-05-05 10-15-13](https://user-images.githubusercontent.com/78759372/236409166-89ac835a-8cd0-4f82-a9fd-de4b644c637d.png)

```
cd TP_MQTT/message_sender/build
./MQTT-Sender
```
Here a snapshot of the message sender :
![Capture d’écran du 2023-05-05 10-16-03](https://user-images.githubusercontent.com/78759372/236409375-72fa8f58-ed06-4295-8425-a54beeb3edef.png)

WHat it looks like on another MQTT client :
 <img width="927" alt="image" src="https://user-images.githubusercontent.com/78759372/236409496-55e30d8d-2d59-401d-bcb9-e348fa2364f8.png">


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

