#include <asio.hpp>
#include "defines.h"
#include <catch2/catch.hpp>
#include "ClientDatabase.h"

tc("After registering client getClientFromId would give the registered client"){
  ClientDatabase database;
  asio::io_context context;
  Server::ptr server = Server::create(context);
  auto client = Client::create(context, server, 1);
  database.registerClient(client);
  req(database.getClientFromId(1).lock() == client);
}

tc("After removing registered client, asking for it would throw exception"){
  ClientDatabase database;
  asio::io_context context;
  Server::ptr server = Server::create(context);
  auto client = Client::create(context, server, 1);
  database.registerClient(client);
  database.removeClient(client);
  reqThrows(database.getClientFromId(1));
}
