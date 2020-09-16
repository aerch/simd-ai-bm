#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <inttypes.h>
#include <immintrin.h>
#include <sys/prctl.h>
#include <linux/limits.h>

#include "defs.h"
#include "init.h"
#include "print.h"

#include "avx2/simd-ai-epx8.h"
#include "avx2/simd-ai-epx16.h"
#include "avx2/simd-ai-epx32.h"
#include "avx2/simd-ai-epx64.h"

const uint8_t instr_count = 2;
char instructions[ instr_count + 1 ][ 100 ] = {
	"AVX2 64-bit Integer Arithmetic Instructions",
	"vpaddq\t_mm256_add_epi64()",
	"vpsubq\t_mm256_sub_epi64()"
};

typedef struct thread_data {
	pthread_t	th;
	uint32_t	tid;
	bool		thread_active;

	uint32_t	instruction;

	uint64_t	cycles_count;
} thread_data_t;

void* avx2_ai_epx64_bm_thread( void *arg ) {
	uint32_t i;
	// uint32_t cx = 0;
	thread_data_t *td = (thread_data_t*)arg;
	// printf( "avx2_ai_epx64_bm_thread%u started\n", td->tid );

	char name[ 25 ];
	sprintf( name, "avx2aiep64th%u", td->tid );
	prctl( PR_SET_NAME, name );

	int64_t ALIGN32 qi[ 4 ] = { 8, 7, 6, 5 };
	int64_t ALIGN32 qa[ 4 ] = { 1, 2, 3, 4 };

	while ( td->thread_active ) {

		pthread_mutex_lock( &lock );
		while ( (td->instruction == 0) && td->thread_active )
			pthread_cond_wait( &start, &lock );
		pthread_mutex_unlock( &lock );

		if ( !td->thread_active ) break;

		a = _mm256_load_si256( (const __m256i *)qa );

		switch ( td->instruction ) {

			case 1: // add vectors of 4 64-bit signed integers at a cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					v = _mm256_load_si256( (const __m256i *)qi );
					v = _mm256_add_epi64( v, a );
					_mm256_store_si256( (__m256i *)qi, v );
				}
				break;

			case 2: // sub vectors of 4 64-bit signed integers at a cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					v = _mm256_load_si256( (const __m256i *)qi );
					v = _mm256_sub_epi64( v, a );
					_mm256_store_si256( (__m256i *)qi, v );
				}
				break;

			default:
				// printf( "avx2_ai_epx64_bm_thread%u havn't instruction\n", td->tid );
				break;

		}

		pthread_mutex_lock( &lock );
		td->instruction = 0;
		SET_BIT( active_threads_flag, td->tid, 0 );
		pthread_cond_signal( &stop );
		// printf( "avx2_ai_epx64_bm_thread%u finish cycle #%u\n", td->tid, ++cx );
		pthread_mutex_unlock( &lock );

	}

	// printf( "avx2_ai_epx64_bm_thread%u stopped\n", td->tid );
	return NULL;
}

