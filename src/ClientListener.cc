#include "ClientListener.h"

ClientListener::ClientListener(asio::io_context &context, Server::ptr server)
    : context(context), acceptor(context, tcp::endpoint(tcp::v4(), 0)),
      server(server) {}
