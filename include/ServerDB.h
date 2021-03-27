#include <unordered_map>
#include <uvw.hpp>
class ServerDB {
private:
  std::unordered_map<std::shared_ptr<uvw::TCPHandle>,
                     std::shared_ptr<uvw::TCPHandle>>
      clientSocketMap;
  static std::unique_ptr<ServerDB> defaultDBInstance;

public:
  static ServerDB& getDefault();
  void put(std::shared_ptr<uvw::TCPHandle> clientHandle,
           std::shared_ptr<uvw::TCPHandle> serverHandle);
  void remove(std::shared_ptr<uvw::TCPHandle> clientHandle);
  bool contains(std::shared_ptr<uvw::TCPHandle> clientHandle);
  std::optional<std::shared_ptr<uvw::TCPHandle>>
  get(std::shared_ptr<uvw::TCPHandle> clientHandle);
};
