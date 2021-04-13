#include <catch2/catch.hpp>
#include "IDAllocator.h"
#include "defines.h"

tc("Should allocate 0 after construction"){
  IDAllocator allocator;
  req(allocator.allocate() == 0);
}

tc("Consecutive allocation without deallocation should give consecutive results"){
  IDAllocator allocator;
  req(allocator.allocate() == 0);
  req(allocator.allocate() == 1);
  req(allocator.allocate() == 2);
}

tc("Deallocation of number should make alloctor to allocate the deallocated number first"){
  IDAllocator allocator;
  allocator.allocate();
  allocator.allocate();
  allocator.allocate();
  allocator.deallocate(1);
  req(allocator.allocate() == 1);
}

tc("Deallocating a non-allocated id should throw exception"){
  IDAllocator allocator;
  allocator.allocate();
  allocator.allocate();
  REQUIRE_THROWS(allocator.deallocate(2));
}

tc("Should throw exception on allocating after limit"){
  IDAllocator allocator;
  for(std::uint32_t i = 0; i < UINT32_MAX; i++){
    allocator.allocate();
  }
  REQUIRE_THROWS(allocator.allocate());
}
