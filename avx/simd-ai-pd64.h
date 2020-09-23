#ifndef __SIMD_AVX_AI_PD64_BM_H__
#define __SIMD_AVX_AI_PD64_BM_H__

const uint8_t avx_ai_pd64_cnt = 7;

const char *avx_ai_pd64_instructions[ avx_ai_pd64_cnt + 1 ] = {
	"SIMD AVX 64-bit Double-Precision Arithmetic Instructions with 256-bit vectors ...",
	"vaddpd\t_mm256_add_pd()      ",
	"vaddsubpd\t_mm256_addsub_pd()",
	"vdivpd\t_mm256_div_pd()      ",
	"vhaddpd\t_mm256_hadd_pd()    ",
	"vhsubpd\t_mm256_hsub_pd()    ",
	"vmulpd\t_mm256_mul_pd()      ",
	"vsubpd\t_mm256_sub_pd()      "
};

void* avx_ai_pd64_bm_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;
	uint64_t i, _vi_;
	char name[ 25 ];

	sprintf( name, "avx_aipd64th%u", td->tid );
	prctl( PR_SET_NAME, name );

	vector_capacity = 4;
	uint64_t alloc_length = MT_BM_CYCLES_PER_TIME * vector_capacity;
	uint64_t alloc_size = alloc_length * sizeof( double );
	double *pd64 __attribute__((aligned(32))) = (double*)aligned_alloc( 32, alloc_size );
	if ( !pd64 ) perror( "aligned_alloc() error" );

	ad = _mm256_set_pd( 1.11111f, 2.22222f, 3.33333f, 4.44444f );

	pthread_mutex_lock( &lock );
	while ( (td->instruction == 0) && td->thread_active )
		pthread_cond_wait( &start, &lock );
	pthread_mutex_unlock( &lock );

	while ( td->thread_active ) {

		pc_get( td->cycles_count );

		if ( !td->thread_active ) break;

		switch ( td->instruction ) {

			case 1: // add vectors of 4 64-bit doubles at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					vd = _mm256_load_pd( (const double *)&pd64[_vi_] );
					vd = _mm256_add_pd( vd, ad );
					_mm256_store_pd( (double *)&pd64[_vi_], vd );
				}
				break;

			case 2: // addsub vectors of 4 64-bit doubles at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					vd = _mm256_load_pd( (const double *)&pd64[_vi_] );
					vd = _mm256_addsub_pd( vd, ad );
					_mm256_store_pd( (double *)&pd64[_vi_], vd );
				}
				break;

			case 3: // div vectors of 4 64-bit doubles at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					vd = _mm256_load_pd( (const double *)&pd64[_vi_] );
					vd = _mm256_div_pd( vd, ad );
					_mm256_store_pd( (double *)&pd64[_vi_], vd );
				}
				break;

			case 4: // hadd vectors of 4 64-bit doubles at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					vd = _mm256_load_pd( (const double *)&pd64[_vi_] );
					vd = _mm256_hadd_pd( vd, ad );
					_mm256_store_pd( (double *)&pd64[_vi_], vd );
				}
				break;

			case 5: // hsub vectors of 4 64-bit doubles at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					vd = _mm256_load_pd( (const double *)&pd64[_vi_] );
					vd = _mm256_hsub_pd( vd, ad );
					_mm256_store_pd( (double *)&pd64[_vi_], vd );
				}
				break;

			case 6: // mul vectors of 4 64-bit doubles at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					vd = _mm256_load_pd( (const double *)&pd64[_vi_] );
					vd = _mm256_mul_pd( vd, ad );
					_mm256_store_pd( (double *)&pd64[_vi_], vd );
				}
				break;

			case 7: // sub vectors of 4 64-bit doubles at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					vd = _mm256_load_pd( (const double *)&pd64[_vi_] );
					vd = _mm256_sub_pd( vd, ad );
					_mm256_store_pd( (double *)&pd64[_vi_], vd );
				}
				break;

			default:
				printf( "avx_ai_pd64_bm_thread%u havn't instruction\n", td->tid );

		}

		pthread_mutex_lock( &lock );
		pthread_cond_signal( &stop );
		pthread_mutex_unlock( &lock );

	}

	pthread_mutex_lock( &lock );
	active_threads--;
	pthread_cond_signal( &finish );
	pthread_mutex_unlock( &lock );

	if ( pd64 )
		free( pd64 );

	return NULL;
}

#endif // !__SIMD_AVX_AI_PD64_BM_H__