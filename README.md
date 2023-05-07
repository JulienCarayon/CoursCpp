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

## UCAV project 
![image](https://user-images.githubusercontent.com/79545759/236670369-12b425da-55fd-44cc-886f-c0d655f3d655.png)

### Configure project 
![image](https://user-images.githubusercontent.com/79545759/236670296-cd145991-2915-47fe-b007-436d81003e7c.png)

### Drone console
![image](https://user-images.githubusercontent.com/79545759/236670352-cbf74f41-2a97-4d3b-bc5b-b38db9bbe8d6.png)

### Base UI

#### Configure MQTT
You can configure the following different elements :
- Broker Adress
- Topic
- Client ID
- QoS

After configuration click on "Connect"

![image](https://user-images.githubusercontent.com/79545759/236670483-3a1716be-11ee-408a-bd88-c2f9db73fb6c.png)

#### Base connect 
This is what the interface looks like when connected.

If you want to disconnect, click on "Disconnect"
![image](https://user-images.githubusercontent.com/79545759/236670544-e8ec5842-362f-4830-8ad3-1f04c6ed9be1.png)

#### Base receives the image

When receiving the message :
- Display of data received (format : JSON)
- Receonstruction of the image with JSON data
- decoded message in image

![image](https://user-images.githubusercontent.com/79545759/236670561-b895cf8d-4929-4eb9-b140-548fd2eb0a2d.png)



