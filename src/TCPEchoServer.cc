/*
 *   C++ sockets on Unix and Windows
 *   Copyright (C) 2002
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "YASL.h"      // For Socket, ServerSocket, and SocketException
#include "json.hpp"
#include <iostream>    // For cerr and cout
#include <cstdlib>     // For atoi()
#include <fstream>
#include <string>
const uint32_t RCVBUFSIZE = 1024;    // Size of receive buffer

// TCP client handling function
void HandleTCPClient(TCPSocket *sock) {
	std::cout << "Handling client ";
	try {
		std::cout << sock->getForeignAddress() << ":";
	} catch (SocketException e) {
		std::cerr << "Unable to get foreign address" << std::endl;
	}
	try {
		std::cout << sock->getForeignPort();
	} catch (SocketException e) {
		std::cerr << "Unable to get foreign port" << std::endl;
	}
	std::cout << std::endl;

	// Send received string and receive again until the end of transmission
	char echoBuffer[RCVBUFSIZE];
	uint32_t recvMsgSize;	
	using json = nlohmann::json;
	json j2;
	std::ifstream klo("bin/config.json");
	if(!klo.is_open()){std::cout<<"error";}
	klo >> j2;
	klo.close();	
	recvMsgSize = sock->recv(echoBuffer, RCVBUFSIZE);
	std::cout<<recvMsgSize;
	std::cout << echoBuffer;
	sock->send("HTTP/1.1 200 OK\r\n",32);
	sock->send("Content-Type: text/html\r\n\r\n",32);
	std::string var1;
	std::string var5;
	std::string var6;
	std::string var2;
	//std::string var3;
	std::string var3(echoBuffer,5,12);
	var5.append(j2["rootDir"]);
	var5.append(var3);
	var6.append(j2["notFoundFile"]);
	std::cout << var5;
	std::ifstream arch2(var5);
	std::ifstream arch1(var6);
	if(arch2.is_open()){
		//std::cout<<"entro\n\r";
		while(getline(arch2,var1)){
			std::cout << var1;
			std::cout<<var2;
			var2 = var2 + var1;

		}
		arch2.close();
	}else{
		if(arch1.is_open()){		
		while(getline(arch1,var1)){
		var2 = var2 + var1 ;
		}
		arch1.close();}
		
	}
	sock->send(var2.c_str(),var2.length());
	delete sock;
}

int main(int argc, char *argv[]) {
	using json = nlohmann::json;
	json j;
	std::ifstream klo("bin/config.json");
	if(!klo.is_open()){return false;}
	klo >> j;
	klo.close();
	//json config = new json();
	//checkArgs* argumentos = new checkArgs(argc, argv);
	//config* cosa = new config(argc,argv);
	uint16_t echoServPort;   
	//echoServPort  = argumentos->getArgs().PORT;
	echoServPort = j["puerto"];
	try {
		TCPServerSocket servSock(j["ip"],echoServPort);     // Server Socket object

		for (;;) {   // Run forever
			HandleTCPClient(servSock.accept());       // Wait for a client to connect
		}
	} catch (SocketException &e) {
		std::cerr << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}
	// NOT REACHED

	return EXIT_SUCCESS;
}
