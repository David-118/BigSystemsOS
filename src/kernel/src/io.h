#pragma once

#include "stdint.h"

void io_writeToBus(uint16_t port, uint8_t value);
uint8_t io_readFromBus(uint16_t port);
void io_wait();
