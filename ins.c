#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FIELD(x,y,z) { \
	.name = x, \
	.of = y, \
	.mask = z },

#define FIELD_END \
	{ .name = NULL}}},

#define FIELD_START(n) \
	{ \
		.name = #n, \
		.f = (struct field[]){

struct field {
	const char* name;
	const int of;
	const int mask;
};

struct field_group {
	const char *name;
	const struct field *f;
};

static const struct field_group fields[] = {

	FIELD_START(ctrl)
	FIELD("CONTROLLE_RESET",0,1)
	FIELD("FIFO_RESET",1,1)
	FIELD("DMA_RESET",2,1)
	FIELD("INT_ENABLE",4,1)
	FIELD("DMA_ENABLE",5,1)
	FIELD("READ_WAIT",6,1)
	FIELD("SEND_IRQ_RESPONSE",7,1)
	FIELD("ABORT_READ_DATA",8,1)
	FIELD("SEND_CCSD",9,1)
	FIELD("SEND_AUTO_STOP_CCSD",10,1)
	FIELD("CEATA_DEVICE_INTERRUPT_STATUS", 11,1)
	FIELD("ENABLED_OD_PULLUP", 24,1)
	FIELD("USE INTERNAL DMAC", 25,1)
	FIELD_END

	FIELD_START(idsts)
	FIELD("TI", 0, 1)
	FIELD("RI", 1,1)
	FIELD("FBE", 2,1)
	FIELD("DU",4,1)
	FIELD("CES",5,1)
	FIELD("NIS",8,1)
	FIELD("AIS",9,1)
	FIELD("EB",10,3)
	FIELD("FSM",13,4)
	FIELD_END

	FIELD_START(cmd)
	FIELD("CMD_INDEX" , 0, 6)
	FIELD("RESPONSE_EXPECT" , 6, 1)
	FIELD("RESPONSE_LENGTH" , 7, 1)
	FIELD("CHECK_RESPONSE_CRC" , 8, 1)
	FIELD("DATA_EXPECTED" , 9, 1)
	FIELD("READ/WRITE", 10, 1)
	FIELD("TRANSFER_MODE", 11, 1)
	FIELD("SEND_AUTO_STOP", 12, 1)
	FIELD("WAIT_PRVDATA_COMPLETE" , 13, 1)
	FIELD("STOP_ABORT_CMD" , 14, 1)
	FIELD("SEND_INIT", 15, 1)
	FIELD("CARD_NUMBER", 16, 5)
	FIELD("UPDATE_CLOCK_REG_ONLY" , 21, 1)
	FIELD("READ_CEATA_DEV", 22, 1)
	FIELD("CCS_EXPECTTEDS", 23, 1)
	FIELD("ENABLE_BOOT", 24, 1)
	FIELD("EXPECT_BOOT_ACK", 25, 1)
	FIELD("DISABLED BOOT", 26, 1)
	FIELD("BOOT_MODE", 27, 1)
	FIELD("START_CMD", 31, 1)
	FIELD_END

	{ NULL, NULL }
};


int main(int n, char** a)
{

	const struct field_group *fg = fields;
	const struct field *f = NULL;
	unsigned int num_t;
	unsigned int num, ar;

	if(n==3){

		while( fg->name && strcmp(fg->name, a[1]) != 0 )
			fg++;

		if(!fg->name)
			return printf("Not found %s.\n", a[1]), 1;

		f = fg->f;

		sscanf(a[2],"%x",&num);
		
		printf("Input [%08X] Using %s.\n", num, fg->name);

		while(f->name){
			num_t = num;
			num_t >>= f->of;
			num_t &= (1 << f->mask) - 1;
			printf("%s : %08X\n", f->name, num_t);
			f++;
		}


	}
	else
		for(;fg->name;fg++)
			printf("Options for %s.\n", fg->name);

	return 0;	

}
