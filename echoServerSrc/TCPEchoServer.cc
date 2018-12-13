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
#include "checkArgs.h"
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
	/*while ((recvMsgSize = sock->recv(echoBuffer, RCVBUFSIZE)) > 0) { // Zero means
	                                                 // end of transmission
		// Echo message back to client
//		sock->send(echoBuffer, recvMsgSize);
		
		
	
	/*std::string var1;
	std::string var2;
		sock->send("Pichulina\n\r", 32);
		sock->send("Pichulina2323", 32);}*/
	//std::cos = sock->recv(echoBuffer[32]);	
	recvMsgSize = sock->recv(echoBuffer, RCVBUFSIZE);
	std::cout << echoBuffer; 
	sock->send("HTTP/1.1 200 OK\r\n",32);
	sock->send("Content-Type: text/html\r\n\r\n",32);
	std::string var1;
	std::string var2="";
	//std::string var3;
	std::string var3(echoBuffer,5,12);
	std::cout << var3+"\n\r";
	std::ifstream caca("www-data/prueba2.html");
	if(caca.is_open()){
		std::cout<<"entro\n\r";
		while(getline(caca,var1)){
			var2 = var2 + var1 + "\n";
		}
		caca.close();
	}
	else{
		std::cout <<" no se abrio html\r\n";			
	}
	sock->send(var2.c_str(),var2.length());
	delete sock;
}

int main(int argc, char *argv[]) {
	
	checkArgs* argumentos = new checkArgs(argc, argv);
	
	uint16_t echoServPort;   
	echoServPort  = argumentos->getArgs().PORT;
	
	try {
		TCPServerSocket servSock(echoServPort);     // Server Socket object

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
