#ifndef __SIMD_AVX2_AI_EPX8_BM_H__
#define __SIMD_AVX2_AI_EPX8_BM_H__

const uint8_t avx2_ai_epx8_cnt = 8;

const char *avx2_ai_epx8_instructions[ avx2_ai_epx8_cnt + 1 ] = {
	"SIMD AVX2 8-bit Integer Arithmetic Instructions with 256-bit vectors ...",
	"vpaddb\t_mm256_add_epi8()",
	"vpaddsb\t_mm256_adds_epi8()",
	"vpaddusb\t_mm256_adds_epu8()",
	"vpsubb\t_mm256_sub_epi8()",
	"vpsubsb\t_mm256_adds_epi8()",
	"vpsubusb\t_mm256_adds_epu8()",
	"vpsignb\t_mm256_sign_epi8()",
	"vpsadbw\t_mm256_sad_epu8()"
};

void* avx2_ai_epx8_bm_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;
	char name[ 25 ];
	uint64_t i;

	sprintf( name, "avx2_aiep8th%u", td->tid );
	prctl( PR_SET_NAME, name );

	vector_capacity = 32;
	int8_t ALIGN32 bi[ vector_capacity ] = { 8, 7, 6, 5, 4, 3, 2, 1, 8, 7, 6, 5, 4, 3, 2, 1, 8, 7, 6, 5, 4, 3, 2, 1, 8, 7, 6, 5, 4, 3, 2, 1 };
	int8_t ALIGN32 ba[ vector_capacity ] = { 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8 };

	while ( td->thread_active ) {

		pthread_mutex_lock( &lock );
		while ( (td->instruction == 0) && td->thread_active )
			pthread_cond_wait( &start, &lock );
		pthread_mutex_unlock( &lock );

		if ( !td->thread_active ) break;

		ai = _mm256_load_si256( (const __m256i *)ba );

		switch ( td->instruction ) {

			case 1: // add vectors of 32 8-bit signed integers at cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					vi = _mm256_load_si256( (const __m256i *)bi );
					vi = _mm256_add_epi8( vi, ai );
					_mm256_store_si256( (__m256i *)bi, vi );
				}
				break;

			case 2: // adds vectors of 32 8-bit signed integers at cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					vi = _mm256_load_si256( (const __m256i *)bi );
					vi = _mm256_adds_epi8( vi, ai );
					_mm256_store_si256( (__m256i *)bi, vi );
				}
				break;

			case 3: // adds vectors of 32 8-bit unsigned integers at cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					vi = _mm256_load_si256( (const __m256i *)bi );
					vi = _mm256_adds_epu8( vi, ai );
					_mm256_store_si256( (__m256i *)bi, vi );
				}
				break;

			case 4: // sub vectors of 32 8-bit signed integers at cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					vi = _mm256_load_si256( (const __m256i *)bi );
					vi = _mm256_sub_epi8( vi, ai );
					_mm256_store_si256( (__m256i *)bi, vi );
				}
				break;

			case 5: // subs vectors of 32 8-bit signed integers at cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					vi = _mm256_load_si256( (const __m256i *)bi );
					vi = _mm256_subs_epi8( vi, ai );
					_mm256_store_si256( (__m256i *)bi, vi );
				}
				break;

			case 6: // subs vectors of 32 8-bit unsigned integers at cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					vi = _mm256_load_si256( (const __m256i *)bi );
					vi = _mm256_subs_epu8( vi, ai );
					_mm256_store_si256( (__m256i *)bi, vi );
				}
				break;

			case 7: // sign vectors of 32 8-bit signed integers at cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					vi = _mm256_load_si256( (const __m256i *)bi );
					vi = _mm256_sign_epi8( vi, ai );
					_mm256_store_si256( (__m256i *)bi, vi );
				}
				break;

			case 8: // subs vectors of 32 8-bit unsigned integers at cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					vi = _mm256_load_si256( (const __m256i *)bi );
					vi = _mm256_sad_epu8( vi, ai );
					_mm256_store_si256( (__m256i *)bi, vi );
				}
				break;

			default:
				printf( "avx2_ai_epx8_bm_thread%u havn't instruction\n", td->tid );

		}

		pthread_mutex_lock( &lock );
		td->instruction = 0;
		SET_BIT( active_threads_flag, td->tid, 0 );
		if ( !active_threads_flag )
			pthread_cond_signal( &stop );
		pthread_mutex_unlock( &lock );

	}

	return NULL;
}

#endif // !__SIMD_AVX2_AI_EPX8_BM_H__