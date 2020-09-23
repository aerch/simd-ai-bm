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
	uint64_t i, _vi_;
	char name[ 25 ];

	sprintf( name, "avx2_aiep8th%u", td->tid );
	prctl( PR_SET_NAME, name );

	vector_capacity = 32;
	uint64_t alloc_length = MT_BM_CYCLES_PER_TIME * vector_capacity;
	uint64_t alloc_size = alloc_length * sizeof( int8_t );
	int8_t *si8 __attribute__((aligned(32))) = (int8_t*)aligned_alloc( 32, alloc_size );
	if ( !si8 ) perror( "aligned_alloc() error" );

	ai = _mm256_set_epi8( 8, 7, 6, 5, 4, 3, 2, 1, 8, 7, 6, 5, 4, 3, 2, 1, 8, 7, 6, 5, 4, 3, 2, 1, 8, 7, 6, 5, 4, 3, 2, 1 );

	pthread_mutex_lock( &lock );
	while ( (td->instruction == 0) && td->thread_active )
		pthread_cond_wait( &start, &lock );
	pthread_mutex_unlock( &lock );

	while ( td->thread_active ) {

		pc_get( td->cycles_count );

		if ( !td->thread_active ) break;

		switch ( td->instruction ) {

			case 1: // add vectors of 32 8-bit signed integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					vi = _mm256_load_si256( (const __m256i *)&si8[_vi_] );
					vi = _mm256_add_epi8( vi, ai );
					_mm256_store_si256( (__m256i *)&si8[_vi_], vi );
				}
				break;

			case 2: // adds vectors of 32 8-bit signed integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					vi = _mm256_load_si256( (const __m256i *)&si8[_vi_] );
					vi = _mm256_adds_epi8( vi, ai );
					_mm256_store_si256( (__m256i *)&si8[_vi_], vi );
				}
				break;

			case 3: // adds vectors of 32 8-bit unsigned integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					vi = _mm256_load_si256( (const __m256i *)&si8[_vi_] );
					vi = _mm256_adds_epu8( vi, ai );
					_mm256_store_si256( (__m256i *)&si8[_vi_], vi );
				}
				break;

			case 4: // sub vectors of 32 8-bit signed integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					vi = _mm256_load_si256( (const __m256i *)&si8[_vi_] );
					vi = _mm256_sub_epi8( vi, ai );
					_mm256_store_si256( (__m256i *)&si8[_vi_], vi );
				}
				break;

			case 5: // subs vectors of 32 8-bit signed integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					vi = _mm256_load_si256( (const __m256i *)&si8[_vi_] );
					vi = _mm256_subs_epi8( vi, ai );
					_mm256_store_si256( (__m256i *)&si8[_vi_], vi );
				}
				break;

			case 6: // subs vectors of 32 8-bit unsigned integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					vi = _mm256_load_si256( (const __m256i *)&si8[_vi_] );
					vi = _mm256_subs_epu8( vi, ai );
					_mm256_store_si256( (__m256i *)&si8[_vi_], vi );
				}
				break;

			case 7: // sign vectors of 32 8-bit signed integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					vi = _mm256_load_si256( (const __m256i *)&si8[_vi_] );
					vi = _mm256_sign_epi8( vi, ai );
					_mm256_store_si256( (__m256i *)&si8[_vi_], vi );
				}
				break;

			case 8: // subs vectors of 32 8-bit unsigned integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					vi = _mm256_load_si256( (const __m256i *)&si8[_vi_] );
					vi = _mm256_sad_epu8( vi, ai );
					_mm256_store_si256( (__m256i *)&si8[_vi_], vi );
				}
				break;

			default:
				printf( "avx2_ai_epx8_bm_thread%u havn't instruction\n", td->tid );

		}

		pthread_mutex_lock( &lock );
		pthread_cond_signal( &stop );
		pthread_mutex_unlock( &lock );

	}

	pthread_mutex_lock( &lock );
	active_threads--;
	pthread_cond_signal( &finish );
	pthread_mutex_unlock( &lock );

	if ( si8 )
		free( si8 );

	return NULL;
}

#endif // !__SIMD_AVX2_AI_EPX8_BM_H__