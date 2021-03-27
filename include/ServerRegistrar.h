#include <uv.h>
class ServerRegistrar{
  uv_loop_t* eventLoop;
  uv_tcp_t server;
  int listeningPort;
  int maxConnections;
  public:
  ServerRegistrar(int port);
};
