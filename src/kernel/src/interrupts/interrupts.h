#pragma once

#define PIC1_COMMAND 0x20
#define PIC1_DATA 0x21
#define PIC2_COMMAND 0xa0
#define PIC2_DATA 0xa1

#define ICW1_INIT 0x10
#define ICW1_ICW4 0x01
#define ICW4_8086 0x01


struct interrupt_frame;
// Writing to meory outside of your page
__attribute__((interrupt)) void pageFault_handler(struct interrupt_frame* frame);

// two unhandled falts
__attribute__((interrupt)) void doubleFault_handler(struct interrupt_frame* frame);

/* 
 * Can be trigged by many issues such as
 * Segment error
 * Executing privllaged intruction without said prilage
 * Refrencing or accesing a null descriptor"
*/
__attribute__((interrupt)) void gpFault_handler(struct interrupt_frame* frame);

// This when is pretty self explanitray
__attribute__((interrupt)) void keyboard_handler(struct interrupt_frame* frame);

void interrupts_remapPIC();