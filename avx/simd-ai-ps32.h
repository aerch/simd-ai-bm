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
	uint64_t i, _vi_;
	char name[ 25 ];

	sprintf( name, "avx_aips32th%u", td->tid );
	prctl( PR_SET_NAME, name );

	vector_capacity = 8;
	// int64_t alloc_size = td->cycles_count * vector_capacity * sizeof( float );
	int64_t alloc_length = td->cycles_count * vector_capacity;
	int64_t alloc_size = (alloc_length < BM_CYCLES_PER_TIME ? alloc_length : BM_CYCLES_PER_TIME ) * sizeof( float );
	float *ps32 __attribute__((aligned(32))) = (float*)aligned_alloc( 32, alloc_size );
	if ( !ps32 ) perror( "aligned_alloc() error" );

	as = _mm256_set_ps( 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f );

	while ( td->thread_active ) {

		pthread_mutex_lock( &lock );
		while ( (td->instruction == 0) && td->thread_active )
			pthread_cond_wait( &start, &lock );
		pthread_mutex_unlock( &lock );

		if ( !td->thread_active ) break;

		switch ( td->instruction ) {

			case 1: // add vectors of 8 32-bit singles at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					if ( _vi_ >= BM_CYCLES_PER_TIME ) _vi_ = 0;
					vs = _mm256_load_ps( (const float *)&ps32[_vi_] );
					vs = _mm256_add_ps( vs, as );
					_mm256_store_ps( (float *)&ps32[_vi_], vs );
				}
				break;

			case 2: // addsub vectors of 8 32-bit singles at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					if ( _vi_ >= BM_CYCLES_PER_TIME ) _vi_ = 0;
					vs = _mm256_load_ps( (const float *)&ps32[_vi_] );
					vs = _mm256_addsub_ps( vs, as );
					_mm256_store_ps( (float *)&ps32[_vi_], vs );
				}
				break;

			case 3: // div vectors of 8 32-bit singles at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					if ( _vi_ >= BM_CYCLES_PER_TIME ) _vi_ = 0;
					vs = _mm256_load_ps( (const float *)&ps32[_vi_] );
					vs = _mm256_div_ps( vs, as );
					_mm256_store_ps( (float *)&ps32[_vi_], vs );
				}
				break;

			case 4: // dp vectors of 8 32-bit singles at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					if ( _vi_ >= BM_CYCLES_PER_TIME ) _vi_ = 0;
					vs = _mm256_load_ps( (const float *)&ps32[_vi_] );
					vs = _mm256_dp_ps( vs, as, 0x0f );
					_mm256_store_ps( (float *)&ps32[_vi_], vs );
				}
				break;

			case 5: // hadd vectors of 8 32-bit singles at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					if ( _vi_ >= BM_CYCLES_PER_TIME ) _vi_ = 0;
					vs = _mm256_load_ps( (const float *)&ps32[_vi_] );
					vs = _mm256_hadd_ps( vs, as );
					_mm256_store_ps( (float *)&ps32[_vi_], vs );
				}
				break;

			case 6: // hsub vectors of 8 32-bit singles at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					if ( _vi_ >= BM_CYCLES_PER_TIME ) _vi_ = 0;
					vs = _mm256_load_ps( (const float *)&ps32[_vi_] );
					vs = _mm256_hsub_ps( vs, as );
					_mm256_store_ps( (float *)&ps32[_vi_], vs );
				}
				break;

			case 7: // mul vectors of 8 32-bit singles at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					if ( _vi_ >= BM_CYCLES_PER_TIME ) _vi_ = 0;
					vs = _mm256_load_ps( (const float *)&ps32[_vi_] );
					vs = _mm256_mul_ps( vs, as );
					_mm256_store_ps( (float *)&ps32[_vi_], vs );
				}
				break;

			case 8: // sub vectors of 8 32-bit singles at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					if ( _vi_ >= BM_CYCLES_PER_TIME ) _vi_ = 0;
					vs = _mm256_load_ps( (const float *)&ps32[_vi_] );
					vs = _mm256_sub_ps( vs, as );
					_mm256_store_ps( (float *)&ps32[_vi_], vs );
				}
				break;

			default:
				printf( "avx_ai_ps32_bm_thread%u havn't instruction\n", td->tid );

		}

		pthread_mutex_lock( &lock );
		td->instruction = 0;
		SET_BIT( active_threads, td->tid, 0 );
		if ( !active_threads )
			pthread_cond_signal( &stop );
		pthread_mutex_unlock( &lock );

	}

	if ( ps32 )
		free( ps32 );

	return NULL;
}

#endif // !__SIMD_AVX_AI_PS32_BM_H__