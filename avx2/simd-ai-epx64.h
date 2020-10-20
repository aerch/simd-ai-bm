#ifndef __SIMD_AVX2_AI_EPX64_BM_H__
#define __SIMD_AVX2_AI_EPX64_BM_H__

const uint8_t avx2_ai_epx64_cnt = 2;

const char *avx2_ai_epx64_instructions[ avx2_ai_epx64_cnt + 1 ] = {
	"SIMD AVX2 64-bit Integer Arithmetic Instructions with 256-bit vectors ...",
	"vpaddq\t_mm256_add_epi64()",
	"vpsubq\t_mm256_sub_epi64()"
};
inline void avx2_ai_epx64_bm( thread_data_t *td,  pc_data_t *pc, int64_t *si64, int32_t vector_offset ) {
	int64_t i;
	int64_t *p __attribute__((aligned(32)));
	__m256i vi;
	__m256i ai = _mm256_set_epi64x( 8, 6, 4, 2 );

	while ( td->thread_active ) {

		p = si64;

		pc_get( pc, td->cycles_count );

		if ( !td->thread_active ) break;

		pthread_mutex_lock( &lock );
		evaluating_threads++;
		pthread_mutex_unlock( &lock );

		switch ( td->instruction ) {

			case 1: // add vectors of 4 64-bit signed integers at cycle
				vector_capacity = 4;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					vi = _mm256_load_si256( (const __m256i *)p );
					vi = _mm256_add_epi64( vi, ai );
					_mm256_store_si256( (__m256i *)p, vi );
				}
				break;

			case 2: // sub vectors of 4 64-bit signed integers at cycle
				vector_capacity = 4;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					vi = _mm256_load_si256( (const __m256i *)p );
					vi = _mm256_sub_epi64( vi, ai );
					_mm256_store_si256( (__m256i *)p, vi );
				}
				break;

			default:
				printf( "avx2_ai_epx64_bm_thread%u havn't instruction\n", td->tid );

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

void* avx2_ai_epx64_bm_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;
	td->vector_offset = 4;

	sprintf( td->name, "avx2_aiep64th%u", td->tid );
	prctl( PR_SET_NAME, td->name );

	uint64_t alloc_length = ( st_bm_cpt > mt_bm_cpt ? st_bm_cpt : mt_bm_cpt ) * td->vector_offset;
	uint64_t alloc_size = alloc_length * sizeof( int64_t );
	int64_t *si64 __attribute__((aligned(32))) = (int64_t*)aligned_alloc( 32, alloc_size );
	if ( !si64 ) perror( "aligned_alloc() error" );

	avx2_ai_epx64_bm( td, &pc[ DSP_PC ], si64, 4 );

	if ( si64 ) free( si64 );

	return NULL;
}

void* avx2_ai_epx64_cpu_bm_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;
	td->vector_offset = 0;

	sprintf( td->name, "avx2caiep64th%u", td->tid );
	prctl( PR_SET_NAME, td->name );

	int64_t si64[ 4 ] __attribute__((aligned(32))) = { 8, 6, 4, 2 };

	avx2_ai_epx64_bm( td, &pc[ CPU_PC ], si64, 0 );

	return NULL;
}

#endif // !__SIMD_AVX2_AI_EPX64_BM_H__