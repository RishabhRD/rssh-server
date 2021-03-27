#include "ServerRegistrar.h"

ServerRegistrar::ServerRegistrar(int port) : listeningPort(port){
  struct sockaddr_in addr;
  struct sockaddr* rawAddress = reinterpret_cast<struct sockaddr*>(&addr);
  uv_ip4_addr("127.0.0.1", port, &addr);
  eventLoop = uv_default_loop();
  uv_tcp_init(eventLoop, &server);
  uv_tcp_bind(&server, rawAddress, 0);

}
