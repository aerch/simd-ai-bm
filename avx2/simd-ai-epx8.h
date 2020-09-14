
inline void avx2_simd_ai_epx8_bm() {
	uint64_t i;

	fprintf( stream, "\n\tSIMD Arithmetic instructions with 256-bit vectors of  8-bit integers (measured by %i MCycles)\n", (int32_t)(cycles_count/1e6) );
	printf( "\n\tSIMD Arithmetic instructions with 256-bit vectors of  8-bit integers (measured by %i MCycles)\n", (int32_t)(cycles_count/1e6) );

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

	return;
}
