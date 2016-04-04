#include <pthread.h>
#include <stdio.h>
#include <fcntl.h>

pthread_mutex_t	lock_file = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t	cond;
pthread_mutex_t	lock_cond = PTHREAD_MUTEX_INITIALIZER;

static int	cnt = 0;

void *cb(void *arg) {
	pthread_mutex_lock(&lock_file);
	int	fd = open("test.log",O_WRONLY|O_APPEND|O_CREAT);
	write(fd, "test\n", 5);
	close(fd);
	pthread_mutex_unlock(&lock_file);

	pthread_mutex_lock(&lock_cond);
	++cnt;
	pthread_cond_signal(&cond);
	pthread_mutex_unlock(&lock_cond);
}
	

int main() {
	pthread_t	p1, p2, p3;
	pthread_create(&p1, NULL, cb, NULL);
	pthread_create(&p2, NULL, cb, NULL);
	pthread_create(&p3, NULL, cb, NULL);
/*
	void		*ret;
	pthread_join(p1, &ret);
	pthread_join(p2, &ret);
	pthread_join(p3, &ret);
*/
	
	pthread_mutex_lock(&lock_cond);	
	while (cnt < 3) 
		pthread_cond_wait(&cond, &lock_cond);
	pthread_mutex_unlock(&lock_cond);

	return 0;
}
