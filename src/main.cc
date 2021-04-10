#include <iostream>
#include <IDAllocator.h>
#include <CloseMessage.h>
IDAllocator IDAllocator::defaultAllocator = IDAllocator();
int main() {
  Message msg(MessageType::CLOSE);
}
