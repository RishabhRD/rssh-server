#include "Client.h"
#include <cstdint>
class ClientDatabase{
  static ClientDatabase defaultDatabase;
  public:
    ClientDatabase();
    static ClientDatabase& getDefault();
    void registerClient(std::weak_ptr<Client> client);
    void removeClient(std::weak_ptr<Client> client);
    std::weak_ptr<Client> getClientFromId(std::uint32_t id) const;
    bool isIDBeingUsed(std::uint32_t id) const noexcept;
};
