// Буфер по классической схеме "поставщик-потребитель"
#ifndef __PRODUCER_CONSUMER_H__
#define __PRODUCER_CONSUMER_H__

#define PC_STATE_ACTIVE 0
#define PC_STATE_STOP   1

// Структура данных буфера по классической схеме "поставщик-потребитель"
typedef struct pc_data {
	pthread_mutex_t	lock;		// мьютекс обеспечивающий ексклюзивный доступ к буферу
	pthread_cond_t	notempty;	// сигнал состояния - буфер непуст
	pthread_cond_t	notfull;	// сигнал состояния - буфер неполон
	int32_t 	readpos;	// индекс чтения из буфера
	int32_t 	writepos;	// индекс запсиси в буфер
	int32_t 	num;		// колличество блоков буфера
	int32_t		state;		// текущее состояние буфера
	int64_t 	*cycles;	// массив из продконс-буферов
} pc_data_t;

// Функция запуска буфера
inline void pc_start( pc_data_t *pc ) {
	pthread_mutex_lock(&pc->lock);
	pc->readpos = 0;
	pc->writepos = 0;
	pc->state = PC_STATE_ACTIVE;
	pthread_mutex_unlock(&pc->lock);
	return;
}

// Функция останова буфера
inline void pc_stop( pc_data_t *pc ) {
	pthread_mutex_lock(&pc->lock);
	pc->state = PC_STATE_STOP;
	pthread_cond_broadcast(&pc->notempty);
	pthread_cond_signal(&pc->notfull);
	pthread_mutex_unlock(&pc->lock);
	return;
}

// Инициализация буфера
inline void pc_init( pc_data_t *pc, int32_t n ) {
	if ( n <= 0 ) perror("pc_init(): error, buffer's number less or equal 0\n");
	pthread_mutex_init( &pc->lock, NULL );
	pthread_cond_init( &pc->notempty, NULL );
	pthread_cond_init( &pc->notfull, NULL );
	pc->num = n;
	pc->cycles = (int64_t*)malloc( pc->num * sizeof(int64_t) );
	if ( !pc->cycles ) perror("pc_init(): malloc() error\n");
	pc_start( pc );
	return;
}

// Деинициализация буфера
inline void pc_finit( pc_data_t *pc ) {
	pc_stop( pc );
	free( pc->cycles );
	return;
}

// Функция записи в буфер
inline void pc_put( pc_data_t *pc, int64_t _cycles_ ) {
	if (pc->state == PC_STATE_STOP) return;
	pthread_mutex_lock(&pc->lock);
	while (((pc->writepos + 1) % pc->num == pc->readpos) && (pc->state != PC_STATE_STOP))
		pthread_cond_wait(&pc->notfull, &pc->lock);
	pc->cycles[ pc->writepos ] = _cycles_;
	pc->writepos++;
	if (pc->writepos >= pc->num)
		pc->writepos = 0;
	pthread_cond_broadcast(&pc->notempty);
	pthread_mutex_unlock(&pc->lock);
	return;
}

// Функция чтения из буфера
inline void pc_get( pc_data_t *pc, int64_t &_cycles_ ) {
	if (pc->state == PC_STATE_STOP) { _cycles_ = -1; return; }
	pthread_mutex_lock(&pc->lock);
	while ((pc->writepos == pc->readpos) && (pc->state != PC_STATE_STOP))
		pthread_cond_wait(&pc->notempty, &pc->lock);
	_cycles_ = pc->cycles[ pc->readpos ];
	pc->readpos++;
	if (pc->readpos >= pc->num)
		pc->readpos = 0;
	pthread_cond_signal(&pc->notfull);
	pthread_mutex_unlock(&pc->lock);
	return;
}

// Функция подсчёта занятых буферов
inline int32_t pc_count( pc_data_t *pc ) { return (pc->writepos - pc->readpos + pc->num) % pc->num; }

#endif // !__PRODUCER_CONSUMER_H__