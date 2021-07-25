#include <stdbool.h>
#include "interrupts.h"
#include "../graphics.h"
#include "../kernel.h"
#include "../panic.h"
#include "../io.h"


__attribute__((interrupt)) void pageFault_handler(struct interrupt_frame* frame){
    panic_panic("Page Fault Detected");
}

__attribute__((interrupt)) void doubleFault_handler(struct interrupt_frame* frame){
    panic_panic("Dobule Fault Detected");
}

__attribute__((interrupt)) void gpFault_handler(struct interrupt_frame* frame){
    panic_panic("Genral Protection Fault Detected");
}

__attribute__((interrupt)) void keyboard_handler(struct interrupt_frame* frame) {
    panic_test();
    uint8_t scancode = io_readFromBus(0x60);
    interrupts_picEndMaster();

}

void interrupts_remapPIC() {
    uint8_t bitmask1, bitmask2;

    bitmask1 = io_readFromBus(PIC1_DATA);
    io_wait();
    bitmask2 = io_readFromBus(PIC2_DATA);
    io_wait();

    // Initilize master PIC chip
    io_writeToBus(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
    io_wait();

    // Initilize slave PIC chip
    io_writeToBus(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
    io_wait();

    // Provide chips with interupt offset so that they don't collide with exceptions
    io_writeToBus(PIC1_DATA, 0x20);
    io_wait();
    io_writeToBus(PIC2_DATA, 0x28);
    io_wait();

    // Tell the chips how to communicate with eachother
    io_writeToBus(PIC1_DATA, 4);
    io_wait();
    io_writeToBus(PIC2_DATA, 2);
    io_wait();

    // Set the chips to 8086 mode
    io_writeToBus(PIC1_DATA, ICW4_8086);
    io_wait();
    io_writeToBus(PIC2_DATA, ICW4_8086);
    io_wait();

    // Restore bitmasks
    io_writeToBus(PIC1_DATA, bitmask1);
    io_wait();
    io_writeToBus(PIC2_DATA, bitmask2);
    io_wait();
}    

void interrupts_picEndMaster() {
    io_writeToBus(PIC1_COMMAND, PIC_EOI);
}

void interrupts_picEndSlave() {
    io_writeToBus(PIC2_COMMAND, PIC_EOI);
    interrupts_picEndMaster();
}