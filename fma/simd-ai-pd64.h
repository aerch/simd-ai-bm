#ifndef __SIMD_FMA_AI_PD64_BM_H__
#define __SIMD_FMA_AI_PD64_BM_H__

const uint8_t fma_ai_pd64_cnt = 16;

const char *fma_ai_pd64_instructions[ fma_ai_pd64_cnt + 1 ] = {
	"SIMD FMA 64-bit Double-Precision Arithmetic Instructions with 128-bit & 256-bit vectors ...",
	"vfmaddXpd\t_mm_fmadd_pd         ",
	"vfmaddXsd\t_mm_fmadd_sd         ",
	"vfmaddsubXpd\t_mm_fmaddsub_pd   ",
	"vfmsubXpd\t_mm_fmsub_pd         ",
	"vfmsubXsd\t_mm_fmsub_sd         ",
	"vfmsubaddXpd\t_mm_fmsubadd_pd   ",
	"vfnmaddXpd\t_mm_fnmadd_pd       ",
	"vfnmaddXsd\t_mm_fnmadd_sd       ",
	"vfnmsubXpd\t_mm_fnmsub_pd       ",
	"vfnmsubXsd\t_mm_fnmsub_sd       ",
	"vfmaddXpd\t_mm256_fmadd_pd      ",
	"vfmaddsubXpd\t_mm256_fmaddsub_pd",
	"vfmsubXpd\t_mm256_fmsub_pd      ",
	"vfmsubaddXpd\t_mm256_fmsubadd_pd",
	"vfnmaddXpd\t_mm256_fnmadd_pd    ",
	"vfnmsubXpd\t_mm256_fnmsub_pd    "
};

