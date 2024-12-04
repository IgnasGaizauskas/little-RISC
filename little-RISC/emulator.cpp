#include "emulator.h"

using namespace emulator;
using namespace core;

template<typename REG_WIDTH>
Emulator<REG_WIDTH>::Emulator(memory::Memory& RAM_) :
  Core<REG_WIDTH>(RAM_) {};

//running the emulator
template<typename REG_WIDTH>
void Emulator<REG_WIDTH>::run(uint8_t program[], size_t size) {
  size_t counter = 0;
  while (counter <= size) {
    //Get current instruction
    this->control_registers.CI = this->control_registers.PC;
    //Reinterpret the prvided bytes as a 2 byte instruction
    uint16_t current_instruction =
      *reinterpret_cast<uint16_t*>(&program[this->control_registers.CI]);
    //get the opcode from the current instruction
    auto opcode = current_instruction >> 13;

    switch (opcode) {
    case static_cast<uint16_t>(INSTRUCTIONS::OPCODES::LOAD):
      LOAD(current_instruction);
      break;
    case static_cast<uint16_t>(INSTRUCTIONS::OPCODES::STORE):
      STORE(current_instruction);
      break;
    case static_cast<uint16_t>(INSTRUCTIONS::OPCODES::BEQ):
      BEQ(current_instruction);
      break;
    case static_cast<uint16_t>(INSTRUCTIONS::OPCODES::JALR):
      JALR(current_instruction);
      break;
    case static_cast<uint16_t>(INSTRUCTIONS::OPCODES::ADDI):
      ADDI(current_instruction);
      break;
    case static_cast<uint16_t>(INSTRUCTIONS::OPCODES::LUI):
      LUI(current_instruction);
      break;
    case static_cast<uint16_t>(INSTRUCTIONS::OPCODES::ARRIT):
      ARRIT(current_instruction);
      break;
    case static_cast<uint16_t>(INSTRUCTIONS::OPCODES::EXT):
      EXT(current_instruction);
      break;
    }
    counter += 2;
  }
}

//instruction execution
template<typename REG_WIDTH>
void Emulator<REG_WIDTH>::LOAD(uint16_t instruction){
}
template<typename REG_WIDTH>
void Emulator<REG_WIDTH>::STORE(uint16_t instruction) {
}
template<typename REG_WIDTH>
void Emulator<REG_WIDTH>::BEQ(uint16_t instruction) {
  constexpr REG_WIDTH neg_sign = static_cast<REG_WIDTH>((~0U) << 7U);
  bool last_equal = this->getEqualFlag();
  REG_WIDTH s = this->getA_reg(instruction);
  REG_WIDTH imm = this->getBEQIValue(instruction);
  if (last_equal == true) {
    this->control_registers.PC += imm;
  }
  else {
    this->control_registers.PC += 2;
  }
}
template<typename REG_WIDTH>
void Emulator<REG_WIDTH>::JALR(uint16_t instruction) {
  constexpr REG_WIDTH neg_sign = (~0U) << 7U;
  REG_WIDTH imm = this->getJALDII(instruction);
  REG_WIDTH sign = this->getJALDIIS(instruction);
  //sign extension
  if (sign == 1U) {
    imm = imm | neg_sign;
  }
  REG_WIDTH branch_address = this->data_registers[instruction & decode_masks.A_reg >> 10U] + imm;
  REG_WIDTH return_address = this->data_registers[instruction & decode_masks.B_reg >> 7U] + 2U;
  this->data_registers.rp = this->control_registers.CI + return_address;
  this->control_registers.PC = branch_address;
}
template<typename REG_WIDTH>
void Emulator<REG_WIDTH>::ADDI(uint16_t instruction) {
  constexpr REG_WIDTH neg_sign = (~0U) << 7U;
  REG_WIDTH imm = this->getJALDII(instruction);
  REG_WIDTH sign = this->getJALDIIS(instruction);
  //sign extension
  if (sign == decode_masks.JALDIIS) {
    imm = neg_sign | imm  ;
  }
  size_t src = this->getA_reg(instruction);
  size_t dst = this->getB_reg(instruction);
  std::cout << "imm " << int16_t(imm) << std::endl;
  std::cout << "src " << src << std::endl;
  std::cout << "dst " << dst << std::endl;
  this->data_registers[dst] = this->data_registers[src] + imm;
  this->control_registers.PC += 2U;
}
template<typename REG_WIDTH>
void Emulator<REG_WIDTH>::LUI(uint16_t instruction) {
  REG_WIDTH dst = this->getA_reg(instruction);
  REG_WIDTH imm = this->getLUII(instruction);
  this->control_registers.PC += 2;
}
template<typename REG_WIDTH>
void Emulator<REG_WIDTH>::ARRIT(uint16_t instruction) {
}
template<typename REG_WIDTH>
void Emulator<REG_WIDTH>::EXT(uint16_t instruction) {
}

//explicit instantiation
template class Emulator<uint16_t>;
template class Emulator<uint32_t>;
template class Emulator<uint64_t>;
