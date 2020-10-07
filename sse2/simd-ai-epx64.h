#ifndef __SIMD_SSE2_AI_EPX64_BM_H__
#define __SIMD_SSE2_AI_EPX64_BM_H__

const uint8_t sse2_ai_epx64_cnt = 4;

const char *sse2_ai_epx64_instructions[ sse2_ai_epx64_cnt + 1 ] = {
	"SIMD SSE2 64-bit Integer Arithmetic Instructions with 64-bit & 128-bit vectors ...",
	"paddq\t_mm_add_epi64()   ",
	"paddq\t_mm_add_si64()    ",
	"psubq\t_mm_sub_epi64()   ",
	"psubq\t_mm_sub_si64()    "
};

inline void sse2_ai_epx64_bm( thread_data_t *td,  pc_data_t *pc, int64_t *si64 ) {
	int64_t i;
	int64_t *si64_start __attribute__((aligned(16))) = si64;
	__m128i wi;
	__m128i bi = _mm_set_epi64x( 8, 5 );
	__m64 xi;
	si64[0] = 1;
	__m64 ci = _mm_load_si64( (const __m64 *)si64 );

	while ( td->thread_active ) {

		pc_get( pc, td->cycles_count );

		if ( !td->thread_active ) break;

		pthread_mutex_lock( &lock );
		evaluating_threads++;
		pthread_mutex_unlock( &lock );

		si64 = si64_start;

		switch ( td->instruction ) {

			case 1: // add vectors of 2 64-bit signed integers at cycle
				vector_capacity = 2;
				for ( i = 0; i < td->cycles_count; i++, si64 += td->vector_offset ) {
					wi = _mm_load_si128( (const __m128i *)si64 );
					wi = _mm_add_epi64( wi, bi );
					_mm_store_si128( (__m128i *)si64, wi );
				}
				break;

			case 2: // add vectors of 1 64-bit signed integers at cycle
				vector_capacity = 1;
				for ( i = 0; i < td->cycles_count; i++, si64 += td->vector_offset ) {
					xi = _mm_load_si64( (const __m64 *)si64 );
					xi = _mm_add_si64( xi, ci );
					_mm_store_si64( (__m64 *)si64, xi );
				}
				break;

			case 3: // sub vectors of 2 64-bit signed integers at cycle
				vector_capacity = 2;
				for ( i = 0; i < td->cycles_count; i++, si64 += td->vector_offset ) {
					wi = _mm_load_si128( (const __m128i *)si64 );
					wi = _mm_sub_epi64( wi, bi );
					_mm_store_si128( (__m128i *)si64, wi );
				}
				break;

			case 4: // sub vectors of 1 64-bit signed integers at cycle
				vector_capacity = 1;
				for ( i = 0; i < td->cycles_count; i++, si64 += td->vector_offset ) {
					xi = _mm_load_si64( (const __m64 *)si64 );
					xi = _mm_sub_si64( xi, ci );
					_mm_store_si64( (__m64 *)si64, xi );
				}
				break;

			default:
				printf( "sse2_ai_epx64_bm_thread%u havn't instruction\n", td->tid );

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

void* sse2_ai_epx64_bm_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;
	td->vector_offset = 2;

	sprintf( td->name, "sse2_aiep64th%u", td->tid );
	prctl( PR_SET_NAME, td->name );

	uint64_t alloc_length = ( ST_BM_CYCLES_PER_TIME > MT_BM_CYCLES_PER_TIME ? ST_BM_CYCLES_PER_TIME : MT_BM_CYCLES_PER_TIME ) * td->vector_offset;
	uint64_t alloc_size = alloc_length * sizeof( int64_t );
	int64_t *si64 __attribute__((aligned(16))) = (int64_t*)aligned_alloc( 16, alloc_size );
	if ( !si64 ) perror( "aligned_alloc() error" );

	sse2_ai_epx64_bm( td, &pc[ DSP_PC ], si64 );

	if ( si64 ) free( si64 );

	return NULL;
}

void* sse2_ai_epx64_cpu_bm_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;
	td->vector_offset = 0;

	sprintf( td->name, "sse2caiep64th%u", td->tid );
	prctl( PR_SET_NAME, td->name );

	int64_t si64[ 2 ] __attribute__((aligned(16))) = { 8, 2 };

	sse2_ai_epx64_bm( td, &pc[ CPU_PC ], si64 );

	return NULL;
}

#endif // !__SIMD_SSE2_AI_EPX64_BM_H__