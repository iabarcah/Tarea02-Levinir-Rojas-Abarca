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
	
	std::ifstream arch1("www-data/prueba2.html");
	std::ifstream arch2("www-data/prueba1.html");
	std::ifstream arch3("www-data/prueba3.html");
	std::ifstream arch4("www-error/error404.html");
	if(var3 == "prueba2.html"){
	if(arch2.is_open()){
		std::cout<<"entro\n\r";
		while(getline(arch1,var1)){
			var2 = var2 + var1 + "\n";
		}
		arch1.close();
	}
	else{
		std::cout <<" no se abrio html\r\n";			
	}
	sock->send(var2.c_str(),var2.length());
	}
	else if(var3 == "prueba1.html"){
	if(arch2.is_open()){
		std::cout<<"entro\n\r";
		while(getline(arch2,var1)){
			var2 = var2 + var1 + "\n";
		}
		arch2.close();
		
	}
	else{
		std::cout <<" no se abrio html\r\n";			
	}
	sock->send(var2.c_str(),var2.length());
	}
	else if(var3 == "prueba3.html"){
	if(arch3.is_open()){
		std::cout<<"entro\n\r";
		while(getline(arch3,var1)){
			var2 = var2 + var1 + "\n";
		}
		arch3.close();
		
	}
	else{
		std::cout <<" no se abrio html\r\n";			
	}
	sock->send(var2.c_str(),var2.length());
	}
	else{
	if(arch4.is_open()){
		std::cout<<"entro\n\r";
		while(getline(arch4,var1)){
			var2 = var2 + var1 + "\n";
		}
		arch4.close();
	}
	else{
		std::cout <<" no se abrio html\r\n";			
	}
	sock->send(var2.c_str(),var2.length());
	}
	delete sock;
}

int main(int argc, char *argv[]) {
	//json config = new json();
	checkArgs* argumentos = new checkArgs(argc, argv);
	//config* cosa = new config(argc,argv);
	uint16_t echoServPort;   
	echoServPort  = argumentos->getArgs().PORT;
	//echoServPort = cosa->puerto;
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
