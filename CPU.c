#include <stdio.h>
#include <stdlib.h>
#define KB 1024
#define ZERO_PAGE 0
#define ZERO_PAGE_X 1
#define ZERO_PAGE_Y 2
#define ABSOLUTE 3
#define ABSOLUTE_X 4
#define ABSOLUTE_Y 5
#define INDIRECT 6
#define INDIRECT_X 7
#define INDIRECT_Y 8
#define IMPLIED 9
#define ACCUMULATOR 10
#define IMMEDIATE 11
#define RELATIVE 12
#define INVALID -1
// Not yet quite sure about how I want to set up my struct for the CPU.

//6502

//struct CPU {
//  unsigned char zeroPage[100];
//  unsigned char stack[100];
//  unsigned char ram[600];
//  unsigned char IO[20];
//  unsigned char expRom[1980];
//  unsigned char sram[2000];
//  unsigned char lowPrgRom[4000];
//  unsigned char upPrgRom[4000];
//}
//}

struct opcode {
  unsigned char code[3];
  char mode[11];
  u_int8_t hex;
  u_int8_t operands;
};

// instruction name, address mode, address, length in bytes
const struct opcode opcodes[256] = {
  {"BRK", IMPLIED, 1},    // 0x00
  {"ORA", INDIRECT_X, 2},
  {"NAN", INVALID, 0},
  {"NAN", INVALID, 0},
  {"NAN", INVALID, 0},
  {"ORA", ZERO_PAGE, 2},
  {"ASL", ZERO_PAGE, 2},
  {"NAN", INVALID, 0},
  {"PHP", IMPLIED, 1},
  {"ORA", IMMEDIATE, 2},
  {"ASL", ACCUMULATOR, 1},
  {"NAN", INVALID, 0},
  {"NAN", INVALID, 0},
  {"ORA", ABSOLUTE, 3},
  {"ASL", ABSOLUTE, 3},
  {"NAN", INVALID, 0},    // 0x0F
  {"BPL", RELATIVE, 2},
  {"ORA", INDIRECT_Y, 2},
  {"NAN", INVALID, 0},
  {"NAN", INVALID, 0},
  {"NAN", INVALID, 0},
  {"ORA", ZERO_PAGE_X, 1},
  {"ASL", ZERO_PAGE_X, 2},
  {"NAN", INVALID, 0},
  {"CLC", IMPLIED, 1},
  {"ORA", ABSOLUTE_Y, 3},
  {"NAN", INVALID, 0},
  {"NAN", INVALID, 0},
  {"NAN", INVALID, 0},
  {"ORA", ABSOLUTE_X, 3},
  {"ASL", ABSOLUTE_X, 3},
  {"NAN", INVALID, 0},    // 0x1F
  {"JSR", ABSOLUTE, 3},
  {"AND", INDIRECT_X, 2},
  {"NAN", INVALID, 0},
  {"NAN", INVALID, 0},
  {"BIT", ZERO_PAGE, 2},
  {"AND", ZERO_PAGE, 2},
  {"ROL", ZERO_PAGE, 2},
  {"NAN", INVALID, 0},
  {"PLP", IMPLIED, 1},
  {"AND", IMMEDIATE, 2},
  {"ROL", ACCUMULATOR, 1},
  {"NAN", INVALID, 0},
  {"BIT", ABSOLUTE, 3},
  {"AND", ABSOLUTE, 3},
  {"ROL", ABSOLUTE, 3},
  {"NAN", INVALID, 0},   // 0x2F
  {"BMI", RELATIVE, 2},
  {"AND", INDIRECT_Y, 2},
  {"NAN", INVALID, 0},
  {"NAN", INVALID, 0},
  {"NAN", INVALID, 0},
  {"AND", ZERO_PAGE_X, 2},
  {"ROL", ZERO_PAGE_X, 2},
  {"NAN", INVALID, 0},
  {"SEC", IMPLIED, 1},
  {"AND", ABSOLUTE_Y, 3},
  {"NAN", INVALID, 0},
  {"NAN", INVALID, 0},
  {"NAN", INVALID, 0},
  {"AND", ABSOLUTE_X, 3},
  {"ROL", ABSOLUTE_X, 3},
  {"NAN", INVALID, 0x02, 0},  // 0x3F
  {"RTI", IMPLIED, 1},
  {"EOR", INDIRECT_X, 2},
  {"NAN", INVALID, 0},
  {"NAN", INVALID, 0},
  {"NAN", INVALID, 0},
  {"EOR", ZERO_PAGE, 2},
  {"LSR", ZERO_PAGE, 2},
  {"NAN", INVALID, 0},
  {"PHA", IMPLIED, 1},
  {"EOR", IMMEDIATE, 2},
  {"LSR", ACCUMULATOR, 1},
  {"NAN", INVALID, 0},
  {"JMP", ABSOLUTE, 3},
  {"EOR", ABSOLUTE, 3},
  {"LSR", ABSOLUTE, 3},
  {"NAN", INVALID, 0},    // 0x4F
  {"BVC", RELATIVE, 2},
  {"EOR", INDIRECT_Y, 2},
  {"NAN", INVALID, 0},
  {"NAN", INVALID, 0},
  {"NAN", INVALID, 0},
  {"EOR", ZERO_PAGE_X, 2},
  {"LSR", ZERO_PAGE_X, 2},
  {"NAN", INVALID, 0},
  {"CLI", IMPLIED, 1},
  {"EOR", ABSOLUTE_Y, 3},
  {"NAN", INVALID, 0},
  {"NAN", INVALID, 0},
  {"NAN", INVALID, 0},
  {"EOR", ABSOLUTE_X, 3},
  {"LSR", ABSOLUTE_X, 3},
  {"NAN", INVALID, 0},    // 0x5F
  {"RTS", IMPLIED, 1},
  {"ADC", INDIRECT_X, 2},
  {"NAN", INVALID, 0},
  {"NAN", INVALID, 0},
  {"NAN", INVALID, 0},
  {"ADC", ZERO_PAGE, 2},
  {"ROR", ZERO_PAGE, 2},
  {"NAN", INVALID, 0},
  {"PLA", IMPLIED, 1},
  {"ADC", IMMEDIATE, 2},
  {"ROR", ACCUMULATOR, 1},
  {"NAN", INVALID, 0},
  {"JMP", INDIRECT, 3},
  {"ADC", ABSOLUTE, 3},
  {"ROR", ABSOLUTE, 3},
  {"NAN", INVALID, 0},    // 0x6F
  {"BVS", RELATIVE, 2},
  {"ADC", INDIRECT_Y, 2},
  {"NAN", INVALID, 0},
  {"NAN", INVALID, 0},
  {"NAN", INVALID, 0},
  {"ADC", ZERO_PAGE_X, 2},
  {"ROR", ZERO_PAGE_X, 2},
  {"NAN", INVALID, 0},
  {"SEI", IMPLIED, 1},
  {"ADC", ABSOLUTE_Y, 3},
  {"NAN", INVALID, 0},
  {"NAN", INVALID, 0},
  {"NAN", INVALID, 0},
  {"ADC", ABSOLUTE_X, 3},
  {"ROR", ABSOLUTE_X, 3},
  {"NAN", INVALID, 0},    // 0x7F
  {"NAN", INVALID, 0},
  {"STA", INDIRECT_X, 2},
  {"NAN", INVALID, 0},
  {"NAN", INVALID, 0},
  {"STY", ZERO_PAGE, 2},
  {"STA", ZERO_PAGE, 2},
  {"STX", ZERO_PAGE, 2},
  {"NAN", INVALID, 0},
  {"DEY", IMPLIED, 1},
  {"NAN", INVALID, 0},
  {"TXA", IMPLIED, 1},
  {"NAN", INVALID, 0},
  {"STY", ABSOLUTE, 3},
  {"STA", ABSOLUTE, 3},
  {"STX", ABSOLUTE, 3},
  {"NAN", INVALID, 0},    // 0x8F
  {"BCC", RELATIVE, 2},
  {"STA", INDIRECT_Y, 2},
  {"NAN", INVALID, 0},
  {"NAN", INVALID, 0},
  {"STY", ZERO_PAGE_X, 2},
  {"STA", ZERO_PAGE_X, 2},
  {"STX", ZERO_PAGE_X, 2},
  {"NAN", INVALID, 0},
  {"TYA", IMPLIED, 1},
  {"STA", ABSOLUTE_Y, 3},
  {"TXS", IMPLIED, 1},
  {"NAN", INVALID, 0},
  {"NAN", INVALID, 0},
  {"STA", ABSOLUTE_X, 3},
  {"NAN", INVALID, 0},
  {"NAN", INVALID, 0},  // 0x9F
  {"LDY", IMMEDIATE, 2},
  {"LDA", INDIRECT_X, 2},
  {"LDX", IMMEDIATE, 2},
  {"NAN", INVALID, 0},
  {"LDY", ZERO_PAGE, 2},
  {"LDA", ZERO_PAGE, 2},
  {"LDX", ZERO_PAGE, 2},
  {"NAN", INVALID, 0},
  {"TAY", IMPLIED, 1},
  {"LDA", IMMEDIATE, 2},
  {"TAX", IMPLIED, 1},
  {"NAN", INVALID, 0},
  {"LDY", ABSOLUTE, 3},
  {"LDA", ABSOLUTE, 3},
  {"LDX", ABSOLUTE, 3},
  {"NAN", INVALID, 0},    // 0xAF
  {"BCS", RELATIVE, 2}, 
  {"LDA", INDIRECT_Y, 2},
  {"NAN", INVALID, 0},
  {"NAN", INVALID, 0},
  {"LDY", ZERO_PAGE_X, 2},
  {"LDA", ZERO_PAGE_X, 2},
  {"LDX", ZERO_PAGE_Y, 2},
  {"NAN", INVALID, 0},
  {"CLV", IMPLIED, 1},
  {"LDA", ABSOLUTE_Y, 3},
  {"TSX", IMPLIED, 1},
  {"NAN", INVALID, 0},
  {"LDY", ABSOLUTE_X, 3},
  {"LDA", ABSOLUTE_X, 3},
  {"LDX", ABSOLUTE_Y, 3},
  {"NAN", INVALID, 0},    // 0xBF
  {"CPY", IMMEDIATE, 2},
  {"CMP", INDIRECT_X, 2},
  {"NAN", INVALID, 0},
  {"NAN", INVALID, 0},
  {"CPY", ZERO_PAGE, 2},
  {"CMP", ZERO_PAGE, 2},
  {"DEC", ZERO_PAGE, 2},
  {"NAN", INVALID, 0},
  {"INY", IMPLIED, 1},
  {"CMP", IMMEDIATE, 2},
  {"DEX", IMPLIED, 1},
  {"NAN", INVALID, 0},
  {"CPY", ABSOLUTE, 3},
  {"CMP", ABSOLUTE, 3},
  {"DEC", ABSOLUTE, 3},
  {"NAN", INVALID, 0},    // 0xCF     
  {"BNE", RELATIVE, 2},
  {"CMP", INDIRECT_Y, 2},
  {"NAN", INVALID, 0},
  {"NAN", INVALID, 0},
  {"NAN", INVALID, 0},
  {"CMP", ZERO_PAGE_X, 2},
  {"DEC", ZERO_PAGE_X, 2},
  {"NAN", INVALID, 0},
  {"CLD", IMPLIED, 1},
  {"CMP", ABSOLUTE_Y, 3},
  {"NAN", INVALID, 0},
  {"NAN", INVALID, 0},
  {"NAN", INVALID, 0},
  {"CMP", ABSOLUTE_X, 3},
  {"DEC", ABSOLUTE_X, 3},
  {"NAN", INVALID, 0},      // 0xDF
  {"CPX", IMMEDIATE, 2},
  {"SBC", INDIRECT_X, 2},
  {"NAN", INVALID, 0},
  {"NAN", INVALID, 0},
  {"CPX", ZERO_PAGE, 2},
  {"SBC", ZERO_PAGE, 2},
  {"INC", ZERO_PAGE, 2},
  {"NAN", INVALID, 0},
  {"INX", IMPLIED, 1},
  {"SBC", IMMEDIATE, 2},
  {"NOP", IMPLIED, 1},
  {"NAN", INVALID, 0},
  {"CPX", ABSOLUTE, 3},
  {"SBC", ABSOLUTE, 3},
  {"INC", ABSOLUTE, 3},
  {"NAN", INVALID, 0},  // 0xEF
  {"BEQ", RELATIVE, 2},
  {"SBC", INDIRECT_Y, 2},
  {"NAN", INVALID, 0},
  {"NAN", INVALID, 0},
  {"NAN", INVALID, 0},
  {"SBC", ZERO_PAGE_X, 2},
  {"INC", ZERO_PAGE_X, 2},
  {"NAN", INVALID, 0},
  {"SED", IMPLIED, 1},
  {"SBC", ABSOLUTE_Y, 3},
  {"NAN", INVALID, 0},      // 0xFA
  {"NAN", INVALID, 0},      // 0xFB
  {"NAN", INVALID, 0},      // 0xFC
  {"SBC", ABSOLUTE_X, 3},   // 0xFD
  {"INC", ABSOLUTE_X, 3},   // 0xFE
  {"NAN", INVALID, 0}      // 0xFF
};
