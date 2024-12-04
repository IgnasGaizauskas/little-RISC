#pragma once

#include <memory>

namespace memory {
  class Memory {
    uint8_t* data;
    size_t size;
  public:
    Memory(size_t memory_size);
    ~Memory();
    uint8_t read(size_t address) const;
    void write(size_t address, uint8_t data);
  };
}