inline void fma_ai_pd64_bm( thread_data_t *td,  pc_data_t *pc, double *pd64, uint8_t vector_offset ) {
	int64_t i;
	double *pd64_start __attribute__((aligned(32))) = pd64;
	__m128d wd;
	__m128d bd = _mm_set_pd( 3.33333f, 4.44444f );
	__m128d zd = _mm_set_pd( 1.11111f, 2.22222f );
	__m256d vd;
	__m256d ad = _mm256_set_pd( 1.11111f, 2.22222f, 3.33333f, 4.44444f );
	__m256d yd = _mm256_set_pd( 4.44444f, 3.33333f, 2.22222f, 1.11111f );

	while ( td->thread_active ) {

		pc_get( pc, td->cycles_count );

		if ( !td->thread_active ) break;

		pthread_mutex_lock( &lock );
		evaluating_threads++;
		pthread_mutex_unlock( &lock );

		pd64 = pd64_start;
		td->vector_offset = vector_offset;

		switch ( td->instruction ) {

			case 1: // vfmadd132pd vectors of 4 64-bit doubles at cycle
				vector_capacity = 2;
				for ( i = 0; i < td->cycles_count; i++, pd64 += td->vector_offset) {
					wd = _mm_load_pd( (const double *)pd64 );
					wd = _mm_fmadd_pd( wd, bd, zd );
					_mm_store_pd( (double *)pd64, wd );
				}
				break;

			case 2: // vfmadd132sd vectors of 4 64-bit doubles at cycle
				vector_capacity = 2;
				for ( i = 0; i < td->cycles_count; i++, pd64 += td->vector_offset) {
					wd = _mm_load_pd( (const double *)pd64 );
					wd = _mm_fmadd_sd( wd, bd, zd );
					_mm_store_pd( (double *)pd64, wd );
				}
				break;

			case 3: // vfmaddsub132pd vectors of 4 64-bit doubles at cycle
				vector_capacity = 2;
				for ( i = 0; i < td->cycles_count; i++, pd64 += td->vector_offset) {
					wd = _mm_load_pd( (const double *)pd64 );
					wd = _mm_fmaddsub_pd( wd, bd, zd );
					_mm_store_pd( (double *)pd64, wd );
				}
				break;

			case 4: // vfmsub132pd vectors of 4 64-bit doubles at cycle
				vector_capacity = 2;
				for ( i = 0; i < td->cycles_count; i++, pd64 += td->vector_offset) {
					wd = _mm_load_pd( (const double *)pd64 );
					wd = _mm_fmsub_pd( wd, bd, zd );
					_mm_store_pd( (double *)pd64, wd );
				}
				break;

			case 5: // vfmsub132sd vectors of 4 64-bit doubles at cycle
				vector_capacity = 2;
				for ( i = 0; i < td->cycles_count; i++, pd64 += td->vector_offset) {
					wd = _mm_load_pd( (const double *)pd64 );
					wd = _mm_fmsub_sd( wd, bd, zd );
					_mm_store_pd( (double *)pd64, wd );
				}
				break;

			case 6: // vfmsubadd132pd vectors of 4 64-bit doubles at cycle
				vector_capacity = 2;
				for ( i = 0; i < td->cycles_count; i++, pd64 += td->vector_offset) {
					wd = _mm_load_pd( (const double *)pd64 );
					wd = _mm_fmsubadd_pd( wd, bd, zd );
					_mm_store_pd( (double *)pd64, wd );
				}
				break;

			case 7: // vfnmadd132pd vectors of 4 64-bit doubles at cycle
				vector_capacity = 2;
				for ( i = 0; i < td->cycles_count; i++, pd64 += td->vector_offset) {
					wd = _mm_load_pd( (const double *)pd64 );
					wd = _mm_fnmadd_pd( wd, bd, zd );
					_mm_store_pd( (double *)pd64, wd );
				}
				break;

			case 8: // vfnmadd132sd vectors of 4 64-bit doubles at cycle
				vector_capacity = 2;
				for ( i = 0; i < td->cycles_count; i++, pd64 += td->vector_offset) {
					wd = _mm_load_pd( (const double *)pd64 );
					wd = _mm_fnmadd_sd( wd, bd, zd );
					_mm_store_pd( (double *)pd64, wd );
				}
				break;

			case 9: // vfnmsub132pd vectors of 4 64-bit doubles at cycle
				vector_capacity = 2;
				for ( i = 0; i < td->cycles_count; i++, pd64 += td->vector_offset) {
					wd = _mm_load_pd( (const double *)pd64 );
					wd = _mm_fnmsub_pd( wd, bd, zd );
					_mm_store_pd( (double *)pd64, wd );
				}
				break;

			case 10:// vfnmsub132sd vectors of 4 64-bit doubles at cycle
				vector_capacity = 2;
				for ( i = 0; i < td->cycles_count; i++, pd64 += td->vector_offset) {
					wd = _mm_load_pd( (const double *)pd64 );
					wd = _mm_fnmsub_sd( wd, bd, zd );
					_mm_store_pd( (double *)pd64, wd );
				}
				break;

			case 11:// vfmadd132pd vectors of 4 64-bit doubles at cycle
				vector_capacity = 4;
				for ( i = 0; i < td->cycles_count; i++, pd64 += td->vector_offset) {
					vd = _mm256_load_pd( (const double *)pd64 );
					vd = _mm256_fmadd_pd( vd, ad, yd );
					_mm256_store_pd( (double *)pd64, vd );
				}
				break;

			case 12:// vfmaddsub132pd vectors of 4 64-bit doubles at cycle
				vector_capacity = 4;
				for ( i = 0; i < td->cycles_count; i++, pd64 += td->vector_offset) {
					vd = _mm256_load_pd( (const double *)pd64 );
					vd = _mm256_fmaddsub_pd( vd, ad, yd );
					_mm256_store_pd( (double *)pd64, vd );
				}
				break;

			case 13:// vfmsub132pd vectors of 4 64-bit doubles at cycle
				vector_capacity = 4;
				for ( i = 0; i < td->cycles_count; i++, pd64 += td->vector_offset) {
					vd = _mm256_load_pd( (const double *)pd64 );
					vd = _mm256_fmsub_pd( vd, ad, yd );
					_mm256_store_pd( (double *)pd64, vd );
				}
				break;

			case 14:// vfmsubadd132pd vectors of 4 64-bit doubles at cycle
				vector_capacity = 4;
				for ( i = 0; i < td->cycles_count; i++, pd64 += td->vector_offset) {
					vd = _mm256_load_pd( (const double *)pd64 );
					vd = _mm256_fmsubadd_pd( vd, ad, yd );
					_mm256_store_pd( (double *)pd64, vd );
				}
				break;

			case 15:// vfnmadd132pd vectors of 4 64-bit doubles at cycle
				vector_capacity = 4;
				for ( i = 0; i < td->cycles_count; i++, pd64 += td->vector_offset) {
					vd = _mm256_load_pd( (const double *)pd64 );
					vd = _mm256_fnmadd_pd( vd, ad, yd );
					_mm256_store_pd( (double *)pd64, vd );
				}
				break;

			case 16:// vfnmsub132pd vectors of 4 64-bit doubles at cycle
				vector_capacity = 4;
				for ( i = 0; i < td->cycles_count; i++, pd64 += td->vector_offset) {
					vd = _mm256_load_pd( (const double *)pd64 );
					vd = _mm256_fnmsub_pd( vd, ad, yd );
					_mm256_store_pd( (double *)pd64, vd );
				}
				break;

			default:
				printf( "fma_ai_pd64_bm_thread%u havn't instruction\n", td->tid );

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

void* fma_ai_pd64_bm_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;

	sprintf( td->name, "fma_aipd64th%u", td->tid );
	prctl( PR_SET_NAME, td->name );

	vector_capacity = 4;
	uint64_t alloc_length = ( ST_BM_CYCLES_PER_TIME > MT_BM_CYCLES_PER_TIME ? ST_BM_CYCLES_PER_TIME : MT_BM_CYCLES_PER_TIME ) * vector_capacity;
	uint64_t alloc_size = alloc_length * sizeof( double );
	double *pd64 __attribute__((aligned(32))) = (double*)aligned_alloc( 32, alloc_size );
	if ( !pd64 ) perror( "aligned_alloc() error" );

	fma_ai_pd64_bm( td, &pc[ DSP_PC ], pd64, vector_capacity );

	if ( pd64 ) free( pd64 );

	return NULL;
}

void* fma_ai_pd64_cpu_bm_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;

	sprintf( td->name, "fmacaipd64th%u", td->tid );
	prctl( PR_SET_NAME, td->name );

	vector_capacity = 4;
	double pd64[ 4 ] ALIGN32 = { 8, 6, 4, 2 };

	fma_ai_pd64_bm( td, &pc[ CPU_PC ], pd64, 0 );

	return NULL;
}

#endif // !__SIMD_FMA_AI_PD64_BM_H__