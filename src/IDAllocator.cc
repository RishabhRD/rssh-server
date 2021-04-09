#include "IDAllocator.h"
#include "IDUnavailableException.h"
#include <new>
#include <stdexcept>

IDAllocator::IDAllocator() : id(0){
}

IDAllocator &IDAllocator::getDefault() { return defaultAllocator; }

std::uint32_t IDAllocator::allocate() {
  if(deallocatedList.size() > 0){
    auto answer = deallocatedList.back();
    return answer;
  }
  if (id == UINT32_MAX) {
    throw IDUnavailableException("No more id available to allocate");
  }
  return id++;
}

void IDAllocator::deallocate(std::uint32_t id) {
  if (id >= this->id){
    throw std::invalid_argument("deallocation of unallocated id");
  }
  deallocatedList.push_back(id);
}
