Since there is no computer with Linux environment at hand.
I use "DEV C++" of "Windows OS" to compile and complete this project.

Server:

It can listen to UDP messages on specific IP and port and reply a same message back to the client.
I set the port to "4567" and IP to "127.0.0.1".
You can modify the "SERVER_PORT" to modify the port.
IP is also the same can be modified.

Client:

It can send a UDP message to your server and display the echo message. (message, IP and port are configurable).
The message is based on what you input at the time.
Exit code is 0.
I set the port to "4567" and IP to "127.0.0.1".
You can modify the "SERVER_PORT" to modify the port.
IP is also the same can be modified.

It support max-retry option.
I set "max-retry" to 10 and the client will resend message at most 10 times.
Each interval is 0.5 second.
Exit code is 1 if reach max-retry.
You can modify "max-retry" to modify the max times of retries.
