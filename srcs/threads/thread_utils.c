/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 15:58:19 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/11 16:25:15 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		all_threads_are_done(t_sampling *sampling)
{
	while (pthread_mutex_trylock(&sampling->mutex))
		;
	if (sampling->threads_status == sampling->threads_end_status)
	{
		pthread_mutex_unlock(&sampling->mutex);
		return (GOOD);
	}
	pthread_mutex_unlock(&sampling->mutex);
	return (FAILED);
}

void	kill_all_thread(t_sampling *sampling)
{
	unsigned int	i;

	if (sampling->threads_status != sampling->threads_end_status)
	{
		sampling->kill_thread.bool = 1;
		i = 0;
		while (i < RAYMARCHING_THREAD)
		{
			pthread_join(sampling->threads[i], NULL);
			i++;
		}
		sampling->kill_thread.bool = 0;
	}
}
