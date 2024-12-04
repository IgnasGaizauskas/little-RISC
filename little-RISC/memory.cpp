#include "memory.h"

using namespace memory;

Memory::Memory(size_t ram_size): 
  size(ram_size) {
  Memory::data = new uint8_t[ram_size];
};
  
Memory::~Memory(){
  delete data;
}

uint8_t Memory::read(size_t address) const{
  return Memory::data[address];
}

void Memory::write(size_t address, uint8_t data){
  Memory::data[address] = data;
}
