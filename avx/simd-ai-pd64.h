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
	char name[ 25 ];
	uint64_t i;

	sprintf( name, "avx_aipd64th%u", td->tid );
	prctl( PR_SET_NAME, name );

	vector_capacity = 4;
	double ALIGN32 di[ vector_capacity ] = { 8, 7, 6, 5 };
	double ALIGN32 da[ vector_capacity ] = { 1, 2, 3, 4 };

	while ( td->thread_active ) {

		pthread_mutex_lock( &lock );
		while ( (td->instruction == 0) && td->thread_active )
			pthread_cond_wait( &start, &lock );
		pthread_mutex_unlock( &lock );

		if ( !td->thread_active ) break;

		ad = _mm256_load_pd( (const double *)da );

		switch ( td->instruction ) {

			case 1: // add vectors of 4 64-bit doubles at cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					vd = _mm256_load_pd( (const double *)di );
					vd = _mm256_add_pd( vd, ad );
					_mm256_store_pd( (double *)di, vd );
				}
				break;

			case 2: // addsub vectors of 4 64-bit doubles at cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					vd = _mm256_load_pd( (const double *)di );
					vd = _mm256_addsub_pd( vd, ad );
					_mm256_store_pd( (double *)di, vd );
				}
				break;

			case 3: // div vectors of 4 64-bit doubles at cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					vd = _mm256_load_pd( (const double *)di );
					vd = _mm256_div_pd( vd, ad );
					_mm256_store_pd( (double *)di, vd );
				}
				break;

			case 4: // hadd vectors of 4 64-bit doubles at cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					vd = _mm256_load_pd( (const double *)di );
					vd = _mm256_hadd_pd( vd, ad );
					_mm256_store_pd( (double *)di, vd );
				}
				break;

			case 5: // hsub vectors of 4 64-bit doubles at cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					vd = _mm256_load_pd( (const double *)di );
					vd = _mm256_hsub_pd( vd, ad );
					_mm256_store_pd( (double *)di, vd );
				}
				break;

			case 6: // mul vectors of 4 64-bit doubles at cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					vd = _mm256_load_pd( (const double *)di );
					vd = _mm256_mul_pd( vd, ad );
					_mm256_store_pd( (double *)di, vd );
				}
				break;

			case 7: // sub vectors of 4 64-bit doubles at cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					vd = _mm256_load_pd( (const double *)di );
					vd = _mm256_sub_pd( vd, ad );
					_mm256_store_pd( (double *)di, vd );
				}
				break;

			default:
				printf( "avx_ai_pd64_bm_thread%u havn't instruction\n", td->tid );

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

#endif // !__SIMD_AVX_AI_PD64_BM_H__