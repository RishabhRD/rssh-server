#include "Stream.h"
#include <uv.h>
class ServerSocket {
  uv_tcp_t server;
  int listeningPort;
  struct sockaddr_in selfAddress;
  uv_loop_t *eventLoop;
  int maxConnections;

public:
  ServerSocket(int port, int maxConnections = 128);
  Stream listen(void connectionCallback(const Stream &stream));

private:
  void on_new_connection(uv_stream_t *server, int status);
  static uv_buf_t alloc_buffer(uv_handle_t *handle, size_t suggested_size);
  uv_read_cb cb;
  static void echo_read(uv_stream_t *client, size_t nread, uv_buf_t* buf);
};
