#include "InputParser/input_parser.h"
#include <stdexcept>
#include <string>
#include <iostream>
#include "command_line_interface.h"
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h> // read(), write(), close()
#include <strings.h>
#define MAX 80
#define PORT 8080
#define SA struct sockaddr

// This CLI will need to be a TCP stream that can write and read responses to webserver

void CommandLineInterface::run() {
    std::string input;
    InputParser parser;
    while(true) {
        std::getline(std::cin, input);
        try {
            Command command = parser.parseInput(input);
            // do work
            // notify web server to execute command, and also listen for results from web server

            // socket create and verification
            int status, valread, client_fd;
            struct sockaddr_in serv_addr;
            char* hello = "Hello from client";
            char buffer[1024] = { 0 };
            if ((client_fd = socket(AF_INET6, SOCK_STREAM, 0)) < 0) {
                printf("\n Socket creation error \n");
                return -1;
            }

            serv_addr.sin6_family = AF_INET6;
            serv_addr.sin6_addr = in6addr_any;
            serv_addr.sin6_port = htons(PORT);

            if (inet_pton(AF_INET6, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
                printf("\nInvalid address / Address not supported");
                return -1;
            }

            if ((status = connect(client_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) {
                printf("\n Connection Failed \n");
                return -1;
            }

            send(client_fd, hello, strlen(hello), 0);
            printf("Hello message sent\n");
            valread = read(client_fd, buffer, 1024 - 1);
            printf("%s\n", buffer);

            close(client_fd);

            switch (command.restAPI) {
                case (RestAPI::SET):
                    // Send event
                    break;

                case (RestAPI::GET):

                    break;
                case (RestAPI::DELETE):

                    break;

                default:
                    // Invalid
                    break;
            };

        }
        catch (std::runtime_error e) {
            std::cerr << e.what() << '\n';
            continue;
        }
        input.clear();
    }
}
