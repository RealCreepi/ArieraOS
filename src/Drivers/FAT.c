#include "FAT.h"

typedef struct fat12
{
	unsigned char 		bootjmp[3];
	unsigned char 		oem_name[8];
	unsigned short      bytes_per_sector;
	unsigned char		sectors_per_cluster;
	unsigned short		reserved_sector_count;
	unsigned char		table_count;
	unsigned short		root_entry_count;
	unsigned short		total_sectors_16;
	unsigned char		media_type;
	unsigned short		table_size_16;
	unsigned short		sectors_per_track;
	unsigned short		head_side_count;
	unsigned int 		hidden_sector_count;
	unsigned int 		total_sectors_32;
 
	unsigned char		extended_section[54];
 
}__attribute__((packed)) fat12_t;

fat12_t* initDevice() {
    fat12_t* FS;

	return FS;
}