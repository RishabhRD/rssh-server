#pragma once
#include <vector>
#include <cstdint>
class IDAllocator {
  int id;
  std::vector<std::uint32_t> deallocatedList;


public:
  IDAllocator();
  std::uint32_t allocate();
  void deallocate(std::uint32_t id);
};
