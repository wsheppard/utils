#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FIELDN(x,y) { \
	.name = x, \
	.of = -1,\
	.mask = y },

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
	int of;
	const int mask;
};

struct field_group {
	const char *name;
	struct field *f;
};

static struct field_group fields[] = {

	FIELD_START(up)
		FIELD("DATA1",6,1)
		FIELD("CMD1",5,1)
		FIELD("COM1",4,1)
		FIELD("DATA0",3,1)
		FIELD("CMD0",2,1)
		FIELD("COM0",1,1)
	FIELD_END

	FIELD_START(drv)
	FIELD("MSHC1",6,2)
	FIELD("MSHC0",4,2)
	FIELD_END

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

	FIELD_START(status)
	FIELD("FIFO_RX_WATERMARK",0,1)
	FIELD("FIFO_TX_WATER",1,1)
	FIELD("FIFO_EMPTY",2,1)
	FIELD("FIFO_FULL",3,1)
	FIELD("COMMAND_FSM_STATES",4,4)
	FIELD("DATA_3_STATUS",8,1)
	FIELD("DATA_BUSY",9,1)
	FIELD("DATA_STATE_MC_BUSY",10,1)
	FIELD("RESPONSE_INDEX",11,6)
	FIELD("FIFO_COUNT",17,13)
	FIELD_END

	FIELD_START(bmod)
	FIELD("SWR",0,1)
	FIELD("FB",1,1)
	FIELD("DSL",2,5)
	FIELD("DE",7,1)
	FIELD("PBL",8,3)
	FIELD_END

	FIELD_START(des0)
	FIELD("OWN",31,1)
	FIELD("CES",30,1)
	FIELD("ER",5,1)
	FIELD("CH",4,1)
	FIELD("FS",3,1)
	FIELD("LD",2,1)
	FIELD("DIC",1,1)
	FIELD_END

	FIELD_START(des1)
	FIELD("BUFFER1SIZE",0,13)
	FIELD("BUFFER2SIZE",13,13)
	FIELD_END


	FIELD_START(fifoth)
	FIELD("TX_WATERMARK",0,12)
	FIELD("RX_WATERMARK",16,12)
	FIELD("DMA MULTIPLE", 28, 3)
	FIELD_END

	FIELD_START(irqs)
	FIELD("cd (card detect)", 0,1)
	FIELD("re",1,1)
	FIELD("cd (command done)",2,1)
	FIELD("dto",3,1)
	FIELD("txdr",4,1)
	FIELD("rxdr",5,1)
	FIELD("rcrc",6,1)
	FIELD("dcrc",7,1)
	FIELD("rto/bar",8,1)
	FIELD("bds",9,1)
	FIELD("hto",10,1)
	FIELD("frun",11,1)
	FIELD("hle",12,1)
	FIELD("sbe",13,1)
	FIELD("acd",14,1)
	FIELD("ebe",15,1)
	FIELD("sdio",16,1)
	FIELD_END

	FIELD_START(pads)
	FIELD("MSHC0",10,1)
	FIELD("MSHC1",11,1)
	FIELD_END

	FIELD_START(dwc)
		FIELDN("curmode",1)
		FIELDN("modemismatch",1)
		FIELDN("otgintr",1)
		FIELDN("sofintr",1)
		FIELDN("rxstsqlvl",1)
		FIELDN("nptxfempty",1)
		FIELDN("ginnakeff",1)
		FIELDN("goutnakeff",1)
		FIELDN("ulpickint",1)
		FIELDN("i2cintr",1)
		FIELDN("erlysuspend",1)
		FIELDN("usbsuspend",1)
		FIELDN("usbreset",1)
		FIELDN("enumdone",1)
		FIELDN("isooutdrop",1)
		FIELDN("eopframe",1)
		FIELDN("restoredone",1)
		FIELDN("epmismatch",1)
		FIELDN("inepint",1)
		FIELDN("outepintr",1)
		FIELDN("incomplisoin",1)
		FIELDN("incomplisoout",1)
		FIELDN("fetsusp",1)
		FIELDN("resetdet",1)
		FIELDN("portintr",1)
		FIELDN("hcintr",1)
		FIELDN("ptxfempty",1)
		FIELDN("lpmtranrcvd",1)
		FIELDN("conidstschng",1)
		FIELDN("disconnect",1)
		FIELDN("sessreqintr",1)
		FIELDN("wkupintr",1)
	FIELD_END

	{ NULL, NULL }
};


int main(int n, char** a)
{

	struct field_group *fg = fields;
	struct field *f = NULL;
	const char *name;
	unsigned int num_t;
	unsigned int num, ar;
	int x;

	/* Process aggregate ones */
	for( fg = fields; fg->name; fg++ )
	{

		x=0;

		for( f = fg->f; f->name; f++ )
		{
			if(f->of != -1)
				continue;

			if(f == fg->f)
				f->of = 0;
			else
			{
				f->of = f[-1].of + f[-1].mask;
				//printf("Set %s[%d]\n", f->name, f->of);
			}
		}

	}

	fg = fields;

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
			
			if(!num_t)
				printf("%s[%d-%d]: %d [0x%X] \n", f->name, f->of + f->mask - 1, f->of, num_t, num_t);
			else
				printf("\033[1m\033[37m%s[%d-%d]: %d [0x%X] \033[0m\n", f->name, f->of + f->mask - 1, f->of, num_t, num_t);

			

			f++;
		}


	}
	else
		for(;fg->name;fg++)
			printf("Options for %s.\n", fg->name);

	return 0;	

}
