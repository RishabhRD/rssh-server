#include <iostream>
#include "ServerListener.h"
using namespace std;
int main() {
  try{
  asio::io_context context;
  ServerListener listener(context, 8080);
  listener.startListening();
  context.run();
  }catch(std::system_error& error){
    cerr<<error.what()<<endl;
  }
}
