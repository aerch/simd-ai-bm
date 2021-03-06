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

inline void avx2_ai_epx32_bm( thread_data_t *td,  pc_data_t *pc, int32_t *si32, int32_t vector_offset ) {
	int64_t i;
	int32_t *p __attribute__((aligned(32)));
	__m256i vi;
	__m256i ai = _mm256_set_epi32( 8, 7, 6, 5, 4, 3, 2, 1 );

	while ( td->thread_active ) {

		p = si32;

		pc_get( pc, td->cycles_count );

		if ( !td->thread_active ) break;

		pthread_mutex_lock( &lock );
		evaluating_threads++;
		pthread_mutex_unlock( &lock );

		switch ( td->instruction ) {

			case 1: // add vectors of 8 32-bit signed integers at cycle
				vector_capacity = 8;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					vi = _mm256_load_si256( (const __m256i *)p );
					vi = _mm256_add_epi32( vi, ai );
					_mm256_store_si256( (__m256i *)p, vi );
				}
				break;

			case 2: // hadd vectors of 8 32-bit signed integers at cycle
				vector_capacity = 8;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					vi = _mm256_load_si256( (const __m256i *)p );
					vi = _mm256_hadd_epi32( vi, ai );
					_mm256_store_si256( (__m256i *)p, vi );
				}
				break;

			case 3: // sub vectors of 8 32-bit signed integers at cycle
				vector_capacity = 8;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					vi = _mm256_load_si256( (const __m256i *)p );
					vi = _mm256_sub_epi32( vi, ai );
					_mm256_store_si256( (__m256i *)p, vi );
				}
				break;

			case 4: // hsub vectors of 8 32-bit signed integers at cycle
				vector_capacity = 8;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					vi = _mm256_load_si256( (const __m256i *)p );
					vi = _mm256_hsub_epi32( vi, ai );
					_mm256_store_si256( (__m256i *)p, vi );
				}
				break;

			case 5: // mul vectors of 8 32-bit signed integers at cycle
				vector_capacity = 8;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					vi = _mm256_load_si256( (const __m256i *)p );
					vi = _mm256_mul_epi32( vi, ai );
					_mm256_store_si256( (__m256i *)p, vi );
				}
				break;

			case 6: // mul vectors of 8 32-bit unsigned integers at cycle
				vector_capacity = 8;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					vi = _mm256_load_si256( (const __m256i *)p );
					vi = _mm256_mul_epu32( vi, ai );
					_mm256_store_si256( (__m256i *)p, vi );
				}
				break;

			case 7: // mullo vectors of 8 32-bit signed integers at cycle
				vector_capacity = 8;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					vi = _mm256_load_si256( (const __m256i *)p );
					vi = _mm256_mullo_epi32( vi, ai );
					_mm256_store_si256( (__m256i *)p, vi );
				}
				break;

			case 8: // sign vectors of 8 32-bit signed integers at cycle
				vector_capacity = 8;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					vi = _mm256_load_si256( (const __m256i *)p );
					vi = _mm256_sign_epi32( vi, ai );
					_mm256_store_si256( (__m256i *)p, vi );
				}
				break;

			default:
				printf( "avx2_ai_epx32_bm_thread%u havn't instruction\n", td->tid );

		}

		pthread_mutex_lock( &lock );
		evaluating_threads--;
		pthread_cond_signal( &stop );
		pthread_mutex_unlock( &lock );

	}

	pthread_mutex_lock( &lock );
	active_threads--;
	pthread_cond_signal( &finish );
	pthread_mutex_unlock( &lock );

	return;
}

void* avx2_ai_epx32_bm_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;
	td->vector_offset = 8;

	sprintf( td->name, "avx2_aiep32th%u", td->tid );
	prctl( PR_SET_NAME, td->name );

	uint64_t alloc_length = ( st_bm_cpt > mt_bm_cpt ? st_bm_cpt : mt_bm_cpt ) * td->vector_offset;
	uint64_t alloc_size = alloc_length * sizeof( int32_t );
	int32_t *si32 __attribute__((aligned(32))) = (int32_t*)aligned_alloc( 32, alloc_size );
	if ( !si32 ) perror( "aligned_alloc() error" );

	avx2_ai_epx32_bm( td, &pc[ DSP_PC ], si32, 8 );

	if ( si32 ) free( si32 );

	return NULL;
}

void* avx2_ai_epx32_cpu_bm_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;
	td->vector_offset = 0;

	sprintf( td->name, "avx2caiep32th%u", td->tid );
	prctl( PR_SET_NAME, td->name );

	int32_t si32[ 8 ] __attribute__((aligned(32))) = { 8, 7, 6, 5, 4, 3, 2, 1 };

	avx2_ai_epx32_bm( td, &pc[ CPU_PC ], si32, 0 );

	return NULL;
}

#endif // !__SIMD_AVX2_AI_EPX32_BM_H__