// little-RISC.cpp : Defines the entry point for the application.
//

#include "little-RISC.h"

/////////////////////opcArgBrgIMMEDIA
uint16_t hex[] = { 0b1000010111000011, 0b1000110111000011 };
uint8_t *binary = reinterpret_cast<uint8_t*>(hex);

int main()
{
	auto RAM = memory::Memory(1024 * MEMORY_SIZE);
	auto emulator = emulator::Emulator<cpu_register_width>(RAM);
	auto emulator1 = emulator::Emulator<cpu_register_width>(RAM);
	emulator.RAM.write(25, 125);
	emulator.run(binary, 4);
	emulator.dumpRegisters();
	emulator.advanceClock();
	emulator.advanceClock();
	emulator.advanceClock();
	std::cout << emulator.metadata.clock << std::endl;
	std::cout << emulator1.metadata.clock << std::endl;
	std::cout  << static_cast<uint32_t>(RAM.read(25)) << "   " << emulator.metadata.clock << std::endl;
	return 0;
}

struct pipeline_registers {
	bool flush = false;
	bool branch = false;
	bool cpu_stall = false;
} pipeline_registers;