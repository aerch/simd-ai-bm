#ifndef __SIMD_SSE4_1_AI_PS32_BM_H__
#define __SIMD_SSE4_1_AI_PS32_BM_H__

const uint8_t sse4_1_ai_ps32_cnt = 1;

const char *sse4_1_ai_ps32_instructions[ sse4_1_ai_ps32_cnt + 1 ] = {
	"SIMD SSE4.1 32-bit Single-Precision Arithmetic Instructions with 128-bit vectors ...",
	"dpps   \t_mm_dp_ps()         "
};

void* sse4_1_ai_ps32_bm_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;
	uint64_t i, _vi_;
	char name[ 25 ];

	sprintf( name, "sse4.1_aips32th%u", td->tid );
	prctl( PR_SET_NAME, name );

	vector_capacity = 4;
	uint64_t alloc_length = MT_BM_CYCLES_PER_TIME * vector_capacity;
	uint64_t alloc_size = alloc_length * sizeof( float );
	float *ps32 __attribute__((aligned(16))) = (float*)aligned_alloc( 16, alloc_size );
	if ( !ps32 ) perror( "aligned_alloc() error" );

	bs = _mm_set_ps( 1.11111f, 2.22222f, 3.33333f, 4.44444f );

	pthread_mutex_lock( &lock );
	while ( (td->instruction == 0) && td->thread_active )
		pthread_cond_wait( &start, &lock );
	pthread_mutex_unlock( &lock );

	while ( td->thread_active ) {

		pc_get( td->cycles_count );

		if ( !td->thread_active ) break;

		switch ( td->instruction ) {

			case 1: // pd vectors of 2 32-bit singles at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					ws = _mm_load_ps( (const float *)&ps32[_vi_] );
					ws = _mm_dp_ps( ws, bs, 0x0f );
					_mm_store_ps( (float *)&ps32[_vi_], ws );
				}
				break;

			default:
				printf( "sse4_1_ai_ps32_bm_thread%u havn't instruction\n", td->tid );

		}

		pthread_mutex_lock( &lock );
		pthread_cond_signal( &stop );
		pthread_mutex_unlock( &lock );

	}

	pthread_mutex_lock( &lock );
	active_threads--;
	pthread_cond_signal( &finish );
	pthread_mutex_unlock( &lock );

	if ( ps32 )
		free( ps32 );

	return NULL;
}

#endif // !__SIMD_SSE4_1_AI_PS32_BM_H__