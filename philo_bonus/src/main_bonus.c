/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmontese <pmontes@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 22:19:25 by pmontese          #+#    #+#             */
/*   Updated: 2021/11/22 23:23:25 by pmontese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	read_args(int argc, const char *argv[], t_game *g)
{
	if (argc != 5 && argc != 6)
		return (print_error(WRONG_N_ARGS));
	g->amount = (long int)ft_atoi(argv[1]);
	g->time2die = (long int)ft_atoi(argv[2]);
	g->eat_time = (long int)ft_atoi(argv[3]);
	g->sleep_time = (long int)ft_atoi(argv[4]);
	g->meals_needed = -1;
	if (argc == 6)
	{
		g->meals_needed = ft_atoi(argv[5]);
		if (g->meals_needed <= 0)
			return (print_error(INVALID_ARG));
	}
	if (g->amount <= 0 || g->time2die <= 0
		|| g->eat_time <= 0 || g->sleep_time <= 0)
		return (print_error(INVALID_ARG));
	return (0);
}

int	init_processes(t_game *g)
{
	int		i;
	t_philo	*f;

	i = 0;
	g->start_time = current_ms();
	while (i < g->amount)
	{
		f = &g->philos[i];
		f->pid = fork();
		if (f->pid < 0)
			return (1);
		if (f->pid == 0)
			philo_p(f);
		usleep(100);
		i++;
	}	
	return (0);
}

int	init_philos(t_game *g)
{
	int		i;
	t_philo	*f;

	i = 0;
	while (i < g->amount)
	{
		f = &g->philos[i];
		f->meals = 0;
		f->g = g;
		f->id = i + 1;
		f->is_full = 0;
		f->last_meal_ms = 0;
		i++;
	}
	return (0);
}

int	init_data(t_game *g)
{
	g->philos = (t_philo *)malloc(sizeof(t_philo) * g->amount);
	if (!g->philos)
		return (print_error(MALLOC_ERR));
	sem_unlink("forks");
	sem_unlink("print");
	sem_unlink("hunger_check");
	g->forks = sem_open("forks", O_CREAT, 0777, g->amount);
	g->print = sem_open("print", O_CREAT, 0777, 1);
	g->hunger_check = sem_open("hunger_check", O_CREAT, 0777, 1);
	if (g->forks <= 0 || g->print <= 0 || g->hunger_check <= 0)
		return (print_error(SEM_ERR));
	g->start_time = current_ms();
	return (0);
}

int	main(int argc, const char *argv[])
{
	t_game	game;
	int		i;

	if (read_args(argc, argv, &game))
		return (1);
	if (init_data(&game))
		return (1);
	if (init_philos(&game))
		return (1);
	if (init_processes(&game))
		return (1);
	monitor(&game);
	return (0);
}
