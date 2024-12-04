#pragma once

#include <iostream>

#include "memory.h"
#include "core.h"
#include "instructions.h"


namespace emulator {
  template<typename REG_WIDTH>
  class Emulator : public core::Core<REG_WIDTH> {
    void LOAD(uint16_t instruction);
    void STORE(uint16_t instruction);
    void BEQ(uint16_t instruction);
    void JALR(uint16_t instruction);
    void ADDI(uint16_t instruction);
    void LUI(uint16_t instruction);
    void ARRIT(uint16_t instruction);
    void EXT(uint16_t instruction);
  public:
    Emulator() = delete;
    Emulator(memory::Memory &ram);
    //void advanceClock();
    //struct execute {

    //} execute;
    void run(uint8_t program[], size_t size) override;
  };
}

