#ifndef __SIMD_SSSE3_AI_EPX8_BM_H__
#define __SIMD_SSSE3_AI_EPX8_BM_H__

const uint8_t ssse3_ai_epx8_cnt = 2;

const char *ssse3_ai_epx8_instructions[ ssse3_ai_epx8_cnt + 1 ] = {
	"SIMD SSSE3 8-bit Integer Arithmetic Instructions with 64-bit & 128-bit vectors ...",
	"psignb\t_mm_sign_epi8()     ",
	"psignb\t_mm_sign_pi8()      "
};

inline void ssse3_ai_epx8_bm( thread_data_t *td,  pc_data_t *pc, int8_t *si8, int32_t vector_offset ) {
	int64_t i;
	int8_t *p __attribute__((aligned(16)));
	__m128i wi;
	__m128i bi = _mm_set_epi8( 8, 7, 6, 5, 4, 3, 2, 1, 8, 7, 6, 5, 4, 3, 2, 1 );
	__m64 xi;
	__m64 ci = _mm_set_si64_epi8( 8, 7, 6, 5, 4, 3, 2, 1 );

	while ( td->thread_active ) {

		p = si8;

		pc_get( pc, td->cycles_count );

		if ( !td->thread_active ) break;

		pthread_mutex_lock( &lock );
		evaluating_threads++;
		pthread_mutex_unlock( &lock );

		switch ( td->instruction ) {

			case 1: // add vectors of 16 8-bit signed integers at cycle
				vector_capacity = 16;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					wi = _mm_load_si128( (const __m128i *)p );
					wi = _mm_sign_epi8( wi, bi );
					_mm_store_si128( (__m128i *)p, wi );
				}
				break;

			case 2: // adds vectors of 8 8-bit signed integers at cycle
				vector_capacity = 8;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					xi = *((const __m64*)p);
					xi = _mm_sign_pi8( xi, ci );
					*((__m64 *)p) = xi;
				}
				break;

			default:
				printf( "ssse3_ai_epx8_bm_thread%u havn't instruction\n", td->tid );

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

void* ssse3_ai_epx8_bm_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;
	td->vector_offset = 16;

	sprintf( td->name, "ssse3_aiep8th%u", td->tid );
	prctl( PR_SET_NAME, td->name );

	uint64_t alloc_length = ( st_bm_cpt > mt_bm_cpt ? st_bm_cpt : mt_bm_cpt ) * td->vector_offset;
	uint64_t alloc_size = alloc_length * sizeof( int8_t );
	int8_t *si8 __attribute__((aligned(16))) = (int8_t*)aligned_alloc( 16, alloc_size );
	if ( !si8 ) perror( "aligned_alloc() error" );

	ssse3_ai_epx8_bm( td, &pc[ DSP_PC ], si8, 16 );

	if ( si8 ) free( si8 );

	return NULL;
}

void* ssse3_ai_epx8_cpu_bm_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;
	td->vector_offset = 0;

	sprintf( td->name, "ssse3caiep8th%u", td->tid );
	prctl( PR_SET_NAME, td->name );

	int8_t si8[ 16 ] __attribute__((aligned(16))) = { 8, 7, 6, 5, 4, 3, 2, 1, 8, 7, 6, 5, 4, 3, 2, 1 };

	ssse3_ai_epx8_bm( td, &pc[ CPU_PC ], si8, 0 );

	return NULL;
}

#endif // !__SIMD_SSSE3_AI_EPX8_BM_H__