#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <inttypes.h>
#include <immintrin.h>
#include <sys/prctl.h>
#include <sys/sysinfo.h>
#include <linux/limits.h>

#include "init.h"
#include "benchmarks.h"

int main( int argc, char const *argv[] ) {

	make_inits();

	make_st_banchmarks();

	make_mt_banchmarks();

	make_finits();

	exit(EXIT_SUCCESS);
}
