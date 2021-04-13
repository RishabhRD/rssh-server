#include <asio.hpp>
#include "defines.h"
#include <catch2/catch.hpp>
#include "ClientDatabase.h"

tc("After registering client getClientFromId would give the registered client"){
  ClientDatabase database;
  asio::io_context context;
  Server::ptr server = Server::create(context);
  auto client = Client::create(context, server, 1);
  database.registerClient(1, client);
  req(database.getClientFromId(1).lock() == client);
}

tc("After removing registered client, asking for it would throw exception"){
  ClientDatabase database;
  asio::io_context context;
  Server::ptr server = Server::create(context);
  auto client = Client::create(context, server, 1);
  database.registerClient(1, client);
  database.removeClient(1);
  reqThrows(database.getClientFromId(1));
}

tc("Once registered client with a ID, idBeingUsed should return true for that"){
  ClientDatabase database;
  asio::io_context context;
  Server::ptr server = Server::create(context);
  auto client = Client::create(context, server, 1);
  database.registerClient(1, client);
  req(database.isIDBeingUsed(1) == true);
}

tc("Client registered with a ID and after remvoe should return false"){
  ClientDatabase database;
  asio::io_context context;
  Server::ptr server = Server::create(context);
  auto client = Client::create(context, server, 1);
  database.registerClient(1, client);
  database.removeClient(1);
  req(database.isIDBeingUsed(1) == false);
}

tc("Registering a client with preRegisteredId should throw exception"){
  ClientDatabase database;
  asio::io_context context;
  Server::ptr server = Server::create(context);
  auto client = Client::create(context, server, 1);
  database.registerClient(1, client);
  reqThrows(database.registerClient(1, client));
}
