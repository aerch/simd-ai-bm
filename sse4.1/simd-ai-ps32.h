#ifndef __SIMD_SSE4_1_AI_PS32_BM_H__
#define __SIMD_SSE4_1_AI_PS32_BM_H__

const uint8_t sse4_1_ai_ps32_cnt = 1;

const char *sse4_1_ai_ps32_instructions[ sse4_1_ai_ps32_cnt + 1 ] = {
	"SIMD SSE4.1 32-bit Single-Precision Arithmetic Instructions with 128-bit vectors ...",
	"dpps   \t_mm_dp_ps()         "
};

inline void sse4_1_ai_ps32_bm( thread_data_t *td,  pc_data_t *pc, float *ps32 ) {
	int64_t i;
	float *ps32_start __attribute__((aligned(16))) = ps32;
	__m128 ws;
	__m128 bs = _mm_set_ps( 1.11111f, 2.22222f, 3.33333f, 4.44444f );

	while ( td->thread_active ) {

		pc_get( pc, td->cycles_count );

		if ( !td->thread_active ) break;

		pthread_mutex_lock( &lock );
		evaluating_threads++;
		pthread_mutex_unlock( &lock );

		ps32 = ps32_start;

		switch ( td->instruction ) {

			case 1: // pd vectors of 4 32-bit singles at cycle
				vector_capacity = 4;
				for ( i = 0; i < td->cycles_count; i++, ps32 += td->vector_offset ) {
					ws = _mm_load_ps( (const float *)ps32 );
					ws = _mm_dp_ps( ws, bs, 0x0f );
					_mm_store_ps( (float *)ps32, ws );
				}
				break;

			default:
				printf( "sse4_1_ai_ps32_bm_thread%u havn't instruction\n", td->tid );

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

void* sse4_1_ai_ps32_bm_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;
	td->vector_offset = 4;

	sprintf( td->name, "sse4.1_aips32th%u", td->tid );
	prctl( PR_SET_NAME, td->name );

	uint64_t alloc_length = ( ST_BM_CYCLES_PER_TIME > MT_BM_CYCLES_PER_TIME ? ST_BM_CYCLES_PER_TIME : MT_BM_CYCLES_PER_TIME ) * td->vector_offset;
	uint64_t alloc_size = alloc_length * sizeof( float );
	float *ps32 __attribute__((aligned(16))) = (float*)aligned_alloc( 16, alloc_size );
	if ( !ps32 ) perror( "aligned_alloc() error" );

	sse4_1_ai_ps32_bm( td, &pc[ DSP_PC ], ps32 );

	if ( ps32 ) free( ps32 );

	return NULL;
}

void* sse4_1_ai_ps32_cpu_bm_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;
	td->vector_offset = 0;

	sprintf( td->name, "sse4.1caips32th%u", td->tid );
	prctl( PR_SET_NAME, td->name );

	float ps32[ 4 ] __attribute__((aligned(16))) = { 8, 6, 4, 2 };

	sse4_1_ai_ps32_bm( td, &pc[ CPU_PC ], ps32 );

	return NULL;
}

#endif // !__SIMD_SSE4_1_AI_PS32_BM_H__