/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmontese <pmontese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 22:19:32 by pmontese          #+#    #+#             */
/*   Updated: 2021/11/27 16:17:45 by pmontese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

long int	current_ms(void)
{
	struct timeval	tv;
	long int		ms;

	gettimeofday(&tv, NULL);
	ms = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (ms);
}

int	light_sleep(t_game *g, long int ms)
{
	long int	start_time;

	start_time = 0;
	start_time = current_ms();
	while ((current_ms() - start_time) < ms)
		usleep(g->amount * 2);
	return (0);
}

void	msg(t_game *g, t_philo *f, char *content, int lock_print)
{
	long int	ms;

	if (lock_print)
		sem_wait(g->print);
	ms = current_ms() - g->start_time;
	printf("%ld\t%d %s\n", ms, f->id, content);
	if (lock_print)
		sem_post(g->print);
}
