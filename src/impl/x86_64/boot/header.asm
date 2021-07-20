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
section .multiboot_header
header_start:
    ; This is the magic number Multi-Boot 2 will look for
    dd 0xe85250d6
    ; Specify architecture
    dd 0 ;0 means protected mode i386
    ; specify the head length, length is implied from header_end-header_start
    dd header_end-header_start
    ; make checksum for error checking, the checksum takes into account all previous numbers
    dd 0x100000000 - (0xe85250d6 + 0 + (header_end-header_start))
    ; end tag to say we don't have anymore data
    dw 0
    dw 0
    dd 8
header_end: