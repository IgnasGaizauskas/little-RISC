#pragma once

//default define for CPU register width
#ifndef CPU_REGISTER_WIDTH
#define CPU_REGISTER_WIDTH 16 //bit
#endif
#if CPU_REGISTER_WIDTH == 16
using cpu_register_width = uint16_t;
#endif
#if CPU_REGISTER_WIDTH == 32
using cpu_register_width = uint32_t;
#endif
#if CPU_REGISTER_WIDTH == 64
using cpu_register_width = uint64_t;
#endif

#ifndef PREFETCH // STATIC | DYNAMIC
#define PREFETCH STATIC
#endif 

#ifndef MEMORY_SIZE
#define MEMORY_SIZE 4 //kiB
#endif

#ifndef SIMULATE_RAM_DELAY
#define SIMULATE_RAM_DELAY == false
#endif 

#ifndef CACHE
#define CACHE false
#if CACHE == true
#define DATA_CACHE 512//bytes
#define INSTRUCTION_CACHE 512//bytes
#endif
#endif

#ifndef REGISTER_RENAMING
#define REGISTER_RENAMING false
#define PHYSICAL_REGISTER_COUNT = 40;
#endif