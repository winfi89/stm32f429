
#include "dev_tree_handler.h"
#include "dev_tree.h"

void * devTreeWrite( void )
{
	extern uint8_t dev_tree[];
	extern int dev_tree_sz;
	uint8_t * tgs = (uint8_t *)0x10000000;
	int i;
	for ( i=0; i<dev_tree_sz; i++ )
		tgs[i] = dev_tree[i];

	return tgs;
}

