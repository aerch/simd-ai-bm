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

	printf("\t   SIMD Arithmetic instructions with 256-bit vectors of 8-bit integers (measured by %i MCycles)\n", (int32_t)(cycles_count/1e6));

	int8_t ALIGN bi[ 32 ] = { 8, 7, 6, 5, 4, 3, 2, 1, 8, 7, 6, 5, 4, 3, 2, 1, 8, 7, 6, 5, 4, 3, 2, 1, 8, 7, 6, 5, 4, 3, 2, 1 };
	int8_t ALIGN ba[ 32 ] = { 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8 };

	// add vectors of 32 8-bit signed integers at a cycle
	_BMARK_ON_;
	for ( i = 0; i < cycles_count; i++ ) {
		v = _mm256_load_si256( (const __m256i *)bi );
		a = _mm256_load_si256( (const __m256i *)ba );
		v = _mm256_add_epi8( v, a );
		_mm256_store_si256( (__m256i *)bi, v );
	}
	_BMARK_OFF( total_time );
	print_results_epi8( "vpaddb\t_mm256_add_epi8()", 32, bi, cycles_count, total_time );

	// adds vectors of 32 8-bit signed integers at a cycle
	_BMARK_ON_;
	for ( i = 0; i < cycles_count; i++ ) {
		v = _mm256_load_si256( (const __m256i *)bi );
		a = _mm256_load_si256( (const __m256i *)ba );
		v = _mm256_adds_epi8( v, a );
		_mm256_store_si256( (__m256i *)bi, v );
	}
	_BMARK_OFF( total_time );
	print_results_epi8( "vpaddsb\t_mm256_adds_epi8()", 32, bi, cycles_count, total_time );

	// adds vectors of 32 8-bit unsigned integers at a cycle
	_BMARK_ON_;
	for ( i = 0; i < cycles_count; i++ ) {
		v = _mm256_load_si256( (const __m256i *)bi );
		a = _mm256_load_si256( (const __m256i *)ba );
		v = _mm256_adds_epu8( v, a );
		_mm256_store_si256( (__m256i *)bi, v );
	}
	_BMARK_OFF( total_time );
	print_results_epi8( "vpaddusb\t_mm256_adds_epu8()", 32, bi, cycles_count, total_time );

	// sub vectors of 32 8-bit signed integers at a cycle
	_BMARK_ON_;
	for ( i = 0; i < cycles_count; i++ ) {
		v = _mm256_load_si256( (const __m256i *)bi );
		a = _mm256_load_si256( (const __m256i *)ba );
		v = _mm256_sub_epi8( v, a );
		_mm256_store_si256( (__m256i *)bi, v );
	}
	_BMARK_OFF( total_time );
	print_results_epi8( "vpsubb\t_mm256_sub_epi8()", 32, bi, cycles_count, total_time );

	// subs vectors of 32 8-bit signed integers at a cycle
	_BMARK_ON_;
	for ( i = 0; i < cycles_count; i++ ) {
		v = _mm256_load_si256( (const __m256i *)bi );
		a = _mm256_load_si256( (const __m256i *)ba );
		v = _mm256_subs_epi8( v, a );
		_mm256_store_si256( (__m256i *)bi, v );
	}
	_BMARK_OFF( total_time );
	print_results_epi8( "vpsubsb\t_mm256_adds_epi8()", 32, bi, cycles_count, total_time );

	// subs vectors of 32 8-bit unsigned integers at a cycle
	_BMARK_ON_;
	for ( i = 0; i < cycles_count; i++ ) {
		v = _mm256_load_si256( (const __m256i *)bi );
		a = _mm256_load_si256( (const __m256i *)ba );
		v = _mm256_subs_epu8( v, a );
		_mm256_store_si256( (__m256i *)bi, v );
	}
	_BMARK_OFF( total_time );
	print_results_epi8( "vpsubusb\t_mm256_adds_epu8()", 32, bi, cycles_count, total_time );

	// sign vectors of 32 8-bit signed integers at a cycle
	_BMARK_ON_;
	for ( i = 0; i < cycles_count; i++ ) {
		v = _mm256_load_si256( (const __m256i *)bi );
		a = _mm256_load_si256( (const __m256i *)ba );
		v = _mm256_sign_epi8( v, a );
		_mm256_store_si256( (__m256i *)bi, v );
	}
	_BMARK_OFF( total_time );
	print_results_epi8( "vpsignb\t_mm256_sign_epi8()", 32, bi, cycles_count, total_time );

	// subs vectors of 32 8-bit unsigned integers at a cycle
	_BMARK_ON_;
	for ( i = 0; i < cycles_count; i++ ) {
		v = _mm256_load_si256( (const __m256i *)bi );
		a = _mm256_load_si256( (const __m256i *)ba );
		v = _mm256_sad_epu8( v, a );
		_mm256_store_si256( (__m256i *)bi, v );
	}
	_BMARK_OFF( total_time );
	print_results_epi8( "vpsadbw\t_mm256_sad_epu8()", 32, bi, cycles_count, total_time );


	printf("\t   SIMD Arithmetic instructions with 256-bit vectors of 16-bit integers (measured by %i MCycles)\n", (int32_t)(cycles_count/1e6));

	int16_t ALIGN wi[ 16 ] = { 8, 7, 6, 5, 4, 3, 2, 1, 8, 7, 6, 5, 4, 3, 2, 1 };
	int16_t ALIGN wa[ 16 ] = { 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8 };

	// add vectors of 16 16-bit signed integers at a cycle
	_BMARK_ON_;
	for ( i = 0; i < cycles_count; i++ ) {
		v = _mm256_load_si256( (const __m256i *)wi );
		a = _mm256_load_si256( (const __m256i *)wa );
		v = _mm256_add_epi16( v, a );
		_mm256_store_si256( (__m256i *)wi, v );
	}
	_BMARK_OFF( total_time );
	print_results_epi16( "vpaddw\t_mm256_add_epi16()", 16, wi, cycles_count, total_time );

	// adds vectors of 16 16-bit signed integers at a cycle
	_BMARK_ON_;
	for ( i = 0; i < cycles_count; i++ ) {
		v = _mm256_load_si256( (const __m256i *)wi );
		a = _mm256_load_si256( (const __m256i *)wa );
		v = _mm256_adds_epi16( v, a );
		_mm256_store_si256( (__m256i *)wi, v );
	}
	_BMARK_OFF( total_time );
	print_results_epi16( "vpaddsw\t_mm256_adds_epi16()", 16, wi, cycles_count, total_time );

	// adds vectors of 16 16-bit unsigned integers at a cycle
	_BMARK_ON_;
	for ( i = 0; i < cycles_count; i++ ) {
		v = _mm256_load_si256( (const __m256i *)wi );
		a = _mm256_load_si256( (const __m256i *)wa );
		v = _mm256_adds_epu16( v, a );
		_mm256_store_si256( (__m256i *)wi, v );
	}
	_BMARK_OFF( total_time );
	print_results_epi16( "vpaddusw\t_mm256_adds_epu16()", 16, wi, cycles_count, total_time );

	// hadd vectors of 16 16-bit signed integers at a cycle
	_BMARK_ON_;
	for ( i = 0; i < cycles_count; i++ ) {
		v = _mm256_load_si256( (const __m256i *)wi );
		a = _mm256_load_si256( (const __m256i *)wa );
		v = _mm256_hadd_epi16( v, a );
		_mm256_store_si256( (__m256i *)wi, v );
	}
	_BMARK_OFF( total_time );
	print_results_epi16( "vphaddw\t_mm256_hadd_epi16()", 16, wi, cycles_count, total_time );

	// hadds vectors of 16 16-bit signed integers at a cycle
	_BMARK_ON_;
	for ( i = 0; i < cycles_count; i++ ) {
		v = _mm256_load_si256( (const __m256i *)wi );
		a = _mm256_load_si256( (const __m256i *)wa );
		v = _mm256_hadds_epi16( v, a );
		_mm256_store_si256( (__m256i *)wi, v );
	}
	_BMARK_OFF( total_time );
	print_results_epi16( "vphaddsw\t_mm256_hadds_epi16()", 16, wi, cycles_count, total_time );

	// madd vectors of 16 16-bit signed integers at a cycle
	_BMARK_ON_;
	for ( i = 0; i < cycles_count; i++ ) {
		v = _mm256_load_si256( (const __m256i *)wi );
		a = _mm256_load_si256( (const __m256i *)wa );
		v = _mm256_madd_epi16( v, a );
		_mm256_store_si256( (__m256i *)wi, v );
	}
	_BMARK_OFF( total_time );
	print_results_epi16( "vpmaddwd\t_mm256_madd_epi16()", 16, wi, cycles_count, total_time );

	// maddubs vectors of 16 16-bit signed integers at a cycle
	_BMARK_ON_;
	for ( i = 0; i < cycles_count; i++ ) {
		v = _mm256_load_si256( (const __m256i *)wi );
		a = _mm256_load_si256( (const __m256i *)wa );
		v = _mm256_maddubs_epi16( v, a );
		_mm256_store_si256( (__m256i *)wi, v );
	}
	_BMARK_OFF( total_time );
	print_results_epi16( "vpmaddubsw\t_mm256_maddubs_epi16()", 16, wi, cycles_count, total_time );

	// sub vectors of 16 16-bit signed integers at a cycle
	_BMARK_ON_;
	for ( i = 0; i < cycles_count; i++ ) {
		v = _mm256_load_si256( (const __m256i *)wi );
		a = _mm256_load_si256( (const __m256i *)wa );
		v = _mm256_sub_epi16( v, a );
		_mm256_store_si256( (__m256i *)wi, v );
	}
	_BMARK_OFF( total_time );
	print_results_epi16( "vpsubw\t_mm256_sub_epi16()", 16, wi, cycles_count, total_time );

	// subs vectors of 16 16-bit signed integers at a cycle
	_BMARK_ON_;
	for ( i = 0; i < cycles_count; i++ ) {
		v = _mm256_load_si256( (const __m256i *)wi );
		a = _mm256_load_si256( (const __m256i *)wa );
		v = _mm256_subs_epi16( v, a );
		_mm256_store_si256( (__m256i *)wi, v );
	}
	_BMARK_OFF( total_time );
	print_results_epi16( "vpsubsw\t_mm256_subs_epi16()", 16, wi, cycles_count, total_time );

	// subs vectors of 16 16-bit unsigned integers at a cycle
	_BMARK_ON_;
	for ( i = 0; i < cycles_count; i++ ) {
		v = _mm256_load_si256( (const __m256i *)wi );
		a = _mm256_load_si256( (const __m256i *)wa );
		v = _mm256_subs_epu16( v, a );
		_mm256_store_si256( (__m256i *)wi, v );
	}
	_BMARK_OFF( total_time );
	print_results_epi16( "vpsubusw\t_mm256_subs_epu16()", 16, wi, cycles_count, total_time );

	// hsub vectors of 16 16-bit signed integers at a cycle
	_BMARK_ON_;
	for ( i = 0; i < cycles_count; i++ ) {
		v = _mm256_load_si256( (const __m256i *)wi );
		a = _mm256_load_si256( (const __m256i *)wa );
		v = _mm256_hsub_epi16( v, a );
		_mm256_store_si256( (__m256i *)wi, v );
	}
	_BMARK_OFF( total_time );
	print_results_epi16( "vphsubw\t_mm256_hsub_epi16()", 16, wi, cycles_count, total_time );

	// hsubs vectors of 16 16-bit signed integers at a cycle
	_BMARK_ON_;
	for ( i = 0; i < cycles_count; i++ ) {
		v = _mm256_load_si256( (const __m256i *)wi );
		a = _mm256_load_si256( (const __m256i *)wa );
		v = _mm256_hsubs_epi16( v, a );
		_mm256_store_si256( (__m256i *)wi, v );
	}
	_BMARK_OFF( total_time );
	print_results_epi16( "vphsubsw\t_mm256_hsubs_epi16()", 16, wi, cycles_count, total_time );

	// mulhi vectors of 16 16-bit signed integers at a cycle
	_BMARK_ON_;
	for ( i = 0; i < cycles_count; i++ ) {
		v = _mm256_load_si256( (const __m256i *)wi );
		a = _mm256_load_si256( (const __m256i *)wa );
		v = _mm256_mulhi_epi16( v, a );
		_mm256_store_si256( (__m256i *)wi, v );
	}
	_BMARK_OFF( total_time );
	print_results_epi16( "vpmulhw\t_mm256_mulhi_epi16()", 16, wi, cycles_count, total_time );

	// mullo vectors of 16 16-bit signed integers at a cycle
	_BMARK_ON_;
	for ( i = 0; i < cycles_count; i++ ) {
		v = _mm256_load_si256( (const __m256i *)wi );
		a = _mm256_load_si256( (const __m256i *)wa );
		v = _mm256_mullo_epi16( v, a );
		_mm256_store_si256( (__m256i *)wi, v );
	}
	_BMARK_OFF( total_time );
	print_results_epi16( "vpmullw\t_mm256_mullo_epi16()", 16, wi, cycles_count, total_time );

	// mulhrs vectors of 16 16-bit signed integers at a cycle
	_BMARK_ON_;
	for ( i = 0; i < cycles_count; i++ ) {
		v = _mm256_load_si256( (const __m256i *)wi );
		a = _mm256_load_si256( (const __m256i *)wa );
		v = _mm256_mulhrs_epi16( v, a );
		_mm256_store_si256( (__m256i *)wi, v );
	}
	_BMARK_OFF( total_time );
	print_results_epi16( "vpmulhrsw\t_mm256_mulhrs_epi16()", 16, wi, cycles_count, total_time );

	// mulhi vectors of 16 16-bit unsigned integers at a cycle
	_BMARK_ON_;
	for ( i = 0; i < cycles_count; i++ ) {
		v = _mm256_load_si256( (const __m256i *)wi );
		a = _mm256_load_si256( (const __m256i *)wa );
		v = _mm256_mulhi_epu16( v, a );
		_mm256_store_si256( (__m256i *)wi, v );
	}
	_BMARK_OFF( total_time );
	print_results_epi16( "vpmulhuw\t_mm256_mulhi_epu16()", 16, wi, cycles_count, total_time );

	// sign vectors of 16 16-bit signed integers at a cycle
	_BMARK_ON_;
	for ( i = 0; i < cycles_count; i++ ) {
		v = _mm256_load_si256( (const __m256i *)wi );
		a = _mm256_load_si256( (const __m256i *)wa );
		v = _mm256_sign_epi16( v, a );
		_mm256_store_si256( (__m256i *)wi, v );
	}
	_BMARK_OFF( total_time );
	print_results_epi16( "vpsignw\t_mm256_sign_epi16()", 16, wi, cycles_count, total_time );


	printf("\t   SIMD Arithmetic instructions with 256-bit vectors of 32-bit integers (measured by %i MCycles)\n", (int32_t)(cycles_count/1e6));

	int32_t ALIGN si[ 8 ] = { 8, 7, 6, 5, 4, 3, 2, 1 };
	int32_t ALIGN sa[ 8 ] = { 1, 2, 3, 4, 5, 6, 7, 8 };

	// add vectors of 8 32-bit signed integers at a cycle
	_BMARK_ON_;
	for ( i = 0; i < cycles_count; i++ ) {
		v = _mm256_load_si256( (const __m256i *)si );
		a = _mm256_load_si256( (const __m256i *)sa );
		v = _mm256_add_epi32( v, a );
		_mm256_store_si256( (__m256i *)si, v );
	}
	_BMARK_OFF( total_time );
	print_results_epi32( "vpaddd\t_mm256_add_epi32()", 8, si, cycles_count, total_time );

	// hadd vectors of 8 32-bit signed integers at a cycle
	_BMARK_ON_;
	for ( i = 0; i < cycles_count; i++ ) {
		v = _mm256_load_si256( (const __m256i *)si );
		a = _mm256_load_si256( (const __m256i *)sa );
		v = _mm256_hadd_epi32( v, a );
		_mm256_store_si256( (__m256i *)si, v );
	}
	_BMARK_OFF( total_time );
	print_results_epi32( "vphaddd\t_mm256_hadd_epi32()", 8, si, cycles_count, total_time );

	// sub vectors of 8 32-bit signed integers at a cycle
	_BMARK_ON_;
	for ( i = 0; i < cycles_count; i++ ) {
		v = _mm256_load_si256( (const __m256i *)si );
		a = _mm256_load_si256( (const __m256i *)sa );
		v = _mm256_sub_epi32( v, a );
		_mm256_store_si256( (__m256i *)si, v );
	}
	_BMARK_OFF( total_time );
	print_results_epi32( "vpsubd\t_mm256_sub_epi32()", 8, si, cycles_count, total_time );

	// hsub vectors of 8 32-bit signed integers at a cycle
	_BMARK_ON_;
	for ( i = 0; i < cycles_count; i++ ) {
		v = _mm256_load_si256( (const __m256i *)si );
		a = _mm256_load_si256( (const __m256i *)sa );
		v = _mm256_hsub_epi32( v, a );
		_mm256_store_si256( (__m256i *)si, v );
	}
	_BMARK_OFF( total_time );
	print_results_epi32( "vphsubd\t_mm256_hsub_epi32()", 8, si, cycles_count, total_time );

	// mul vectors of 8 32-bit signed integers at a cycle
	_BMARK_ON_;
	for ( i = 0; i < cycles_count; i++ ) {
		v = _mm256_load_si256( (const __m256i *)si );
		a = _mm256_load_si256( (const __m256i *)sa );
		v = _mm256_mul_epi32( v, a );
		_mm256_store_si256( (__m256i *)si, v );
	}
	_BMARK_OFF( total_time );
	print_results_epi32( "vpmuldq\t_mm256_mul_epi32()", 8, si, cycles_count, total_time );

	// mul vectors of 8 32-bit unsigned integers at a cycle
	_BMARK_ON_;
	for ( i = 0; i < cycles_count; i++ ) {
		v = _mm256_load_si256( (const __m256i *)si );
		a = _mm256_load_si256( (const __m256i *)sa );
		v = _mm256_mul_epu32( v, a );
		_mm256_store_si256( (__m256i *)si, v );
	}
	_BMARK_OFF( total_time );
	print_results_epi32( "vpmuludq\t_mm256_mul_epu32()", 8, si, cycles_count, total_time );

	// mullo vectors of 8 32-bit signed integers at a cycle
	_BMARK_ON_;
	for ( i = 0; i < cycles_count; i++ ) {
		v = _mm256_load_si256( (const __m256i *)si );
		a = _mm256_load_si256( (const __m256i *)sa );
		v = _mm256_mullo_epi32( v, a );
		_mm256_store_si256( (__m256i *)si, v );
	}
	_BMARK_OFF( total_time );
	print_results_epi32( "vpmulld\t_mm256_mullo_epi32()", 8, si, cycles_count, total_time );

	// sign vectors of 8 32-bit signed integers at a cycle
	_BMARK_ON_;
	for ( i = 0; i < cycles_count; i++ ) {
		v = _mm256_load_si256( (const __m256i *)si );
		a = _mm256_load_si256( (const __m256i *)sa );
		v = _mm256_sign_epi32( v, a );
		_mm256_store_si256( (__m256i *)si, v );
	}
	_BMARK_OFF( total_time );
	print_results_epi32( "vpsignd\t_mm256_sign_epi32()", 8, si, cycles_count, total_time );


	printf("\t   SIMD Arithmetic instructions with 256-bit vectors of 64-bit integers (measured by %i MCycles)\n", (int32_t)(cycles_count/1e6));

	int64_t ALIGN di[ 4 ] = { 8, 7, 6, 5 };
	int64_t ALIGN da[ 4 ] = { 1, 2, 3, 4 };

	// add vectors of 4 64-bit signed integers at a cycle
	_BMARK_ON_;
	for ( i = 0; i < cycles_count; i++ ) {
		v = _mm256_load_si256( (const __m256i *)di );
		a = _mm256_load_si256( (const __m256i *)da );
		v = _mm256_add_epi64( v, a );
		_mm256_store_si256( (__m256i *)di, v );
	}
	_BMARK_OFF( total_time );
	print_results_epi64( "vpaddq\t_mm256_add_epi64()", 4, di, cycles_count, total_time );

	// sub vectors of 4 64-bit signed integers at a cycle
	_BMARK_ON_;
	for ( i = 0; i < cycles_count; i++ ) {
		v = _mm256_load_si256( (const __m256i *)di );
		a = _mm256_load_si256( (const __m256i *)da );
		v = _mm256_sub_epi64( v, a );
		_mm256_store_si256( (__m256i *)di, v );
	}
	_BMARK_OFF( total_time );
	print_results_epi64( "vpsubq\t_mm256_sub_epi64()", 4, di, cycles_count, total_time );


	printf("\t   SIMD Arithmetic Instructions Benchmark value (simd-aibm)\t~%5.1lf GT/sec\n", total_tps);

	return 0;
}