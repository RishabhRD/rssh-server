#include <asio.hpp>
#include "defines.h"
#include <catch2/catch.hpp>
#include "ClientDatabase.h"
#include "Server.h"
#include "Client.h"

tc("After registering client getClientFromId would give the registered client"){
  ClientDatabase database;
  asio::io_context context;
  Server::ptr server = Server::create(context);
  IDAllocator allocator;
  int id = allocator.allocate();
  auto client = Client::create(context, server, id, allocator);
  database.registerClient(id, client);
  req(database.getClientFromId(id).lock() == client);
}

tc("After removing registered client, asking for it would throw exception"){
  ClientDatabase database;
  asio::io_context context;
  Server::ptr server = Server::create(context);
  IDAllocator allocator;
  int id = allocator.allocate();
  auto client = Client::create(context, server, id, allocator);
  database.registerClient(id, client);
  database.removeClient(id);
  reqThrows(database.getClientFromId(id));
}

tc("Once registered client with a ID, idBeingUsed should return true for that"){
  ClientDatabase database;
  asio::io_context context;
  Server::ptr server = Server::create(context);
  IDAllocator allocator;
  int id = allocator.allocate();
  auto client = Client::create(context, server, id, allocator);
  database.registerClient(id, client);
  req(database.isIDBeingUsed(id) == true);
}

tc("Client registered with a ID and after remvoe should return false"){
  ClientDatabase database;
  asio::io_context context;
  Server::ptr server = Server::create(context);
  IDAllocator allocator;
  int id = allocator.allocate();
  auto client = Client::create(context, server, id, allocator);
  database.registerClient(id, client);
  database.removeClient(id);
  req(database.isIDBeingUsed(id) == false);
}

tc("Registering a client with preRegisteredId should throw exception"){
  ClientDatabase database;
  asio::io_context context;
  Server::ptr server = Server::create(context);
  IDAllocator allocator;
  int id = allocator.allocate();
  auto client = Client::create(context, server, id, allocator);
  database.registerClient(id, client);
  reqThrows(database.registerClient(id, client));
}
