#pragma once
class Client;
#include <memory>
#include <cstdint>
#include <unordered_map>
class ClientDatabase{
  std::unordered_map<std::uint32_t, std::weak_ptr<Client>> mp;
  public:
    ClientDatabase();
    void registerClient(std::uint32_t id, std::weak_ptr<Client> client);
    void removeClient(std::uint32_t id);
    std::weak_ptr<Client> getClientFromId(std::uint32_t id) const;
    bool isIDBeingUsed(std::uint32_t id) const noexcept;
    void removeAll();
};
