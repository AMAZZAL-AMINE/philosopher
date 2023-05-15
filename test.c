#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


typedef struct s_data
{
    int n_philos;
    int n_time_die;
    int n_time_sleep;
    int n_time_eat;
    pthread_mutex_t exit_lock;
    pthread_mutex_t print_lock;
} s_data;

typedef struct s_philo
{
    int p_id;
    pthread_t philo;
    pthread_mutex_t fork;
    struct timeval tv_cretaed_at;
    struct timeval tz_cretaed_at;
    struct timeval tv_last_eat;
    int is_dead;
    s_data *data;
} s_philo;

void test(s_philo *p_data) {
    int count = 0;
  while (count < 5) {
      printf("%d\n", p_data[count].data->n_time_die);
      count++;
  }
}

int main()
{
  s_philo *data = malloc(sizeof(s_philo) * 5);
    s_data *d_ = malloc(sizeof(s_data) * 5);
  int count = 0;
  while (count < 5) {
    data[count].data = d_;
    count++;
  }
  data->data->n_time_die = 50;
  test(data);
}