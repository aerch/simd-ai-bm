#ifndef __VARS_H__
#define __VARS_H__

typedef struct thread_data {
	uint16_t	tid;
	pthread_t	th;
	pthread_t	cpu_th;
	uint8_t		instruction;
	uint8_t		vector_offset;
	int64_t		cycles_count;
	bool		thread_active;
	char		name[ 25 ];
} thread_data_t;

int32_t		result;
FILE		*stream = NULL;
char		_str_[ 1024 ];

char		brand_string[ 50 ];
char		current_path[ PATH_MAX ];

uint64_t	cycles_count = CYCLES_COUNT;	// 1,000,000,000 - 10,000,000,000

uint8_t 	available_processors;		// system's available processor threads
uint8_t 	vector_capacity;		// simd vector's capacity
uint16_t 	threads_count;			// threads number
uint16_t	active_threads;			// active threads number
uint16_t	evaluating_threads;		// evaluating threads number

double		total_time;
double		total_tps;
double		cpu_time;

double		simd_ai_st_bm;
double		simd_ai_mt_bm;
double		simd_ai_mt_bm_rate;

// __m256		as, vs, ys;
// __m256d		ad, vd, yd;
// // __m256i		ai, vi;

// __m128		bs, ws, zs;
// __m128d		bd, wd, zd;
// __m128i		bi, wi;

// __m64		ci, xi;

pthread_mutex_t	lock;
pthread_cond_t	stop;
pthread_cond_t	finish;

thread_data_t	td[ 2 ][ MAX_THR_CNT ];

pc_data_t	pc[ 2 ];

#endif // !__VARS_H__