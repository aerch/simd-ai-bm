
inline void avx2_simd_ai_epx64_bm() {
	uint64_t i;

	fprintf( stream, "\n\tSIMD Arithmetic instructions with 256-bit vectors of 64-bit integers (measured by %i MCycles)\n", (int32_t)(cycles_count/1e6) );
	printf( "\n\tSIMD Arithmetic instructions with 256-bit vectors of 64-bit integers (measured by %i MCycles)\n", (int32_t)(cycles_count/1e6) );

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

	return;
}
