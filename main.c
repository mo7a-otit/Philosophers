/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otitebah <otitebah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:42:57 by otitebah          #+#    #+#             */
/*   Updated: 2023/06/25 03:27:50 by otitebah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	freedom(t_info *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philo)
	{
		pthread_mutex_destroy(&data->philo[i].l_fork);
		pthread_mutex_destroy(data->philo[i].r_fork);
	}
	free(data->philo);
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->m_stop);
	pthread_mutex_destroy(&data->m_eat);
	pthread_mutex_destroy(&data->dead);
}

int main(int ac, char **av)
{
    t_info  data;

    if (ac != 5 && ac != 6)
        return (0);
	if (init_var(&data, av) == 1)
	{
		free(data.philo);
		return (0);
	}
	philo_init(&data);
	freedom(&data);
}