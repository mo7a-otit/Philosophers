/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otitebah <otitebah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 03:03:47 by otitebah          #+#    #+#             */
/*   Updated: 2023/06/25 03:27:00 by otitebah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int is_dead(t_philo *philo, int nb)
{
	pthread_mutex_lock(&philo->info->dead);
	if(nb)
		philo->info->stop = 1;
	if (philo->info->stop)
	{
		pthread_mutex_unlock(&philo->info->dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->info->dead);
	return (0);
}

long long   timee(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void my_usleep(int ms)
{
	long int	time;

	time = timee();
	while (timee() - time < ms)
		usleep(ms / 10);
}

void	print(t_philo *philo, char *str)
{
	long	int	time;
	
	pthread_mutex_lock(&(philo->info->print));
	time = timee() - philo->info->t_start;
	if (!philo->info->stop && time >= 0 \
			&& time <= INT_MAX && !is_dead(philo, 0))
		printf("%lld %d %s", timee() - philo->info->t_start, philo->n, str);
	pthread_mutex_unlock(&(philo->info->print));
}