#ifndef __SIMD_SSE2_AI_PD64_BM_H__
#define __SIMD_SSE2_AI_PD64_BM_H__

const uint8_t sse2_ai_pd64_cnt = 8;

const char *sse2_ai_pd64_instructions[ sse2_ai_pd64_cnt + 1 ] = {
	"SIMD SSE2 64-bit Double-Precision Arithmetic Instructions with 128-bit vectors ...",
	"addpd   \t_mm_add_pd()    ",
	"addsd   \t_mm_add_sd()    ",
	"divpd   \t_mm_div_pd()    ",
	"divsd   \t_mm_div_sd()    ",
	"mulpd   \t_mm_mul_pd()    ",
	"mulsd   \t_mm_mul_sd()    ",
	"subpd   \t_mm_sub_pd()    ",
	"subsd   \t_mm_sub_sd()    "
};

void* sse2_ai_pd64_bm_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;
	uint64_t i, _vi_;
	char name[ 25 ];

	sprintf( name, "sse2_aipd64th%u", td->tid );
	prctl( PR_SET_NAME, name );

	vector_capacity = 2;
	uint64_t alloc_length = MT_BM_CYCLES_PER_TIME * vector_capacity;
	uint64_t alloc_size = alloc_length * sizeof( double );
	double *pd64 __attribute__((aligned(16))) = (double*)aligned_alloc( 16, alloc_size );
	if ( !pd64 ) perror( "aligned_alloc() error" );

	bd = _mm_set_pd( 1.11111f, 2.22222f );

	pthread_mutex_lock( &lock );
	while ( (td->instruction == 0) && td->thread_active )
		pthread_cond_wait( &start, &lock );
	pthread_mutex_unlock( &lock );

	while ( td->thread_active ) {

		pc_get( td->cycles_count );

		if ( !td->thread_active ) break;

		switch ( td->instruction ) {

			case 1: // add vectors of 2 64-bit doubles at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					wd = _mm_load_pd( (const double *)&pd64[_vi_] );
					wd = _mm_add_pd( wd, bd );
					_mm_store_pd( (double *)&pd64[_vi_], wd );
				}
				break;

			case 2: // add vectors of 2 64-bit doubles at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					wd = _mm_load_pd( (const double *)&pd64[_vi_] );
					wd = _mm_add_sd( wd, bd );
					_mm_store_pd( (double *)&pd64[_vi_], wd );
				}
				break;

			case 3: // div vectors of 2 64-bit doubles at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					wd = _mm_load_pd( (const double *)&pd64[_vi_] );
					wd = _mm_div_pd( wd, bd );
					_mm_store_pd( (double *)&pd64[_vi_], wd );
				}
				break;

			case 4: // div vectors of 2 64-bit doubles at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					wd = _mm_load_pd( (const double *)&pd64[_vi_] );
					wd = _mm_div_sd( wd, bd );
					_mm_store_pd( (double *)&pd64[_vi_], wd );
				}
				break;

			case 5: // mul vectors of 2 64-bit doubles at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					wd = _mm_load_pd( (const double *)&pd64[_vi_] );
					wd = _mm_mul_pd( wd, bd );
					_mm_store_pd( (double *)&pd64[_vi_], wd );
				}
				break;

			case 6: // mul vectors of 2 64-bit doubles at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					wd = _mm_load_pd( (const double *)&pd64[_vi_] );
					wd = _mm_mul_sd( wd, bd );
					_mm_store_pd( (double *)&pd64[_vi_], wd );
				}
				break;

			case 7: // sub vectors of 2 64-bit doubles at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					wd = _mm_load_pd( (const double *)&pd64[_vi_] );
					wd = _mm_sub_pd( wd, bd );
					_mm_store_pd( (double *)&pd64[_vi_], wd );
				}
				break;

			case 8: // sub vectors of 2 64-bit doubles at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					wd = _mm_load_pd( (const double *)&pd64[_vi_] );
					wd = _mm_sub_sd( wd, bd );
					_mm_store_pd( (double *)&pd64[_vi_], wd );
				}
				break;

			default:
				printf( "sse2_ai_pd64_bm_thread%u havn't instruction\n", td->tid );

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

#endif // !__SIMD_SSE2_AI_PD64_BM_H__