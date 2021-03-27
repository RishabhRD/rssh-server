#include <uvw.hpp>
#include <functional>
#include "ServerSocket.h"
#include <stdlib.h>

ServerSocket::ServerSocket(int port, int maxConnections)
    : maxConnections(maxConnections), listeningPort(port) {
  struct sockaddr_in addr;
  struct sockaddr *rawAddress = reinterpret_cast<struct sockaddr *>(&addr);
  eventLoop = uv_default_loop();
  uv_ip4_addr("127.0.0.1", listeningPort, &addr);
  uv_tcp_init(eventLoop, &server);
  uv_tcp_bind(&server, rawAddress, 0);
}

Stream ServerSocket::listen(void connectionCallback(const Stream &stream)) {
  uv_tcp_t *client = (uv_tcp_t *)malloc(sizeof(uv_tcp_t));
  uv_tcp_init(eventLoop, client);
}

void ServerSocket::on_new_connection(uv_stream_t *server, int status) {
  if (status == -1) {
    return;
  }
  const auto f = [this](uv_stream_t *client, ssize_t nread, uv_buf_t buf){
    this->echo_read(client, nread, buf);
  };

  uv_tcp_t *client = (uv_tcp_t *)malloc(sizeof(uv_tcp_t));
  uv_tcp_init(eventLoop, client);
  if (uv_accept(server, (uv_stream_t *)client) == 0) {
    uv_read_start((uv_stream_t *)client, this->alloc_buffer, echo_read);
  } else {
    uv_close((uv_handle_t *)client, NULL);
  }
}

uv_buf_t ServerSocket::alloc_buffer(uv_handle_t *handle,
                                    size_t suggested_size) {
  return uv_buf_init((char *)malloc(suggested_size), suggested_size);
}

void ServerSocket::echo_read(uv_stream_t *client, size_t nread, uv_buf_t* buf) {
  if (nread == -1) {
    fprintf(stderr, "Read error!\n");
    uv_close((uv_handle_t *)client, NULL);
    return;
  }

  uv_write_t *write_req = (uv_write_t *)malloc(sizeof(uv_write_t));
  write_req->data = (void *)buf->base;
  buf->len = nread;
}
