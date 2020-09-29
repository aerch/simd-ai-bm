#ifndef __SIMD_AVX_AI_PS32_BM_H__
#define __SIMD_AVX_AI_PS32_BM_H__

const uint8_t avx_ai_ps32_cnt = 8;

const char *avx_ai_ps32_instructions[ avx_ai_ps32_cnt + 1 ] = {
	"SIMD AVX 32-bit Single-Precision Arithmetic Instructions with 256-bit vectors ...",
	"vaddps\t_mm256_add_ps()      ",
	"vaddsubps\t_mm256_addsub_ps()",
	"vdivps\t_mm256_div_ps()      ",
	"vdpps\t_mm256_dp_ps()        ",
	"vhaddps\t_mm256_hadd_ps()    ",
	"vhsubps\t_mm256_hsub_ps()    ",
	"vmulps\t_mm256_mul_ps()      ",
	"vsubps\t_mm256_sub_ps()      "
};

inline void avx_ai_ps32_bm( thread_data_t *td,  pc_data_t *pc, float *ps32, uint8_t vector_offset ) {
	int64_t i;
	float *ps32_start __attribute__((aligned(32))) = ps32;
	__m256 vs;
	__m256 as = _mm256_set_ps( 1.11111f, 2.22222f, 3.33333f, 4.44444f, 5.55555f, 6.66666f, 7.77777f, 8.88888f );

	while ( td->thread_active ) {

		pc_get( pc, td->cycles_count );

		if ( !td->thread_active ) break;

		pthread_mutex_lock( &lock );
		evaluating_threads++;
		pthread_mutex_unlock( &lock );

		ps32 = ps32_start;
		td->vector_offset = vector_offset;

		switch ( td->instruction ) {

			case 1: // add vectors of 8 32-bit singles at cycle
				for ( i = 0; i < td->cycles_count; i++, ps32 += td->vector_offset ) {
					vs = _mm256_load_ps( (const float *)ps32 );
					vs = _mm256_add_ps( vs, as );
					_mm256_store_ps( (float *)ps32, vs );
				}
				break;

			case 2: // addsub vectors of 8 32-bit singles at cycle
				for ( i = 0; i < td->cycles_count; i++, ps32 += td->vector_offset ) {
					vs = _mm256_load_ps( (const float *)ps32 );
					vs = _mm256_addsub_ps( vs, as );
					_mm256_store_ps( (float *)ps32, vs );
				}
				break;

			case 3: // div vectors of 8 32-bit singles at cycle
				for ( i = 0; i < td->cycles_count; i++, ps32 += td->vector_offset ) {
					vs = _mm256_load_ps( (const float *)ps32 );
					vs = _mm256_div_ps( vs, as );
					_mm256_store_ps( (float *)ps32, vs );
				}
				break;

			case 4: // dp vectors of 8 32-bit singles at cycle
				for ( i = 0; i < td->cycles_count; i++, ps32 += td->vector_offset ) {
					vs = _mm256_load_ps( (const float *)ps32 );
					vs = _mm256_dp_ps( vs, as, 0x0f );
					_mm256_store_ps( (float *)ps32, vs );
				}
				break;

			case 5: // hadd vectors of 8 32-bit singles at cycle
				for ( i = 0; i < td->cycles_count; i++, ps32 += td->vector_offset ) {
					vs = _mm256_load_ps( (const float *)ps32 );
					vs = _mm256_hadd_ps( vs, as );
					_mm256_store_ps( (float *)ps32, vs );
				}
				break;

			case 6: // hsub vectors of 8 32-bit singles at cycle
				for ( i = 0; i < td->cycles_count; i++, ps32 += td->vector_offset ) {
					vs = _mm256_load_ps( (const float *)ps32 );
					vs = _mm256_hsub_ps( vs, as );
					_mm256_store_ps( (float *)ps32, vs );
				}
				break;

			case 7: // mul vectors of 8 32-bit singles at cycle
				for ( i = 0; i < td->cycles_count; i++, ps32 += td->vector_offset ) {
					vs = _mm256_load_ps( (const float *)ps32 );
					vs = _mm256_mul_ps( vs, as );
					_mm256_store_ps( (float *)ps32, vs );
				}
				break;

			case 8: // sub vectors of 8 32-bit singles at cycle
				for ( i = 0; i < td->cycles_count; i++, ps32 += td->vector_offset ) {
					vs = _mm256_load_ps( (const float *)ps32 );
					vs = _mm256_sub_ps( vs, as );
					_mm256_store_ps( (float *)ps32, vs );
				}
				break;

			default:
				printf( "avx_ai_ps32_bm_thread%u havn't instruction\n", td->tid );

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

void* avx_ai_ps32_bm_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;

	sprintf( td->name, "avx_aips32th%u", td->tid );
	prctl( PR_SET_NAME, td->name );

	vector_capacity = 8;
	uint64_t alloc_length = ( ST_BM_CYCLES_PER_TIME > MT_BM_CYCLES_PER_TIME ? ST_BM_CYCLES_PER_TIME : MT_BM_CYCLES_PER_TIME ) * vector_capacity;
	uint64_t alloc_size = alloc_length * sizeof( float );
	float *ps32 __attribute__((aligned(32))) = (float*)aligned_alloc( 32, alloc_size );
	if ( !ps32 ) perror( "aligned_alloc() error" );

	avx_ai_ps32_bm( td, &pc[ DSP_PC ], ps32, vector_capacity );

	if ( ps32 ) free( ps32 );

	return NULL;
}

void* avx_ai_ps32_cpu_bm_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;

	sprintf( td->name, "avxcaips32th%u", td->tid );
	prctl( PR_SET_NAME, td->name );

	vector_capacity = 8;
	float ps32[ 8 ] ALIGN32 = { 8, 7, 6, 5, 4, 3, 2, 1 };

	avx_ai_ps32_bm( td, &pc[ CPU_PC ], ps32, 0 );

	return NULL;
}

#endif // !__SIMD_AVX_AI_PS32_BM_H__