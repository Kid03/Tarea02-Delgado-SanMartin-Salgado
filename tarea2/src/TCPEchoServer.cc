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
#include <iostream>    // For cerr and cout
#include <cstdlib>    // For atoi()
#include <fstream>     // For File Stream
#include "json.hpp"
const uint32_t RCVBUFSIZE = 1024;    // Size of receive buffer

// TCP client handling function
void HandleTCPClient(TCPSocket *sock) {
    std::ifstream i("bin/config.json");
    nlohmann::json j;
    i >> j;
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
  
  // Zero means end of transmission
  while ((recvMsgSize = sock->recv(echoBuffer, RCVBUFSIZE)) != 0) {
    // Echo message back to client
    std::cout << echoBuffer;
    break;
  }

  std::string pagina;
  char *token = strtok(echoBuffer, " ");
  for(int i = 0; i < 2; i++){
    if(i == 0){
        token = strtok(NULL," ");
    }
    else{
        pagina = token;
    }
  }
  //AQUI ESTA LA MALDITA PAGINA
  pagina = pagina.substr(1, pagina.length());
  if(pagina == "holamundo.html"){
    pagina="";
    pagina.append(j["root_dir"]);
    pagina.append("holamundo.html");
  }
  else if(pagina == "chaomundo.html"){
    pagina="";
    pagina.append(j["root_dir"]);
    pagina.append("chaomundo.html");
  }
  else if(pagina == "h1.html"){
    pagina="";
    pagina.append(j["root_dir"]);
    pagina.append("h1.html");
  }
  else{
    pagina = j["notFoundFile"];
    //sock->send(lectura.c_str(),lectura.lenght());
  }
  
  std::ifstream archivo(pagina);
  std::string lectura = "";
  std::string a;
  
  try{
  	sock->send("HTTP/1.1 200 ok\r\nContent-Type: text/html\r\n\r\n",44);
  	if(archivo.is_open()){
  		while(getline(archivo,a)){
  			lectura = lectura + a + "\n";
  		}
  		archivo.close();
  	}
    else{
  		std::cerr << "Error en lectura." << std::endl;
  		exit(EXIT_FAILURE);
  	}
  }
  catch (std::ifstream::failure e) {
  	std::cerr << "Error al abrir el archivo." << std::endl;
  	exit(EXIT_FAILURE);
  }
  
  sock->send(lectura.c_str(),lectura.length());
  delete sock;
}

int main(int argc, char *argv[]) {
  if (argc >= 2) {                     // Test for correct number of arguments
    std::cerr << "Usage: " << argv[0] << " [<Server Port>]" << std::endl;
    exit(EXIT_FAILURE);
  }
  uint16_t echoServPort;
  std::ifstream i("bin/config.json");
  nlohmann::json j;
  i >> j;
  if (argc == 1){
    echoServPort = j["puerto"];
  }else {
    echoServPort = atoi(argv[1]);  // First arg: local port
  }

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
