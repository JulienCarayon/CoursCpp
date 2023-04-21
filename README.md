# CoursCpp

In these lessons, we had to do a few project : 
`displayer` and `message sender` are two MQTT client :


  `TP_MQTT/displayer` : Callback based topic watcher : It prints the messages from the topic in the terminal output. \
  `TP_MQTT/message_sender` : Sends a beautiful message in a topic.

## How to build
Each individual project can be build independently by following these commands:
  ```
  cd displayer
  chmod +x build.sh
  ./build.sh
  ```

  ```
  cd message_sender
  chmod +x build.sh
  ./build.sh
  ```

## How to run
To run these you need by following these commands:
```
cd displayer/build
./MQTT-Receiver
```

```
cd message_sender/build
./MQTT-Sender
```
