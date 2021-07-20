;
; Copyright © 2021 BIG SYSTEMS
;
; This file is part of BIG SYSTEMS OS.
;
; BIG SYSTEMS OS is free software: you can redistribute it and/or
; modify it under the terms of the GNU Public License Version 2 as published
; by the Free Software Foundation.
;
; BIG SYSTEMS OS is distributed in the hope that it will be useful,
; but WITHOUT ANY WARRANTY; without even the implied warranty of
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General
; Public License for more details.
;
; You should have received a copy of the GNU General Public License along
; with this program.  If not, see <https://www.gnu.org/licenses/>.
;
global long_mode_start
extern kernel_main

section .text
bits 64
long_mode_start:
    ; load null into all data segment registers
    mov ax, 0
    mov ss, ax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

	call kernel_main
    hlt