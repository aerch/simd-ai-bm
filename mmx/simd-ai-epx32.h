#ifndef __SIMD_MMX_AI_EPX32_BM_H__
#define __SIMD_MMX_AI_EPX32_BM_H__

const uint8_t mmx_ai_epx32_cnt = 4;

const char *mmx_ai_epx32_instructions[ mmx_ai_epx32_cnt + 1 ] = {
	"SIMD MMX 32-bit Integer Arithmetic Instructions with 64-bit vectors ...",
	"paddd\t_mm_add_pi32    ",
	"paddd\t_m_paddd        ",
	"psubd\t_mm_sub_pi32    ",
	"psubd\t_m_psubd        "
};

inline void mmx_ai_epx32_bm( thread_data_t *td,  pc_data_t *pc, int32_t *si32 ) {
	int64_t i;
	int32_t *si32_start __attribute__((aligned(16))) = si32;
	__m64 xi;
	__m64 ci = _mm_set_si64_epi16( 4, 3, 2, 1 );

	while ( td->thread_active ) {

		pc_get( pc, td->cycles_count );

		if ( !td->thread_active ) break;

		pthread_mutex_lock( &lock );
		evaluating_threads++;
		pthread_mutex_unlock( &lock );

		si32 = si32_start;

		switch ( td->instruction ) {

			case 1: // paddd vectors of 2 32-bit signed integers at cycle
				vector_capacity = 2;
				for ( i = 0; i < td->cycles_count; i++, si32 += td->vector_offset ) {
					xi = _mm_load_si64( (const __m64 *)si32 );
					xi = _mm_add_pi32( xi, ci );
					_mm_store_si64( (__m64 *)si32, xi );
				}
				break;

			case 2: // paddd vectors of 2 32-bit signed integers at cycle
				vector_capacity = 2;
				for ( i = 0; i < td->cycles_count; i++, si32 += td->vector_offset ) {
					xi = _mm_load_si64( (const __m64 *)si32 );
					xi = _m_paddd( xi, ci );
					_mm_store_si64( (__m64 *)si32, xi );
				}
				break;

			case 3: // psubd vectors of 2 32-bit signed integers at cycle
				vector_capacity = 2;
				for ( i = 0; i < td->cycles_count; i++, si32 += td->vector_offset ) {
					xi = _mm_load_si64( (const __m64 *)si32 );
					xi = _mm_sub_pi32( xi, ci );
					_mm_store_si64( (__m64 *)si32, xi );
				}
				break;

			case 4: // psubd vectors of 2 32-bit signed integers at cycle
				vector_capacity = 2;
				for ( i = 0; i < td->cycles_count; i++, si32 += td->vector_offset ) {
					xi = _mm_load_si64( (const __m64 *)si32 );
					xi = _m_psubd( xi, ci );
					_mm_store_si64( (__m64 *)si32, xi );
				}
				break;

			default:
				printf( "mmx_ai_epx32_bm_thread%u havn't instruction\n", td->tid );

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

void* mmx_ai_epx32_bm_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;
	td->vector_offset = 2;

	sprintf( td->name, "mmx_aiep32th%u", td->tid );
	prctl( PR_SET_NAME, td->name );

	uint64_t alloc_length = ( ST_BM_CYCLES_PER_TIME > MT_BM_CYCLES_PER_TIME ? ST_BM_CYCLES_PER_TIME : MT_BM_CYCLES_PER_TIME ) * td->vector_offset;
	uint64_t alloc_size = alloc_length * sizeof( int32_t );
	int32_t *si32 __attribute__((aligned(16))) = (int32_t*)aligned_alloc( 16, alloc_size );
	if ( !si32 ) perror( "aligned_alloc() error" );

	mmx_ai_epx32_bm( td, &pc[ DSP_PC ], si32 );

	if ( si32 ) free( si32 );

	return NULL;
}

void* mmx_ai_epx32_cpu_bm_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;
	td->vector_offset = 0;

	sprintf( td->name, "mmxcaiep32th%u", td->tid );
	prctl( PR_SET_NAME, td->name );

	int32_t si32[ 2 ] __attribute__((aligned(16))) = { 6, 5 };

	mmx_ai_epx32_bm( td, &pc[ CPU_PC ], si32 );

	return NULL;
}

#endif // !__SIMD_MMX_AI_EPX32_BM_H__