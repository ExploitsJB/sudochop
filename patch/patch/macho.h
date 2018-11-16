/**
 * libmacho-1.0 - macho.h
 * Copyright (C) 2013 Crippy-Dev Team
 * Copyright (C) 2010-2013 Joshua Hill
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 **/

#ifndef MACHO_H_
#define MACHO_H_

#include "debug.h"
#include "symtab.h"
#include "segment.h"
#include "section.h"
#include "command.h"

#define MACHO_MAGIC_32  0xFEEDFACE
#define MACHO_MAGIC_64  0xFEEDFACF
#define MACHO_MAGIC_FAT 0xCAFEBABE

typedef struct macho_header_t {
	uint32_t magic;
	uint32_t cputype;
	uint32_t cpusubtype;
	uint32_t filetype;
	uint32_t ncmds;
	uint32_t sizeofcmds;
	uint32_t flags;
} macho_header_t;

typedef struct macho_t {
	uint8_t* data;
	uint32_t size;
	uint32_t offset;
	uint32_t command_count;
	uint32_t segment_count;
	uint32_t symtab_count;
	macho_header_t* header;
	macho_symtab_t** symtabs;
	macho_command_t** commands;
	macho_segment_t** segments;
} macho_t;

/*
 * Mach-O Functions
 */
macho_t* macho_create();
macho_t* macho_open(const char* path);
macho_t* macho_load(unsigned char* data, uint32_t size);
void macho_debug(macho_t* macho);
void macho_free(macho_t* macho);

uint32_t macho_lookup(macho_t* macho, const char* sym);
macho_segment_t* macho_get_segment(macho_t* macho, const char* segment);
macho_section_t* macho_get_section(macho_t* macho, const char* segment, const char* section);
void macho_list_symbols(macho_t* macho, void (*print_func)(const char*, uint32_t, void*), void* userdata);


int macho_handle_command(macho_t* macho, macho_command_t* command);

/*
 * Mach-O Header Functions
 */
macho_header_t* macho_header_create();
macho_header_t* macho_header_load(macho_t* macho);
void macho_header_debug(macho_t* macho);
void macho_header_free(macho_header_t* header);

/*
 * Mach-O Commands Functions
 */
macho_command_t** macho_commands_create(uint32_t count);
macho_command_t** macho_commands_load(macho_t* macho);
void macho_commands_debug(macho_t* macho);
void macho_commands_free(macho_command_t** commands);

/*
 * Mach-O Segments Functions
 */
macho_segment_t** macho_segments_create(uint32_t count);
macho_segment_t** macho_segments_load(macho_t* macho);
void macho_segments_debug(macho_t* macho);
void macho_segments_free(macho_segment_t** segments);

/*
 * Mach-O Symtab Functions
 */
macho_symtab_t** macho_symtabs_create(uint32_t count);
macho_symtab_t** macho_symtabs_load(macho_t* macho);
void macho_symtabs_debug(macho_t* macho);
void macho_symtabs_free(macho_symtab_t** symtabs);

/*
 * Mach-O Sections Functions
 */
macho_section_t** macho_sections_create(uint32_t count);
macho_section_t** macho_sections_load(macho_t* macho, macho_segment_t* segment);
void macho_sections_debug(macho_section_t** sections);
void macho_sections_free(macho_section_t** sections);

#endif /* MACHO_H_ */
