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

void* fma_ai_pd64_bm_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;
	uint64_t i, _vi_;
	char name[ 25 ];

	sprintf( name, "fma_aipd64th%u", td->tid );
	prctl( PR_SET_NAME, name );

	vector_capacity = 4;
	uint64_t alloc_length = MT_BM_CYCLES_PER_TIME * vector_capacity;
	uint64_t alloc_size = alloc_length * sizeof( double );
	double *pd64 __attribute__((aligned(32))) = (double*)aligned_alloc( 32, alloc_size );
	if ( !pd64 ) perror( "aligned_alloc() error" );

	bd = _mm_set_pd( 1.11111f, 2.22222f );
	zd = _mm_set_pd( 2.22222f, 1.11111f );
	ad = _mm256_set_pd( 1.11111f, 2.22222f, 3.33333f, 4.44444f );
	yd = _mm256_set_pd( 4.44444f, 3.33333f, 2.22222f, 1.11111f );

	pthread_mutex_lock( &lock );
	while ( (td->instruction == 0) && td->thread_active )
		pthread_cond_wait( &start, &lock );
	pthread_mutex_unlock( &lock );

	while ( td->thread_active ) {

		pc_get( td->cycles_count );

		if ( !td->thread_active ) break;

		switch ( td->instruction ) {

			case 1: // vfmadd132pd vectors of 4 64-bit doubles at cycle
				vector_capacity = 2;
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					wd = _mm_load_pd( (const double *)&pd64[_vi_] );
					wd = _mm_fmadd_pd( wd, bd, zd );
					_mm_store_pd( (double *)&pd64[_vi_], wd );
				}
				break;

			case 2: // vfmadd132sd vectors of 4 64-bit doubles at cycle
				vector_capacity = 2;
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					wd = _mm_load_pd( (const double *)&pd64[_vi_] );
					wd = _mm_fmadd_sd( wd, bd, zd );
					_mm_store_pd( (double *)&pd64[_vi_], wd );
				}
				break;

			case 3: // vfmaddsub132pd vectors of 4 64-bit doubles at cycle
				vector_capacity = 2;
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					wd = _mm_load_pd( (const double *)&pd64[_vi_] );
					wd = _mm_fmaddsub_pd( wd, bd, zd );
					_mm_store_pd( (double *)&pd64[_vi_], wd );
				}
				break;

			case 4: // vfmsub132pd vectors of 4 64-bit doubles at cycle
				vector_capacity = 2;
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					wd = _mm_load_pd( (const double *)&pd64[_vi_] );
					wd = _mm_fmsub_pd( wd, bd, zd );
					_mm_store_pd( (double *)&pd64[_vi_], wd );
				}
				break;

			case 5: // vfmsub132sd vectors of 4 64-bit doubles at cycle
				vector_capacity = 2;
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					wd = _mm_load_pd( (const double *)&pd64[_vi_] );
					wd = _mm_fmsub_sd( wd, bd, zd );
					_mm_store_pd( (double *)&pd64[_vi_], wd );
				}
				break;

			case 6: // vfmsubadd132pd vectors of 4 64-bit doubles at cycle
				vector_capacity = 2;
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					wd = _mm_load_pd( (const double *)&pd64[_vi_] );
					wd = _mm_fmsubadd_pd( wd, bd, zd );
					_mm_store_pd( (double *)&pd64[_vi_], wd );
				}
				break;

			case 7: // vfnmadd132pd vectors of 4 64-bit doubles at cycle
				vector_capacity = 2;
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					wd = _mm_load_pd( (const double *)&pd64[_vi_] );
					wd = _mm_fnmadd_pd( wd, bd, zd );
					_mm_store_pd( (double *)&pd64[_vi_], wd );
				}
				break;

			case 8: // vfnmadd132sd vectors of 4 64-bit doubles at cycle
				vector_capacity = 2;
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					wd = _mm_load_pd( (const double *)&pd64[_vi_] );
					wd = _mm_fnmadd_sd( wd, bd, zd );
					_mm_store_pd( (double *)&pd64[_vi_], wd );
				}
				break;

			case 9: // vfnmsub132pd vectors of 4 64-bit doubles at cycle
				vector_capacity = 2;
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					wd = _mm_load_pd( (const double *)&pd64[_vi_] );
					wd = _mm_fnmsub_pd( wd, bd, zd );
					_mm_store_pd( (double *)&pd64[_vi_], wd );
				}
				break;

			case 10:// vfnmsub132sd vectors of 4 64-bit doubles at cycle
				vector_capacity = 2;
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					wd = _mm_load_pd( (const double *)&pd64[_vi_] );
					wd = _mm_fnmsub_sd( wd, bd, zd );
					_mm_store_pd( (double *)&pd64[_vi_], wd );
				}
				break;

			case 11:// vfmadd132pd vectors of 4 64-bit doubles at cycle
				vector_capacity = 4;
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					vd = _mm256_load_pd( (const double *)&pd64[_vi_] );
					vd = _mm256_fmadd_pd( vd, ad, yd );
					_mm256_store_pd( (double *)&pd64[_vi_], vd );
				}
				break;

			case 12:// vfmaddsub132pd vectors of 4 64-bit doubles at cycle
				vector_capacity = 4;
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					vd = _mm256_load_pd( (const double *)&pd64[_vi_] );
					vd = _mm256_fmaddsub_pd( vd, ad, yd );
					_mm256_store_pd( (double *)&pd64[_vi_], vd );
				}
				break;

			case 13:// vfmsub132pd vectors of 4 64-bit doubles at cycle
				vector_capacity = 4;
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					vd = _mm256_load_pd( (const double *)&pd64[_vi_] );
					vd = _mm256_fmsub_pd( vd, ad, yd );
					_mm256_store_pd( (double *)&pd64[_vi_], vd );
				}
				break;

			case 14:// vfmsubadd132pd vectors of 4 64-bit doubles at cycle
				vector_capacity = 4;
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					vd = _mm256_load_pd( (const double *)&pd64[_vi_] );
					vd = _mm256_fmsubadd_pd( vd, ad, yd );
					_mm256_store_pd( (double *)&pd64[_vi_], vd );
				}
				break;

			case 15:// vfnmadd132pd vectors of 4 64-bit doubles at cycle
				vector_capacity = 4;
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					vd = _mm256_load_pd( (const double *)&pd64[_vi_] );
					vd = _mm256_fnmadd_pd( vd, ad, yd );
					_mm256_store_pd( (double *)&pd64[_vi_], vd );
				}
				break;

			case 16:// vfnmsub132pd vectors of 4 64-bit doubles at cycle
				vector_capacity = 4;
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					vd = _mm256_load_pd( (const double *)&pd64[_vi_] );
					vd = _mm256_fnmsub_pd( vd, ad, yd );
					_mm256_store_pd( (double *)&pd64[_vi_], vd );
				}
				break;

			default:
				printf( "fma_ai_pd64_bm_thread%u havn't instruction\n", td->tid );

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

#endif // !__SIMD_FMA_AI_PD64_BM_H__