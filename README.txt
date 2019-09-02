Instructions for EE542 Lab Assignment 1

To compile use the two commands below, (to compile udp code replace tcp with udp)

    1.) gcc -g -o server_tcp server_tcp.c
    2.) gcc -g -o client_tcp client_tcp.c

To execute

    1.) Start the server using the following command :
        ./server_tcp 5648 (Any port number from 2000 to 65535 works)
    2.) Start the client using the following command :
        ./client_tcp 192.168.0.0 5648 (Same port number as above) (Where 192.168.0.0 is the host ip address)
    3.) You will get a prompt with the following message in the client side if the port number and hostname are correct, enter the message that needs to be sent to the server :
        Please enter the message: hello
    4.) The server receives the message and displays the following message :
        Here is the message: hello
    5.)The client will show the following message once the server receives the message :
        I got your message