#include <uvw.hpp>
class ServerListener {
private:
  int listeningPort;
  uvw::Loop &eventLoop;
  std::shared_ptr<uvw::TCPHandle> tcpHandle;

public:
  ServerListener(uvw::Loop &eventLoop, int listeningPort);

private:
  void onListenAccept(const uvw::ListenEvent &, uvw::TCPHandle &srv);
  void bindConnectionEvent();
  void onSSHServerConnectionClosed(const uvw::EndEvent &,
                                   uvw::TCPHandle &sshServer);
  void onSSHServerSentData(const uvw::DataEvent &, uvw::TCPHandle &sshServer);
  std::shared_ptr<uvw::TCPHandle>
  createClientListenerSocket(std::shared_ptr<uvw::TCPHandle> &sshServerHandle);
};
