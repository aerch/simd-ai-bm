
inline void avx2_simd_ai_epx32_bm() {
	uint64_t i;

	fprintf( stream, "\n\tSIMD Arithmetic instructions with 256-bit vectors of 32-bit integers (measured by %i MCycles)\n", (int32_t)(cycles_count/1e6) );
	printf( BLUE "      SIMD Arithmetic instructions with 256-bit vectors of 32-bit integers (measured by %i MCycles)\n" OFF, (int32_t)(cycles_count/1e6) );

	int32_t ALIGN32 di[ 8 ] = { 8, 7, 6, 5, 4, 3, 2, 1 };
	int32_t ALIGN32 da[ 8 ] = { 1, 2, 3, 4, 5, 6, 7, 8 };

	// add vectors of 8 32-bit signed integers at a cycle
	_BMARK_ON_;
	a = _mm256_load_si256( (const __m256i *)da );
	for ( i = 0; i < cycles_count; i++ ) {
		v = _mm256_load_si256( (const __m256i *)di );
		v = _mm256_add_epi32( v, a );
		_mm256_store_si256( (__m256i *)di, v );
	}
	_BMARK_OFF( total_time );
	print_results( "vpaddd\t_mm256_add_epi32()", 8, cycles_count, total_time );
	// print_results_epi32( "vpaddd\t_mm256_add_epi32()", 8, di, cycles_count, total_time );

	// hadd vectors of 8 32-bit signed integers at a cycle
	_BMARK_ON_;
	a = _mm256_load_si256( (const __m256i *)da );
	for ( i = 0; i < cycles_count; i++ ) {
		v = _mm256_load_si256( (const __m256i *)di );
		v = _mm256_hadd_epi32( v, a );
		_mm256_store_si256( (__m256i *)di, v );
	}
	_BMARK_OFF( total_time );
	print_results( "vphaddd\t_mm256_hadd_epi32()", 8, cycles_count, total_time );
	// print_results_epi32( "vphaddd\t_mm256_hadd_epi32()", 8, di, cycles_count, total_time );

	// sub vectors of 8 32-bit signed integers at a cycle
	_BMARK_ON_;
	a = _mm256_load_si256( (const __m256i *)da );
	for ( i = 0; i < cycles_count; i++ ) {
		v = _mm256_load_si256( (const __m256i *)di );
		v = _mm256_sub_epi32( v, a );
		_mm256_store_si256( (__m256i *)di, v );
	}
	_BMARK_OFF( total_time );
	print_results( "vpsubd\t_mm256_sub_epi32()", 8, cycles_count, total_time );
	// print_results_epi32( "vpsubd\t_mm256_sub_epi32()", 8, di, cycles_count, total_time );

	// hsub vectors of 8 32-bit signed integers at a cycle
	_BMARK_ON_;
	a = _mm256_load_si256( (const __m256i *)da );
	for ( i = 0; i < cycles_count; i++ ) {
		v = _mm256_load_si256( (const __m256i *)di );
		v = _mm256_hsub_epi32( v, a );
		_mm256_store_si256( (__m256i *)di, v );
	}
	_BMARK_OFF( total_time );
	print_results( "vphsubd\t_mm256_hsub_epi32()", 8, cycles_count, total_time );
	// print_results_epi32( "vphsubd\t_mm256_hsub_epi32()", 8, di, cycles_count, total_time );

	// mul vectors of 8 32-bit signed integers at a cycle
	_BMARK_ON_;
	a = _mm256_load_si256( (const __m256i *)da );
	for ( i = 0; i < cycles_count; i++ ) {
		v = _mm256_load_si256( (const __m256i *)di );
		v = _mm256_mul_epi32( v, a );
		_mm256_store_si256( (__m256i *)di, v );
	}
	_BMARK_OFF( total_time );
	print_results( "vpmuldq\t_mm256_mul_epi32()", 8, cycles_count, total_time );
	// print_results_epi32( "vpmuldq\t_mm256_mul_epi32()", 8, di, cycles_count, total_time );

	// mul vectors of 8 32-bit unsigned integers at a cycle
	_BMARK_ON_;
	a = _mm256_load_si256( (const __m256i *)da );
	for ( i = 0; i < cycles_count; i++ ) {
		v = _mm256_load_si256( (const __m256i *)di );
		v = _mm256_mul_epu32( v, a );
		_mm256_store_si256( (__m256i *)di, v );
	}
	_BMARK_OFF( total_time );
	print_results( "vpmuludq\t_mm256_mul_epu32()", 8, cycles_count, total_time );
	// print_results_epi32( "vpmuludq\t_mm256_mul_epu32()", 8, di, cycles_count, total_time );

	// mullo vectors of 8 32-bit signed integers at a cycle
	_BMARK_ON_;
	a = _mm256_load_si256( (const __m256i *)da );
	for ( i = 0; i < cycles_count; i++ ) {
		v = _mm256_load_si256( (const __m256i *)di );
		v = _mm256_mullo_epi32( v, a );
		_mm256_store_si256( (__m256i *)di, v );
	}
	_BMARK_OFF( total_time );
	print_results( "vpmulld\t_mm256_mullo_epi32()", 8, cycles_count, total_time );
	// print_results_epi32( "vpmulld\t_mm256_mullo_epi32()", 8, di, cycles_count, total_time );

	// sign vectors of 8 32-bit signed integers at a cycle
	_BMARK_ON_;
	a = _mm256_load_si256( (const __m256i *)da );
	for ( i = 0; i < cycles_count; i++ ) {
		v = _mm256_load_si256( (const __m256i *)di );
		v = _mm256_sign_epi32( v, a );
		_mm256_store_si256( (__m256i *)di, v );
	}
	_BMARK_OFF( total_time );
	print_results( "vpsignd\t_mm256_sign_epi32()", 8, cycles_count, total_time );
	// print_results_epi32( "vpsignd\t_mm256_sign_epi32()", 8, di, cycles_count, total_time );

	return;
}
