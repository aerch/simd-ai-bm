#ifndef __SIMD_SSE3_AI_PS32_BM_H__
#define __SIMD_SSE3_AI_PS32_BM_H__

const uint8_t sse3_ai_ps32_cnt = 3;

const char *sse3_ai_ps32_instructions[ sse3_ai_ps32_cnt + 1 ] = {
	"SIMD SSE3 32-bit Single-Precision Arithmetic Instructions with 128-bit vectors ...",
	"addsubps\t_mm_addsub_ps()  ",
	"haddps  \t_mm_hadd_ps()    ",
	"hsubps  \t_mm_hsub_ps()    "
};

void* sse3_ai_ps32_bm_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;
	uint64_t i, _vi_;
	char name[ 25 ];

	sprintf( name, "sse3_aips32th%u", td->tid );
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

			case 1: // add vectors of 4 32-bit singles at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					ws = _mm_load_ps( (const float *)&ps32[_vi_] );
					ws = _mm_addsub_ps( ws, bs );
					_mm_store_ps( (float *)&ps32[_vi_], ws );
				}
				break;

			case 2: // hadd vectors of 4 32-bit singles at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					ws = _mm_load_ps( (const float *)&ps32[_vi_] );
					ws = _mm_hadd_ps( ws, bs );
					_mm_store_ps( (float *)&ps32[_vi_], ws );
				}
				break;

			case 3: // hsub vectors of 4 32-bit singles at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					ws = _mm_load_ps( (const float *)&ps32[_vi_] );
					ws = _mm_hsub_ps( ws, bs );
					_mm_store_ps( (float *)&ps32[_vi_], ws );
				}
				break;

			default:
				printf( "sse3_ai_ps32_bm_thread%u havn't instruction\n", td->tid );

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

#endif // !__SIMD_SSE3_AI_PS32_BM_H__