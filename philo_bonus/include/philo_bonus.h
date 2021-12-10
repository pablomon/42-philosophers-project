/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmontese <pmontese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 23:22:50 by pmontese          #+#    #+#             */
/*   Updated: 2021/11/27 16:17:47 by pmontese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <sys/time.h>
# include <sys/wait.h>
# include <signal.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>

# define WRONG_N_ARGS 1
# define INVALID_ARG 2
# define PTHD_ERR 3
# define MALLOC_ERR 4
# define MUTEX_ERR 5
# define SEM_ERR 6
# define LIGHT_SLEEP_MS 20

struct	s_game;

typedef struct s_philo
{
	int				id;
	struct s_game	*g;
	long int		last_meal_ms;
	int				meals;
	int				is_full;
	int				is_alive;
	pid_t			pid;
}	t_philo;

typedef struct s_game
{
	int				amount;
	long int		time2die;
	long int		eat_time;
	long int		sleep_time;
	int				meals_needed;

	long int		start_time;

	t_philo			*philos;
	sem_t			*hunger_check;
	sem_t			*forks;
	sem_t			*print;

}	t_game;

// libft
int			ft_atoi(const char *str);

// utils
long int	current_ms(void);
int			light_sleep(t_game *g, long int ms);
void		msg(t_game *g, t_philo *f, char *content, int lock_mutex);

// philos
int			print_error(int error_type);
void		*philo_p(void *args);
void		monitor(t_game *g);

#endif
