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

void* avx_ai_ps32_bm_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;
	char name[ 25 ];
	uint64_t i;

	sprintf( name, "avx_aips32th%u", td->tid );
	prctl( PR_SET_NAME, name );

	vector_capacity = 8;
	float ALIGN32 si[ vector_capacity ] = { 8, 7, 6, 5, 4, 3, 2, 1 };
	float ALIGN32 sa[ vector_capacity ] = { 1, 2, 3, 4, 5, 6, 7, 8 };

	while ( td->thread_active ) {

		pthread_mutex_lock( &lock );
		while ( (td->instruction == 0) && td->thread_active )
			pthread_cond_wait( &start, &lock );
		pthread_mutex_unlock( &lock );

		if ( !td->thread_active ) break;

		as = _mm256_load_ps( (const float *)sa );

		switch ( td->instruction ) {

			case 1: // add vectors of 8 32-bit singles at cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					vs = _mm256_load_ps( (const float *)si );
					vs = _mm256_add_ps( vs, as );
					_mm256_store_ps( (float *)si, vs );
				}
				break;

			case 2: // addsub vectors of 8 32-bit singles at cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					vs = _mm256_load_ps( (const float *)si );
					vs = _mm256_addsub_ps( vs, as );
					_mm256_store_ps( (float *)si, vs );
				}
				break;

			case 3: // div vectors of 8 32-bit singles at cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					vs = _mm256_load_ps( (const float *)si );
					vs = _mm256_div_ps( vs, as );
					_mm256_store_ps( (float *)si, vs );
				}
				break;

			case 4: // dp vectors of 8 32-bit singles at cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					vs = _mm256_load_ps( (const float *)si );
					vs = _mm256_dp_ps( vs, as, 0x0f );
					_mm256_store_ps( (float *)si, vs );
				}
				break;

			case 5: // hadd vectors of 8 32-bit singles at cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					vs = _mm256_load_ps( (const float *)si );
					vs = _mm256_hadd_ps( vs, as );
					_mm256_store_ps( (float *)si, vs );
				}
				break;

			case 6: // hsub vectors of 8 32-bit singles at cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					vs = _mm256_load_ps( (const float *)si );
					vs = _mm256_hsub_ps( vs, as );
					_mm256_store_ps( (float *)si, vs );
				}
				break;

			case 7: // mul vectors of 8 32-bit singles at cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					vs = _mm256_load_ps( (const float *)si );
					vs = _mm256_mul_ps( vs, as );
					_mm256_store_ps( (float *)si, vs );
				}
				break;

			case 8: // sub vectors of 8 32-bit singles at cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					vs = _mm256_load_ps( (const float *)si );
					vs = _mm256_sub_ps( vs, as );
					_mm256_store_ps( (float *)si, vs );
				}
				break;

			default:
				printf( "avx_ai_ps32_bm_thread%u havn't instruction\n", td->tid );

		}

		pthread_mutex_lock( &lock );
		td->instruction = 0;
		SET_BIT( active_threads_flag, td->tid, 0 );
		if ( !active_threads_flag )
			pthread_cond_signal( &stop );
		pthread_mutex_unlock( &lock );

	}

	return NULL;
}

#endif // !__SIMD_AVX_AI_PS32_BM_H__