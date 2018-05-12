/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   port_reader.h
 * Author: makar
 *
 * Created on May 11, 2018, 5:46 PM
 */

#ifndef PORT_READER_H
#define PORT_READER_H
#include <vector>
#include <stdexcept>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>

inline std::vector <char> port_reader(int sockfd, sockaddr* client_addr) 
{
    socklen_t len;
    std::vector<char> buf;
    while (true) {
        char t;
        if (recvfrom(sockfd, &t, 1, 0, client_addr, &len) != 1)
            throw std::runtime_error("can not read socket");
        std::cout << "." << t << std::endl;
        buf.push_back(t);
        if (t == ';')
            break;
    }
    return buf;
}

#endif /* PORT_READER_H */

