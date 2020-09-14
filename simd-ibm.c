#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <inttypes.h>
#include <immintrin.h>
#include <linux/limits.h>

#include "defs.h"
#include "init.h"
#include "print.h"

#include "avx2/simd-ai-epx8.h"
#include "avx2/simd-ai-epx16.h"
#include "avx2/simd-ai-epx32.h"
#include "avx2/simd-ai-epx64.h"

void* benchmark_thread(void *arg) {

	for (;;) {
		usleep(1000000);
		break;
	}

	return NULL;
}

int main( int argc, char const *argv[] ) {

	make_inits();

	// single thread benchmarks execution
	fprintf( stream, "SIMD Arithmetic Instructions Single-Threaded Benchmark start . . . \n\n" );
	printf( "\nSIMD Arithmetic Instructions Single-Threaded Benchmark start . . . \n\n");

	total_time = 0.0;
	total_tps = 0.0;

	fprintf( stream, "AVX2:\t   ASM INSTR\tINTRINSIC FUNC CALL\t TOTAL EVAL TIME\t PER 1 CYCLE\t OPERAT SPEED\n" );
	printf( "AVX2:\t   ASM INSTR\tINTRINSIC FUNC CALL\t TOTAL EVAL TIME\t PER 1 CYCLE\t OPERAT SPEED\n" );

	avx2_simd_ai_epx8_bm();
	avx2_simd_ai_epx16_bm();
	avx2_simd_ai_epx32_bm();
	avx2_simd_ai_epx64_bm();

	fprintf( stream, "\nSIMD Arithmetic Instructions Single-Threaded Benchmark value\t\t [ SIMD-AI-ST-BM   %8i ]\n\n", (int32_t)round( total_tps ) );
	printf("\nSIMD Arithmetic Instructions Single-Threaded Benchmark value\t\t [ SIMD-AI-ST-BM   %8i ]\n\n", (int32_t)round( total_tps ) );

	// multi-threaded benchmarks execution
	fprintf( stream, "SIMD Arithmetic Instructions Multi-Threaded Benchmark start . . . \n\n" );
	printf( "\nSIMD Arithmetic Instructions Multi-Threaded Benchmark start . . . \n\n");

	total_time = 0.0;
	total_tps = 0.0;

	fprintf( stream, "AVX2:\t   ASM INSTR\tINTRINSIC FUNC CALL\t TOTAL EVAL TIME\t PER 1 CYCLE\t OPERAT SPEED\n" );
	printf( "AVX2:\t   ASM INSTR\tINTRINSIC FUNC CALL\t TOTAL EVAL TIME\t PER 1 CYCLE\t OPERAT SPEED\n" );

	// threads attributes initialization
	pthread_attr_t attr;
	struct sched_param param;
	int fifo_max_prio;

	result = pthread_attr_init( &attr );
	if ( result != 0 ) perror( "pthread_attr_init() error" );

	pthread_attr_setinheritsched( &attr, PTHREAD_EXPLICIT_SCHED );
	pthread_attr_setschedpolicy( &attr, SCHED_FIFO );
	fifo_max_prio = sched_get_priority_max( SCHED_FIFO );
	param.sched_priority = fifo_max_prio;
	pthread_attr_setschedparam( &attr, &param );

	// size_t stack_size = 0;
	// pthread_attr_getstacksize( &attr, &stack_size );
	// stack_size *= 4;
	// pthread_attr_setstacksize( &attr, stack_size );

	// create new threads
	for (int i = 0; i < threads_count; ++i)	{
		result = pthread_create( &threads[i], &attr, benchmark_thread, NULL );
		if ( result != 0 ) perror( "pthread_create() error" );
	}

	// destroy thread attribute object
	result = pthread_attr_destroy( &attr );
	if ( result != 0 ) perror( "pthread_attr_destroy() error" );

	// wait for thread finish
	for (int i = 0; i < threads_count; ++i)	{
		result = pthread_join( threads[i], NULL );
		if ( result != 0 ) perror( "pthread_join() error" );
	}

	fprintf( stream, "\nSIMD Arithmetic Instructions Multi-Threaded Benchmark value\t\t[ SIMD-AI-MT-BM   %8i ]\n\n", (int32_t)round( total_tps ) );
	printf("\nSIMD Arithmetic Instructions Multi-Threaded Benchmark value\t\t[ SIMD-AI-MT-BM   %8i ]\n\n", (int32_t)round( total_tps ) );

	make_finits();

	exit(EXIT_SUCCESS);
}