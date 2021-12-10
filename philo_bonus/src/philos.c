/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmontese <pmontese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 22:19:28 by pmontese          #+#    #+#             */
/*   Updated: 2021/11/27 16:24:22 by pmontese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	print_error(int err)
{
	char	*str;

	if (err == WRONG_N_ARGS)
		str = "Wrong number of arguments\n";
	if (err == INVALID_ARG)
		str = "Invalid argument (only > 0 int)\n";
	if (err == PTHD_ERR)
		str = "Error creating thread\n";
	if (err == MALLOC_ERR)
		str = "Error allocating memory\n";
	if (err == MUTEX_ERR)
		str = "Error initializing mutex\n";
	if (err == SEM_ERR)
		str = "Error creating semaphore\n";
	printf("%s", str);
	if (err == WRONG_N_ARGS)
	{
		printf("Arguments: number_of_philosophers ");
		printf("time_to_die time_to_eat time_to_sleep ");
		printf("[number_of_times_each_philosopher_must_eat]\n");
	}
	return (1);
}

void	*hunger_chk(void *args)
{
	t_philo		*f;
	long int	ms;

	f = (t_philo *)args;
	if (light_sleep(f->g, f->g->time2die))
		return (NULL);
	sem_wait(f->g->hunger_check);
	ms = current_ms();
	if (!f->is_full
		&& ms - f->last_meal_ms >= f->g->time2die)
	{
		sem_wait(f->g->print);
		msg(f->g, f, "died", 0);
		exit(1);
	}
	sem_post(f->g->hunger_check);
	return (NULL);
}

int	eat(t_philo *f)
{
	pthread_t	hunger_thd;

	pthread_create(&hunger_thd, NULL, &hunger_chk, f);
	pthread_detach(hunger_thd);
	sem_wait(f->g->forks);
	msg(f->g, f, "takes fork", 1);
	sem_wait(f->g->forks);
	msg(f->g, f, "takes fork", 1);
	sem_wait(f->g->hunger_check);
	msg(f->g, f, "is eating", 1);
	f->last_meal_ms = current_ms();
	sem_post(f->g->hunger_check);
	f->meals++;
	light_sleep(f->g, f->g->eat_time);
	sem_post(f->g->forks);
	sem_post(f->g->forks);
	if (f->is_full)
		return (1);
	return (0);
}

void	*philo_p(void *args)
{
	int		i;
	t_philo	*f;

	f = (t_philo *)args;
	f->is_alive = 1;
	if (f->id % 2 == 0)
		usleep(50);
	f->last_meal_ms = current_ms();
	while (!f->is_full && f->is_alive)
	{
		if (eat(f))
			break ;
		msg(f->g, f, "is sleeping", 1);
		light_sleep(f->g, f->g->sleep_time);
		if (f->meals == f->g->meals_needed)
		{
			f->is_full = 1;
			break ;
		}
		msg(f->g, f, "is thinking", 1);
	}
	exit(EXIT_SUCCESS);
}

void	monitor(t_game *g)
{
	int	i;
	int	ret;

	waitpid(0, &ret, 0);
	if (ret != 0)
	{
		i = 0;
		while (i < g->amount)
		{
			kill(g->philos[i].pid, SIGTERM);
			i++;
		}
	}
	sem_close(g->forks);
	sem_close(g->print);
	sem_close(g->hunger_check);
	sem_unlink("forks");
	sem_unlink("print");
	sem_unlink("hunger_check");
	free(g->philos);
}
