/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otitebah <otitebah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:40:59 by othmanetite       #+#    #+#             */
/*   Updated: 2023/06/25 03:27:16 by otitebah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>
# include <pthread.h>

typedef struct s_philo
{
    int     n;
    int     m_count;
    int     is_eating;
    pthread_t   thread;
    long int    last_eat;
    struct s_info   *info;
    pthread_mutex_t l_fork;
    pthread_mutex_t *r_fork;
}   t_philo;

typedef struct  s_info
{
    int     philo_eat;
    int     n_philo;
    int     t_die;
    int     t_eat;
    int     t_sleep;
    int     n_eat;
    int     stop;
    long int    t_start;
    t_philo     *philo;
    pthread_mutex_t print;
    pthread_mutex_t m_stop;
    pthread_mutex_t m_eat;
    pthread_mutex_t dead;
}   t_info;

int ft_atoi(char *str);
int	ft_isdigit(int c);
void	*philo_life(void *phi);
void	*check_death(void *phi);
void	philo_eat(t_philo *philo);
void	print(t_philo *philo, char *str);
int is_dead(t_philo *philo, int nb);
void	take_fork(t_philo *philo);
int init_var(t_info *info, char **av);
long long   timee(void);
int philo_init(t_info *info);
void my_usleep(int ms);


#endif