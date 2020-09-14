
inline void avx2_simd_ai_epx64_bm() {
	uint64_t i;

	fprintf( stream, "\n\tSIMD Arithmetic instructions with 256-bit vectors of 64-bit integers (measured by %i MCycles)\n", (int32_t)(cycles_count/1e6) );
	printf( "\n\tSIMD Arithmetic instructions with 256-bit vectors of 64-bit integers (measured by %i MCycles)\n", (int32_t)(cycles_count/1e6) );

	int64_t ALIGN32 qi[ 4 ] = { 8, 7, 6, 5 };
	int64_t ALIGN32 qa[ 4 ] = { 1, 2, 3, 4 };

	// add vectors of 4 64-bit signed integers at a cycle
	_BMARK_ON_;
	a = _mm256_load_si256( (const __m256i *)qa );
	for ( i = 0; i < cycles_count; i++ ) {
		v = _mm256_load_si256( (const __m256i *)qi );
		v = _mm256_add_epi64( v, a );
		_mm256_store_si256( (__m256i *)qi, v );
	}
	_BMARK_OFF( total_time );
	print_results( "vpaddq\t_mm256_add_epi64()", 4, cycles_count, total_time );
	// print_results_epi64( "vpaddq\t_mm256_add_epi64()", 4, qi, cycles_count, total_time );

	// sub vectors of 4 64-bit signed integers at a cycle
	_BMARK_ON_;
	a = _mm256_load_si256( (const __m256i *)qa );
	for ( i = 0; i < cycles_count; i++ ) {
		v = _mm256_load_si256( (const __m256i *)qi );
		v = _mm256_sub_epi64( v, a );
		_mm256_store_si256( (__m256i *)qi, v );
	}
	_BMARK_OFF( total_time );
	print_results( "vpsubq\t_mm256_sub_epi64()", 4, cycles_count, total_time );
	// print_results_epi64( "vpsubq\t_mm256_sub_epi64()", 4, qi, cycles_count, total_time );

	return;
}
