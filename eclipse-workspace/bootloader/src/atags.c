
#include "atags.h"
#include "atag_defs.h"

void initAtags( void )
{
	uint32_t * tgs = (uint32_t *)0x10000000;

	// TAG_CORE
	struct tag_header * hdr = (struct tag_header *)tgs;
	hdr->tag = ATAG_CORE;
	hdr->size = (sizeof(struct tag_header)) >> 2;
	tgs += (sizeof(struct tag_header) >> 2);

	/*
	struct tag_core * tagCore = (struct tag_core *)tgs;
	tagCore->flags = 0;
	tagCore->pagesize = 0;
	tagCore->rootdev  = 0;
	hdr->size += (sizeof(struct tag_core) >> 2);
	tgs += (sizeof(struct tag_core) >> 2);
	*/

	// TAG_MEMORY
	hdr = (struct tag_header *)tgs;
	hdr->tag = ATAG_MEM;
	hdr->size += (sizeof(struct tag_header) >> 2);
	tgs += (sizeof(struct tag_header) >> 2);

	struct tag_mem32 * tagMem = (struct tag_mem32 *)tgs;
	tagMem->start = 0xD0000000;
	tagMem->size  = 8000000;
	tgs += (sizeof(struct tag_mem32) >> 2);

	// TAG_NONE
	hdr = (struct tag_header *)tgs;
	hdr->tag = ATAG_NONE;
	hdr->size += 0;
}

uint32_t * atags( void )
{
	uint32_t * res = (uint32_t *)0x10000000;
	return res;
}


