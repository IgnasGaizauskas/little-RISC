#pragma once


#include <stdint.h>
#include <iostream>

#include "memory.h"
#include "instructions.h"

namespace core {
  
  //MSVC complains about redefinition without this monstrosity, even with c++20
  inline struct decode_masks {
    inline static constexpr uint16_t opcode = 0b1110000000000000;
    inline static constexpr uint16_t A_reg  = 0b0001110000000000;
    inline static constexpr uint16_t B_reg  = 0b0000001110000000;
    inline static constexpr uint16_t C_reg  = 0b0000000000000111;
    inline static constexpr uint16_t func   = 0b0000000001111000;
    inline static constexpr uint16_t sign   = 0b0000000000000001;
    inline static constexpr uint16_t width  = 0b0000000000000110;
    inline static constexpr uint16_t BEQI   = 0b0001111111111111;
    inline static constexpr uint16_t BEQIS  = 0b0001000000000000;
    inline static constexpr uint16_t LUII   = 0b0000001111111111;
    inline static constexpr uint16_t JALDII = 0b0000000001111111;
    inline static constexpr uint16_t JALDIIS= 0b0000000001000000;
  } decode_masks;

  inline struct FLAGS_masks {
    inline static constexpr uint16_t zero     = 0b0000000000000001;
    inline static constexpr uint16_t overflow = 0b0000000000000010;
    inline static constexpr uint16_t equal    = 0b0000000000000100;
    inline static constexpr uint16_t trap     = 0b0000000000001000;
    inline static constexpr uint16_t interrupt= 0b0000000000010000;
    inline static constexpr uint16_t kernel   = 0b0000000000100000;
  } FLAGS_masks;

  template<typename REG_WIDTH>
  class Core {
  public:
    //memory subsystem
    memory::Memory& RAM;

    //register width in bytes
    static constexpr size_t REG_WIDTH_BYTES = sizeof(REG_WIDTH);

    struct control_registers {
      REG_WIDTH CI = 0;//current instruction
      REG_WIDTH PC = 0;//program counter
    } control_registers;

    struct data_registers {
      REG_WIDTH zr = 0;
      REG_WIDTH rp = 0;
      REG_WIDTH sp = 0;
      REG_WIDTH t0 = 0;
      REG_WIDTH t1 = 0;
      REG_WIDTH t2 = 0;
      REG_WIDTH t3 = 0;
      REG_WIDTH FLAGS = 0;
      REG_WIDTH& operator[](size_t i) { return *(&zr + i); }
    } data_registers;

    struct metadata {
      size_t clock = 0;
      size_t instruction_number = 0;
    } metadata;

    //should be inline by default due to being defined in header
    inline REG_WIDTH getA_reg(uint16_t instruction) {
      return REG_WIDTH((decode_masks.A_reg & instruction) >> 10);
    };
    inline REG_WIDTH getB_reg(uint16_t instruction) {
      return REG_WIDTH((decode_masks.B_reg & instruction) >> 7);
    };
    inline REG_WIDTH getC_reg(uint16_t instruction) {
      return REG_WIDTH((decode_masks.C_reg & instruction) );
    };
    inline REG_WIDTH getBEQI(uint16_t instruction) {
      auto gg = instruction & 5U;
      return REG_WIDTH(instruction & decode_masks.BEQI);
    };
    inline REG_WIDTH getBEQIValue(uint16_t instruction) {
      constexpr REG_WIDTH neg_sign = static_cast<size_t>((~0U) << 7U);
      REG_WIDTH imm = instruction & decode_masks.BEQI;
      REG_WIDTH sign = instruction & decode_masks.BEQIS >> 12U;
      if (sign == 1U) {
        imm = imm | neg_sign;
      }
      return imm;
    };
    inline REG_WIDTH getLUII(uint16_t instruction) {
      return REG_WIDTH(instruction & decode_masks.LUII);
    };
    inline REG_WIDTH getJALDII(uint16_t instruction) {
      return REG_WIDTH(decode_masks.JALDII & instruction);
    };
    inline REG_WIDTH getJALDIIS(uint16_t instruction) {
      return REG_WIDTH(decode_masks.JALDIIS & instruction);
    };
    inline REG_WIDTH getZeroFlag() {
      return data_registers.FLAGS & FLAGS_masks.zero;
    };
    inline REG_WIDTH getOverflowFlag() {
      return (data_registers.FLAGS & FLAGS_masks.overflow) >> 1;
    };
    inline REG_WIDTH getEqualFlag() {
      return (data_registers.FLAGS & FLAGS_masks.equal) >> 2;
    };
    inline REG_WIDTH getTrapFlag() {
      return (data_registers.FLAGS & FLAGS_masks.trap) >> 3;
    };
    inline REG_WIDTH getInterruptFlag() {
      return (data_registers.FLAGS & FLAGS_masks.interrupt) >> 4;
    };
    inline REG_WIDTH getKernelFlag() {
      return (data_registers.FLAGS & FLAGS_masks.kernel) >> 5 ;
    };

    void dumpRegisters();
    void advanceClock();
    void updateDisplay();
    void virtual run(uint8_t program[], size_t size) = 0;
    Core() = delete;
    Core(memory::Memory& RAM_);
    ~Core();
  };
}