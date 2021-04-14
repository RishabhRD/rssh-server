#include <iostream>
#include "ServerListener.h"
using namespace std;
int main() {
  try{
  asio::io_context context;
  auto listener = ServerListener::create(context, 8080);
  listener->startListening();
  context.run();
  }catch(std::system_error& error){
    cerr<<error.what()<<endl;
  }
}
