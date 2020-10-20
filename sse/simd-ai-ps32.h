#ifndef __SIMD_SSE_AI_PS32_BM_H__
#define __SIMD_SSE_AI_PS32_BM_H__

const uint8_t sse_ai_ps32_cnt = 8;

const char *sse_ai_ps32_instructions[ sse_ai_ps32_cnt + 1 ] = {
	"SIMD SSE 32-bit Single-Precision Arithmetic Instructions with 128-bit vectors ...",
	"addps   \t_mm_add_ps()     ",
	"addss   \t_mm_add_ss()     ",
	"divps   \t_mm_div_ps()     ",
	"divss   \t_mm_div_ss()     ",
	"mulps   \t_mm_mul_ps()     ",
	"mulss   \t_mm_mul_ss()     ",
	"subps   \t_mm_sub_ps()     ",
	"subss   \t_mm_sub_ss()     "
};

inline void sse_ai_ps32_bm( thread_data_t *td,  pc_data_t *pc, float *ps32, int32_t vector_offset ) {
	int64_t i;
	float *p __attribute__((aligned(16)));
	__m128 ws;
	__m128 bs = _mm_set_ps( 1.11111f, 2.22222f, 3.33333f, 4.44444f );

	while ( td->thread_active ) {

		p = ps32;

		pc_get( pc, td->cycles_count );

		if ( !td->thread_active ) break;

		pthread_mutex_lock( &lock );
		evaluating_threads++;
		pthread_mutex_unlock( &lock );

		switch ( td->instruction ) {

			case 1: // add vectors of 4 32-bit singles at cycle
				vector_capacity = 4;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					ws = _mm_load_ps( (const float *)p );
					ws = _mm_add_ps( ws, bs );
					_mm_store_ps( (float *)p, ws );
				}
				break;

			case 2: // add vectors of 4 32-bit singles at cycle
				vector_capacity = 4;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					ws = _mm_load_ps( (const float *)p );
					ws = _mm_add_ss( ws, bs );
					_mm_store_ps( (float *)p, ws );
				}
				break;

			case 3: // div vectors of 4 32-bit singles at cycle
				vector_capacity = 4;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					ws = _mm_load_ps( (const float *)p );
					ws = _mm_div_ps( ws, bs );
					_mm_store_ps( (float *)p, ws );
				}
				break;

			case 4: // div vectors of 4 32-bit singles at cycle
				vector_capacity = 4;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					ws = _mm_load_ps( (const float *)p );
					ws = _mm_div_ss( ws, bs );
					_mm_store_ps( (float *)p, ws );
				}
				break;

			case 5: // mul vectors of 4 32-bit singles at cycle
				vector_capacity = 4;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					ws = _mm_load_ps( (const float *)p );
					ws = _mm_mul_ps( ws, bs );
					_mm_store_ps( (float *)p, ws );
				}
				break;

			case 6: // mul vectors of 4 32-bit singles at cycle
				vector_capacity = 4;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					ws = _mm_load_ps( (const float *)p );
					ws = _mm_mul_ss( ws, bs );
					_mm_store_ps( (float *)p, ws );
				}
				break;

			case 7: // sub vectors of 4 32-bit singles at cycle
				vector_capacity = 4;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					ws = _mm_load_ps( (const float *)p );
					ws = _mm_sub_ps( ws, bs );
					_mm_store_ps( (float *)p, ws );
				}
				break;

			case 8: // sub vectors of 4 32-bit singles at cycle
				vector_capacity = 4;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					ws = _mm_load_ps( (const float *)p );
					ws = _mm_sub_ss( ws, bs );
					_mm_store_ps( (float *)p, ws );
				}
				break;

			default:
				printf( "sse_ai_ps32_bm_thread%u havn't instruction\n", td->tid );

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

void* sse_ai_ps32_bm_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;
	td->vector_offset = 4;

	sprintf( td->name, "sse_aips32th%u", td->tid );
	prctl( PR_SET_NAME, td->name );

	uint64_t alloc_length = ( st_bm_cpt > mt_bm_cpt ? st_bm_cpt : mt_bm_cpt ) * td->vector_offset;
	uint64_t alloc_size = alloc_length * sizeof( float );
	float *ps32 __attribute__((aligned(16))) = (float*)aligned_alloc( 16, alloc_size );
	if ( !ps32 ) perror( "aligned_alloc() error" );

	sse_ai_ps32_bm( td, &pc[ DSP_PC ], ps32, 4 );

	if ( ps32 ) free( ps32 );

	return NULL;
}

void* sse_ai_ps32_cpu_bm_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;
	td->vector_offset = 0;

	sprintf( td->name, "ssecaips32th%u", td->tid );
	prctl( PR_SET_NAME, td->name );

	float ps32[ 4 ] __attribute__((aligned(16))) = { 8, 7, 6, 5 };

	sse_ai_ps32_bm( td, &pc[ CPU_PC ], ps32, 0 );

	return NULL;
}

#endif // !__SIMD_SSE_AI_PS32_BM_H__