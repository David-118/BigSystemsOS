/*
 * Copyright © 2021 BIG SYSTEMS INC
 *
 * This file is part of BIG SYSTEMS OS.
 *
 * BIG SYSTEMS OS is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Public License Version 2 as published
 * by the Free Software Foundation.
 *
 * BIG SYSTEMS OS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General
 * Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#pragma  once

enum DescType
{
    EfiLoaderCode ,
    EfiReservedMemoryType ,
    EfiLoaderData ,
    EfiBootServicesCode ,
    EfiBootServicesData ,
    EfiRuntimeServicesCode ,
    EfiRuntimeServicesData ,
    EfiConventionalMemory ,
    EfiUnusableMemory ,
    EfiACPIReclaimMemory ,
    EfiACPIMemoryNVS ,
    EfiMemoryMappedIO ,
    EfiPalCode ,
};

typedef struct
{
    enum DescType type;
    void* physAddr;
    void* virtAddr;
    unsigned long numPages;
    unsigned long attribs;
} EFI_MEMORY_DESCRIPTOR;




extern const char* EFI_MEMORY_TYPE_STRINGS[];