## QWebSockets-grandMA2 interface

## Description

This is an example application on how to connect an app to a grandMA2 via websockets. It is using threads.  
Asked by some people, i built this simple app in a few hours so they can have a start point on building diy apps.  
I have used something like this a few years ago to interface with an arduino. Have some creativity! :)  
This was built as a fast example app, it is NOT optimized.  

## Settings

This was coded using Qt Creator 4.11.0 with core Qt 5.14.0.  
grandMA2 version 3.7, but it should work with all major versions.  
To run this demo as it is, you have to execute it on same machine as grandMA2 onPc.  
grandMA2 onPc basic configuration:
- session on localhost interface (127.0.0.1)
- remotes enabled.
- 1 dimmer channel patched on 1.001

## Code structure

This example has 2 objects: Ws2Client and Controller.  
Ws2Client is the websocket interface with grandMA2. Tasks:
- To start a connection
- To end a connection
- To process grandMA2 received messages
- To send wakeup packets, so the connection does not die
- To send command line packets

Controller is an interface between Main and Ws2Client. It has 2 tasks:
- to start the connection of WsClient
- to update a number and pass it to Ws2Client so the program modifies grandMA2's channel 1 dimmer value.

## Execution

1. Main initializes both objects.
2. Main moves Ws2Client to a new thread
3. Main starts Controller
4. Controller starts Ws2Client websocet connection
5. Controller starts a loop that sends a number every second to Ws2Client
6. Ws2Client started a connection
7. Ws2Client started awake timers 1 and 2.
8. Ws2Client sends a command to grandMA2 each time it receives a number from Controller.
9. Ws2Client closes the connection after 30 secs of activity.

## Annotations

Awake timers were built using grandMA2's built-in HTTP webserver wake packets timming. They would be something like 10 secs for a type of packet and 400ms for another.
