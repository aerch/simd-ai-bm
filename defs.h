#ifndef __DEFINES_H__
#define __DEFINES_H__

#define ALIGN8  __attribute__((aligned(8)))	// to simplify the alignment declaration on variables on a 8-byte boundary
#define ALIGN16 __attribute__((aligned(16)))	// to simplify the alignment declaration on variables on a 16-byte boundary
#define ALIGN32 __attribute__((aligned(32)))	// to simplify the alignment declaration on variables on a 32-byte boundary

#define MAX_THR_CNT	128			// maximum value is 128 threads

#ifdef THREADSCOUNT
#define THREADS_COUNT	THREADSCOUNT		// 2 - 128
#else
#define THREADS_COUNT	MAX_THR_CNT
#endif

#ifdef THREADSCOUNT
#define CYCLES_COUNT	CYCLESCOUNT		// 1,000,000 - 10,000,000,000
#else
#define CYCLES_COUNT	1000000000
#endif

#define _BMARK_ON_ clock_gettime(CLOCK_REALTIME, &t1);
#define _BMARK_OFF(cycle) clock_gettime(CLOCK_REALTIME, &t2); \
	diff = (double)((double)t2.tv_sec + (double)t2.tv_nsec/1.0e9) - ((double)t1.tv_sec + (double)t1.tv_nsec/1.0e9); \
	cycle = (double)diff;

#define _BIT(b) (1<<(b))					///< битовый сдвиг влево на b позиций
#define TEST(n,b) (((n)&_BIT(b))!=0)				///< проверка, что b-ый бит числа n - ненулевой
#define SET_BIT(n,b,value) (n) ^= ((-value)^(n)) & (_BIT(b))	///< установка бита из позиции n в позицию b числа value
#define CHECK(n,b) (((n)&_BIT(b))!=0)				///< проверка, что b-ый бит числа n - ненулевой

#define BLACK		"\033[30;1m"
#define BGBLACK		"\033[37;1;40m"
#define RED		"\033[31;1m"
#define BGRED		"\033[37;1;41m"
#define GREEN		"\033[32;1m"
#define BGGREEN		"\033[37;1;42m"
#define YELLOW		"\033[33;1m"
#define BGYELLOW	"\033[30;1;43m"
#define BLUE		"\033[34;1m"
#define BGBLUE		"\033[37;1;44m"
#define PURPLE		"\033[35;1m"
#define BGPURPLE	"\033[37;1;45m"
#define CYAN		"\033[36;1m"
#define BGCYAN		"\033[37;1;46m"
#define WHITE		"\033[37;1m"
#define THINW		"\033[38;1m"
#define WHITE_		"\033[39;1m"
#define BBLACK		"\033[40;1m"
#define BRED		"\033[41;1m"
#define BGREEN		"\033[42;1m"
#define BYELLOW		"\033[43;1m"
#define BBLUE		"\033[44;1m"
#define BPURPLE		"\033[45;1m"
#define BCYAN		"\033[46;1m"
#define BWHITE		"\033[47;1m"
#define BTHINW		"\033[48;1m"
#define BWHITE_		"\033[49;1m"
#define OFF		"\033[0m"

#endif // !__DEFINES_H__