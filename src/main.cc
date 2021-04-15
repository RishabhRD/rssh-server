#include "ServerListener.h"
#include <iostream>
using namespace std;
int main(int argc, char **argv) {
  try {
    if(argc != 2){
      cerr<<"Usage: rssh-server <port>"<<endl;
      return 1;
    }
    std::string port = argv[1];
    int portNum = std::stoi(port);
    asio::io_context context;
    auto listener = ServerListener::create(context, portNum);
    listener->startListening();
    context.run();
  } catch (std::system_error &error) {
    cerr << error.what() << endl;
  } catch (std::exception &ex) {
    cerr << ex.what() << endl;
  }
}
