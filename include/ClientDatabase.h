#include "Client.h"
class ClientDatabase{
  public:
    ClientDatabase();
    void registerClient(std::weak_ptr<Client> client);
    void removeClient(std::weak_ptr<Client> client);
    std::weak_ptr<Client> getClientFromId(int id) const;
};
