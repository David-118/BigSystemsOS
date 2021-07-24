#pragma once

struct interrupt_frame;
__attribute__((interrupt)) void pageFault_handler(struct interrupt_frame* frame);
