#ifndef __VARS_H__
#define __VARS_H__

typedef struct thread_data {
	pthread_t	th;
	uint16_t	tid;
	uint8_t		instruction;
	uint64_t	cycles_count;
	bool		thread_active;
} thread_data_t;

int32_t		result;
FILE		*stream = NULL;
char		_str_[ 1024 ];
char		current_path[ PATH_MAX ];

uint64_t	cycles_count = CYCLES_COUNT;	// 1,000,000,000 - 10,000,000,000

uint8_t 	available_processors;		// available processor threads in system
uint8_t 	vector_capacity;		// simd vector's capacity
uint16_t 	threads_count;			// current threads number
uint16_t	active_threads;

double		total_time;
double		total_tps;

double		simd_ai_st_bm;
double		simd_ai_mt_bm;
double		correlation;

__m256		as, vs, ys;
__m256d		ad, vd, yd;
__m256i		ai, vi;

__m128		bs, ws, zs;
__m128d		bd, wd, zd;
__m128i		bi, wi;

__m64		ci, xi;

pthread_mutex_t	lock;
pthread_cond_t	start;
pthread_cond_t	stop;
pthread_cond_t	finish;

thread_data_t	td[ MAX_THR_CNT ];

#endif // !__VARS_H__