int main( int argc, char const *argv[] ) {

	make_inits();


	// single thread benchmarks execution
	fprintf( stream, "SIMD Arithmetic Instructions Single-Threaded Benchmark start ...\n\n" );
	printf( BLUE "SIMD Arithmetic Instructions Single-Threaded Benchmark start ..." OFF "\n" );

	total_tps = 0.0;

	fprintf( stream, "AVX2:\t   ASM INSTR\tINTRINSIC FUNC CALL\tTOTAL EVALUATE TIME\tPER ONE CYCLE\tOPERATE SPEED\n" );
	printf( BLUE "AVX2:" OFF WHITE "\t   ASM INSTR\tINTRINSIC FUNC CALL\tTOTAL EVALUATE TIME\tPER ONE CYCLE\tOPERATE SPEED\n" OFF );

	avx2_simd_ai_epx8_bm();
	avx2_simd_ai_epx16_bm();
	avx2_simd_ai_epx32_bm();
	avx2_simd_ai_epx64_bm();

	fprintf( stream, "\nSIMD Arithmetic Instructions Single-Threaded Benchmark value\t\t [ SIMD-AI-ST-BM   %8i ]\n\n", (int32_t)round( total_tps ) );
	printf( BLUE "SIMD Arithmetic Instructions Single-Threaded Benchmark value             [ SIMD-AI-ST-BM   %8i ]" OFF "\n\n", (int32_t)round( total_tps ) );


	// multi-threaded benchmarks execution
	fprintf( stream, "SIMD Arithmetic Instructions Multi-Threaded Benchmark start ...\n\n" );
	printf( BLUE "SIMD Arithmetic Instructions Multi-Threaded Benchmark start ..." OFF "\n" );

	total_tps = 0.0;

	fprintf( stream, "AVX2:\t   ASM INSTR\tINTRINSIC FUNC CALL\tTOTAL EVALUATE TIME\tPER ONE CYCLE\tOPERATE SPEED\n" );
	printf( BLUE "AVX2:" OFF WHITE "\t   ASM INSTR\tINTRINSIC FUNC CALL\tTOTAL EVALUATE TIME\tPER ONE CYCLE\tOPERATE SPEED\n" OFF );

	fprintf( stream, "\n\tSIMD Arithmetic instructions with 256-bit vectors of 64-bit integers (measured by %i MCycles)\n", (int32_t)(cycles_count/1e6) );
	printf( BLUE "      SIMD Arithmetic instructions with 256-bit vectors of 64-bit integers (measured by %i MCycles)\n" OFF, (int32_t)(cycles_count/1e6) );

	uint32_t i, c;
	const uint8_t threads_count = 8;
	thread_data_t td[ threads_count ];
	active_threads_flag = 0;

	// threads attributes initialization
	pthread_attr_t attr;

	result = pthread_attr_init( &attr );
	if ( result != 0 ) perror( "pthread_attr_init() error" );

	// struct sched_param param;
	// int fifo_max_prio;
	// pthread_attr_setinheritsched( &attr, PTHREAD_EXPLICIT_SCHED );
	// pthread_attr_setschedpolicy( &attr, SCHED_FIFO );
	// fifo_max_prio = sched_get_priority_max( SCHED_FIFO );
	// param.sched_priority = fifo_max_prio;
	// pthread_attr_setschedparam( &attr, &param );

	// size_t stack_size = 0;
	// pthread_attr_getstacksize( &attr, &stack_size );
	// pthread_attr_setstacksize( &attr, stack_size * 16 );

	pthread_mutex_init( &lock, NULL );
	pthread_cond_init( &start, NULL );
	pthread_cond_init( &stop, NULL );

	// init threads data
	memset( td, 0x00, threads_count * sizeof(thread_data_t) );
	for ( i = 0; i < threads_count; i++ )	{
		td[i].tid = i;
		td[i].cycles_count = cycles_count;
		td[i].thread_active = true;
		td[i].instruction = 0;
	}

	// create threads
	for ( i = 0; i < threads_count; i++ ) {
		result = pthread_create( &td[i].th, &attr, avx2_ai_epx64_bm_thread, &td[i] );
		if ( result != 0 ) perror( "pthread_create() error" );
	}

	// destroy thread attribute object
	result = pthread_attr_destroy( &attr );
	if ( result != 0 ) perror( "pthread_attr_destroy() error" );

	// starting current multi-threaded benchmark
	for ( c = 1; c <= instr_count; c++ ) {
		_BMARK_ON_;
		pthread_mutex_lock( &lock );
		for ( i = 0; i < threads_count; i++ ) {
			td[i].instruction = 1;
			SET_BIT( active_threads_flag, i, 1 );
		}
		pthread_cond_broadcast( &start );
		while ( active_threads_flag )
			pthread_cond_wait( &stop, &lock );
		pthread_mutex_unlock( &lock );
		_BMARK_OFF( total_time );
		print_results( instructions[ c ], 4, cycles_count*threads_count, total_time );
	}

	// finish threads
	pthread_mutex_lock( &lock );
	for ( i = 0; i < threads_count; i++ ) {
		td[i].thread_active = false;
		td[i].instruction = 0;
	}
	pthread_cond_broadcast( &start );
	pthread_mutex_unlock( &lock );

	// wait for thread finish
	for ( i = 0; i < threads_count; i++ ) {
		result = pthread_join( td[i].th, NULL );
		if ( result != 0 ) perror( "pthread_join() error" );
	}

	fprintf( stream, "\nSIMD Arithmetic Instructions Multi-Threaded Benchmark value\t\t[ SIMD-AI-MT-BM   %8i ]\n\n", (int32_t)round( total_tps ) );
	printf( BLUE "SIMD Arithmetic Instructions Multi-Threaded Benchmark value              [ SIMD-AI-MT-BM   %8i ]" OFF "\n\n", (int32_t)round( total_tps ) );

	make_finits();

	exit(EXIT_SUCCESS);
}