#include <libhackrf/hackrf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define FREQ  100400000


hackrf_device* device = NULL;

unsigned char* mbuffer = "abcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdef";

void init_hackrf()
{
	hackrf_init();
	hackrf_open(&device);

	hackrf_set_sample_rate(device, 2000000);
	hackrf_set_baseband_filter_bandwidth(device, 2000000*0.75);
	hackrf_set_freq(device, FREQ);
	hackrf_set_txvga_gain(device, 20);
	hackrf_set_lna_gain(device, 28);
	hackrf_set_amp_enable(device, 0);

	printf("HACKRF init done.\n");
}

int _hackrf_tx_callback(hackrf_transfer *transfer) {
	printf("transfer->valid_length is %d\n", transfer->valid_length);
	// memcpy(transfer->buffer,mbuffer,transfer->valid_length);
	if (strlen(mbuffer) >= transfer->valid_length) {
		printf("send txt len overflow!\n");
	}
	memcpy(transfer->buffer,mbuffer,strlen(mbuffer));
	printf("HACKRF send finish.%s\n", transfer->buffer);
	return 0;
}

int main(void) 
{
	init_hackrf();
	hackrf_start_tx(device, _hackrf_tx_callback, NULL);
	return EXIT_SUCCESS;
}
