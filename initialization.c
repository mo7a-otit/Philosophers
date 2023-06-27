/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otitebah <otitebah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 14:54:37 by otitebah          #+#    #+#             */
/*   Updated: 2023/06/26 21:06:38 by otitebah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int philo_init(t_info *info)
{
    int i;

    info->t_start = timee();
    i = -1;
    while (++i < info->n_philo)
    {
        info->philo[i].n = i + 1;
        info->philo[i].last_eat = 0;
        info->philo[i].r_fork = NULL;
        info->philo[i].info = info;
        info->philo[i].m_count = 0;
        pthread_mutex_init(&(info->philo[i].l_fork), NULL);
        if (i == info->n_philo - 1)
            info->philo[i].r_fork = &info->philo[0].l_fork;
        else
            info->philo[i].r_fork = &info->philo[i + 1].l_fork;
        if (pthread_create(&info->philo[i].thread, NULL, \
                &philo_life, &(info->philo[i])) != 0)
            return (-1);
    }
    i = -1;
    while (++i < info->n_philo)
        if (pthread_join(info->philo[i].thread, NULL) != 0)
            return (-1);
    return (0);
}

int check_num(char **str)  //to check if args are only nbrs
{
    int i;
    int j;

    i = 1;
    while (str[i])
    {
        j = 0;
        while (str[i][j])
        {
            if (!ft_isdigit(str[i][j]))
                return (1);
            j++;
        }
        i++;
    }
    return (0);
}

int init_var(t_info *info, char **av)  //for initial all variables
{
    pthread_mutex_init(&info->print, NULL);
    pthread_mutex_init(&info->m_stop, NULL);
    pthread_mutex_init(&info->m_eat, NULL);
    pthread_mutex_init(&info->dead, NULL);
    info->stop = 0;
    info->philo = malloc(sizeof(t_philo) * info->n_philo);
    if (info->philo == NULL)
        return (2);
    if (check_num(av))
    {
        printf("To many arguments\n");
        return (1);
    }
    info->philo_eat = 0;
    info->n_philo = ft_atoi(av[1]);
    info->t_die = ft_atoi(av[2]);
    info->t_eat = ft_atoi(av[3]);
    info->t_sleep = ft_atoi(av[4]);
    if (av[5])
        info->n_eat = ft_atoi(av[5]);
    if (av[5] && info->n_eat == 0)
        return (1);
    return (0);    
}