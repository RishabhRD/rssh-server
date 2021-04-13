#pragma once
#include <vector>
#include <cstdint>
class IDAllocator {
  int id;
  static IDAllocator defaultAllocator;
  std::vector<std::uint32_t> deallocatedList;


public:
  IDAllocator();
  static IDAllocator &getDefault();
  std::uint32_t allocate();
  void deallocate(std::uint32_t id);
};
