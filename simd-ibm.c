#include <stdio.h>
#include <time.h>
#include <string.h>
#include <inttypes.h>
#include <immintrin.h>

#include "defs.h"
#include "print.h"

int main( int argc, char const *argv[] ) {
	uint64_t i;
	double total_time = 0.0;
	const uint64_t cycles_count = 1000000000;

	printf( "SIMD Instructions Benchmark v0.1\n" );
	if ( system( "grep 'model name' /proc/cpuinfo | uniq | awk '/^model name/{$1=$2=$3=\"\";print $0}' > processor" ) != 0 )
		perror( "error due system call" );
	if ( system( "inxi -CfMxx -c 23" ) != 0 )
		perror( "error due system call" );
	if ( system( "lscpu >> processor" ) != 0 )
		perror( "error due system call" );
	printf("AVX2:\t   ASM INSTR\tINTRINSIC FUNC CALL\t TOTAL EVAL TIME\t PER 1 CYCLE\t OPERAT SPEED\n");

	__m256i a, v;

	#include "avx2/simd-ai-epx8.h"
	#include "avx2/simd-ai-epx16.h"
	#include "avx2/simd-ai-epx32.h"
	#include "avx2/simd-ai-epx64.h"

	printf("\t   SIMD Arithmetic Instructions Benchmark value (simd-aibm)\t~%5.1lf GT/sec\n", total_tps);

	return 0;
}