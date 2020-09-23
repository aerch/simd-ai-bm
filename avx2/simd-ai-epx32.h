#ifndef __SIMD_AVX2_AI_EPX32_BM_H__
#define __SIMD_AVX2_AI_EPX32_BM_H__

const uint8_t avx2_ai_epx32_cnt = 8;

const char *avx2_ai_epx32_instructions[ avx2_ai_epx32_cnt + 1 ] = {
	"SIMD AVX2 32-bit Integer Arithmetic Instructions with 256-bit vectors ...",
	"vpaddd\t_mm256_add_epi32()",
	"vphaddd\t_mm256_hadd_epi32()",
	"vpsubd\t_mm256_sub_epi32()",
	"vphsubd\t_mm256_hsub_epi32()",
	"vpmuldq\t_mm256_mul_epi32()",
	"vpmuludq\t_mm256_mul_epu32()",
	"vpmulld\t_mm256_mullo_epi32()",
	"vpsignd\t_mm256_sign_epi32()"
};

void* avx2_ai_epx32_bm_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;
	uint64_t i, _vi_;
	char name[ 25 ];

	sprintf( name, "avx2_aiep32th%u", td->tid );
	prctl( PR_SET_NAME, name );

	vector_capacity = 8;
	uint64_t alloc_length = MT_BM_CYCLES_PER_TIME * vector_capacity;
	uint64_t alloc_size = alloc_length * sizeof( int32_t );
	int32_t *si32 __attribute__((aligned(32))) = (int32_t*)aligned_alloc( 32, alloc_size );
	if ( !si32 ) perror( "aligned_alloc() error" );

	ai = _mm256_set_epi32( 8, 7, 6, 5, 4, 3, 2, 1 );

	pthread_mutex_lock( &lock );
	while ( (td->instruction == 0) && td->thread_active )
		pthread_cond_wait( &start, &lock );
	pthread_mutex_unlock( &lock );

	while ( td->thread_active ) {

		pc_get( td->cycles_count );

		if ( !td->thread_active ) break;

		switch ( td->instruction ) {

			case 1: // add vectors of 8 32-bit signed integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					vi = _mm256_load_si256( (const __m256i *)&si32[_vi_] );
					vi = _mm256_add_epi32( vi, ai );
					_mm256_store_si256( (__m256i *)&si32[_vi_], vi );
				}
				break;

			case 2: // hadd vectors of 8 32-bit signed integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					vi = _mm256_load_si256( (const __m256i *)&si32[_vi_] );
					vi = _mm256_hadd_epi32( vi, ai );
					_mm256_store_si256( (__m256i *)&si32[_vi_], vi );
				}
				break;

			case 3: // sub vectors of 8 32-bit signed integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					vi = _mm256_load_si256( (const __m256i *)&si32[_vi_] );
					vi = _mm256_sub_epi32( vi, ai );
					_mm256_store_si256( (__m256i *)&si32[_vi_], vi );
				}
				break;

			case 4: // hsub vectors of 8 32-bit signed integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					vi = _mm256_load_si256( (const __m256i *)&si32[_vi_] );
					vi = _mm256_hsub_epi32( vi, ai );
					_mm256_store_si256( (__m256i *)&si32[_vi_], vi );
				}
				break;

			case 5: // mul vectors of 8 32-bit signed integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					vi = _mm256_load_si256( (const __m256i *)&si32[_vi_] );
					vi = _mm256_mul_epi32( vi, ai );
					_mm256_store_si256( (__m256i *)&si32[_vi_], vi );
				}
				break;

			case 6: // mul vectors of 8 32-bit unsigned integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					vi = _mm256_load_si256( (const __m256i *)&si32[_vi_] );
					vi = _mm256_mul_epu32( vi, ai );
					_mm256_store_si256( (__m256i *)&si32[_vi_], vi );
				}
				break;

			case 7: // mullo vectors of 8 32-bit signed integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					vi = _mm256_load_si256( (const __m256i *)&si32[_vi_] );
					vi = _mm256_mullo_epi32( vi, ai );
					_mm256_store_si256( (__m256i *)&si32[_vi_], vi );
				}
				break;

			case 8: // sign vectors of 8 32-bit signed integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					vi = _mm256_load_si256( (const __m256i *)&si32[_vi_] );
					vi = _mm256_sign_epi32( vi, ai );
					_mm256_store_si256( (__m256i *)&si32[_vi_], vi );
				}
				break;

			default:
				printf( "avx2_ai_epx32_bm_thread%u havn't instruction\n", td->tid );

		}

		pthread_mutex_lock( &lock );
		pthread_cond_signal( &stop );
		pthread_mutex_unlock( &lock );

	}

	pthread_mutex_lock( &lock );
	active_threads--;
	pthread_cond_signal( &finish );
	pthread_mutex_unlock( &lock );

	if ( si32 )
		free( si32 );

	return NULL;
}

#endif // !__SIMD_AVX2_AI_EPX32_BM_H__