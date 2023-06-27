/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otitebah <otitebah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 03:22:06 by otitebah          #+#    #+#             */
/*   Updated: 2023/06/26 21:12:51 by otitebah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check_death(void *phi)
{
	t_philo	*philo;

	philo = (t_philo *)phi;
	my_usleep(philo->info->t_die + 1);
	pthread_mutex_lock(&philo->info->m_eat);
	pthread_mutex_lock(&philo->info->m_stop);
	if(!is_dead(philo, 0) && timee() \
		- philo->last_eat >= (long)(philo->info->t_die))
	{
		pthread_mutex_unlock(&philo->info->m_eat);
		pthread_mutex_unlock(&philo->info->m_stop);
		print(philo, "died\n");
		is_dead(philo, 1);
	}
	pthread_mutex_unlock(&philo->info->m_eat);
	pthread_mutex_unlock(&philo->info->m_stop);
	return (NULL);
}

void	take_fork(t_philo *philo)
{
	pthread_mutex_lock(&(philo->l_fork));
	print(philo, " has taken a fork\n");
	if (philo->info->n_philo == 1)
	{
		my_usleep(philo->info->t_die * 2);
		return ;
	}
	pthread_mutex_lock(philo->r_fork);
	print(philo, " has taken a fork\n");
}

void	philo_eat(t_philo *philo)
{
	print(philo, " is eating\n");
	pthread_mutex_lock(&(philo->info->m_eat));
	philo->last_eat = timee();
	philo->m_count++;
	pthread_mutex_unlock(&(philo->info->m_eat));
	my_usleep(philo->info->t_eat);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(&(philo->l_fork));
	print(philo, " is sleeping\n");
	my_usleep(philo->info->t_sleep);
	print(philo, " is thinking\n");
}

void	*philo_life(void *phi)
{
	t_philo	*philo;
	pthread_t	t;

	philo = (t_philo *) phi;
	if (philo->n % 2 == 0)
		my_usleep(philo->info->t_eat / 10);
	while (!is_dead(philo, 0))
	{
		pthread_create(&t, NULL, check_death, phi);
		take_fork(philo);
		philo_eat(philo);
		pthread_detach(t);
		if (philo->m_count == philo->info->n_eat)
		{
			pthread_mutex_lock(&philo->info->m_stop);
			if (++philo->info->philo_eat == philo->info->n_philo)
			{
				pthread_mutex_unlock(&philo->info->m_stop);
				is_dead(philo, 2);
			}
			pthread_mutex_unlock(&philo->info->m_stop);
			return (NULL);
		}
	}
	return (NULL);
}