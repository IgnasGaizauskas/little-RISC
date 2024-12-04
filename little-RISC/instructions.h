#pragma once

#include <stdint.h>

namespace INSTRUCTIONS {

  enum class OPCODES : uint8_t {
    LOAD,
    STORE,
    BEQ,
    JALR,
    ADDI,
    LUI,
    ARRIT,
    EXT
  };

  namespace MEMORY {
    enum class LOAD_INST : uint8_t {
      LOAD,
      LOAD_INCREMENT,
      LOAD_DECREMENT,
      LOAD_PC_RELATIVE,
      LOAD_IF_EQUAL,
      LOAD_IF_NOT_EQUAL,
      LOAD_IF_ZERO,
      LOAD_IF_NOT_ZERO
    };
    enum class STORE_INST : uint8_t {
      STORE,
      STORE_INCREMENT,
      STORE_DECREMENT,
      STORE_PC_RELATIVE,
      STORE_IF_EQUAL,
      STORE_IF_NOT_EQUAL,
      STORE_IF_ZERO,
      STORE_IF_NOT_ZERO
    };
  };

  enum class ARRIT : uint8_t {
    AND,
    OR,
    NOT,
    XOR,
    NAND,
    LSHIFT,
    RSHIFT,
    LROTATE,
    RROTATE,
    ADD,
    ADDC,
    SUB,
    SUBC,
    EQ,
    LESS,
    MORE,
  };

  enum class EXT : uint8_t {
    MULSxU,
    MULSxS,
    MULUxU,
    IDIV,
    MOD,
    CLZ,
    CTZ,
    POPCNT,
    CSW,
    LSHIFT8,
    RSHIFT8,
    LDIR,
    LDID,
    LDIC,
    CPIR,
    ISQRT
  };
};