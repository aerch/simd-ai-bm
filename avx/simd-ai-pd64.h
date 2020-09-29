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

inline void avx_ai_pd64_bm( thread_data_t *td,  pc_data_t *pc, double *pd64, uint8_t vector_offset ) {
	int64_t i;
	double *pd64_start __attribute__((aligned(32))) = pd64;
	__m256d vd;
	__m256d ad = _mm256_set_pd( 1.11111f, 2.22222f, 3.33333f, 4.44444f );

	while ( td->thread_active ) {

		pc_get( pc, td->cycles_count );

		if ( !td->thread_active ) break;

		pthread_mutex_lock( &lock );
		evaluating_threads++;
		pthread_mutex_unlock( &lock );

		pd64 = pd64_start;
		td->vector_offset = vector_offset;

		switch ( td->instruction ) {

			case 1: // add vectors of 4 64-bit doubles at cycle
				for ( i = 0; i < td->cycles_count; i++, pd64 += td->vector_offset ) {
					vd = _mm256_load_pd( (const double *)pd64 );
					vd = _mm256_add_pd( vd, ad );
					_mm256_store_pd( (double *)pd64, vd );
				}
				break;

			case 2: // addsub vectors of 4 64-bit doubles at cycle
				for ( i = 0; i < td->cycles_count; i++, pd64 += td->vector_offset ) {
					vd = _mm256_load_pd( (const double *)pd64 );
					vd = _mm256_addsub_pd( vd, ad );
					_mm256_store_pd( (double *)pd64, vd );
				}
				break;

			case 3: // div vectors of 4 64-bit doubles at cycle
				for ( i = 0; i < td->cycles_count; i++, pd64 += td->vector_offset ) {
					vd = _mm256_load_pd( (const double *)pd64 );
					vd = _mm256_div_pd( vd, ad );
					_mm256_store_pd( (double *)pd64, vd );
				}
				break;

			case 4: // hadd vectors of 4 64-bit doubles at cycle
				for ( i = 0; i < td->cycles_count; i++, pd64 += td->vector_offset ) {
					vd = _mm256_load_pd( (const double *)pd64 );
					vd = _mm256_hadd_pd( vd, ad );
					_mm256_store_pd( (double *)pd64, vd );
				}
				break;

			case 5: // hsub vectors of 4 64-bit doubles at cycle
				for ( i = 0; i < td->cycles_count; i++, pd64 += td->vector_offset ) {
					vd = _mm256_load_pd( (const double *)pd64 );
					vd = _mm256_hsub_pd( vd, ad );
					_mm256_store_pd( (double *)pd64, vd );
				}
				break;

			case 6: // mul vectors of 4 64-bit doubles at cycle
				for ( i = 0; i < td->cycles_count; i++, pd64 += td->vector_offset ) {
					vd = _mm256_load_pd( (const double *)pd64 );
					vd = _mm256_mul_pd( vd, ad );
					_mm256_store_pd( (double *)pd64, vd );
				}
				break;

			case 7: // sub vectors of 4 64-bit doubles at cycle
				for ( i = 0; i < td->cycles_count; i++, pd64 += td->vector_offset ) {
					vd = _mm256_load_pd( (const double *)pd64 );
					vd = _mm256_sub_pd( vd, ad );
					_mm256_store_pd( (double *)pd64, vd );
				}
				break;

			default:
				printf( "avx_ai_pd64_bm_thread%u havn't instruction\n", td->tid );

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

void* avx_ai_pd64_bm_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;

	sprintf( td->name, "avx_aipd64th%u", td->tid );
	prctl( PR_SET_NAME, td->name );

	vector_capacity = 4;
	uint64_t alloc_length = ( ST_BM_CYCLES_PER_TIME > MT_BM_CYCLES_PER_TIME ? ST_BM_CYCLES_PER_TIME : MT_BM_CYCLES_PER_TIME ) * vector_capacity;
	uint64_t alloc_size = alloc_length * sizeof( double );
	double *pd64 __attribute__((aligned(32))) = (double*)aligned_alloc( 32, alloc_size );
	if ( !pd64 ) perror( "aligned_alloc() error" );

	avx_ai_pd64_bm( td, &pc[ DSP_PC ], pd64, vector_capacity );

	if ( pd64 ) free( pd64 );

	return NULL;
}

void* avx_ai_pd64_cpu_bm_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;

	sprintf( td->name, "avxcaipd64th%u", td->tid );
	prctl( PR_SET_NAME, td->name );

	vector_capacity = 4;
	double pd64[ 4 ] ALIGN32 = { 8, 6, 4, 2 };

	avx_ai_pd64_bm( td, &pc[ CPU_PC ], pd64, 0 );

	return NULL;
}

#endif // !__SIMD_AVX_AI_PD64_BM_H__