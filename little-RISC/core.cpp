#include "core.h"

using namespace core;

template<typename CPU_WIDTH>
Core<CPU_WIDTH>::Core(memory::Memory& RAM_) :
  RAM(RAM_) {};

template<typename CPU_WIDTH>
Core<CPU_WIDTH>::~Core() {};

template<typename REG_WIDTH>
void Core<REG_WIDTH>::dumpRegisters(){
  std::cout << "register zr    " << int16_t(data_registers.zr) << "\n\r";
  std::cout << "register rp    " << int16_t(data_registers.rp) << "\n\r";
  std::cout << "register sp    " << int16_t(data_registers.sp) << "\n\r";
  std::cout << "register t0    " << int16_t(data_registers.t0) << "\n\r";
  std::cout << "register t1    " << int16_t(data_registers.t1) << "\n\r";
  std::cout << "register t2    " << int16_t(data_registers.t2) << "\n\r";
  std::cout << "register t3    " << int16_t(data_registers.t3) << "\n\r";
  std::cout << "register FLAGS " << data_registers.FLAGS << "\n\r";
}

template<typename CPU_WIDTH>
void Core<CPU_WIDTH>::advanceClock() { 
  metadata.clock += 1; 
}

template<typename REG_WIDTH>
void Core<REG_WIDTH>::updateDisplay(){

}
//template<typename CPU_WIDTH>
//void Core<CPU_WIDTH>::run() {};

template class Core<uint16_t>;
template class Core<uint32_t>;
template class Core<uint64_t>;
