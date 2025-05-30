/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 21:47:57 by selbouka          #+#    #+#             */
/*   Updated: 2025/03/18 21:47:57 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
{
	t_vars  vr;

	if (ac != 5 && ac != 6)
		return (printf("Number of arguments is incorrect\n"), 0);
	if (!parsing(av, &vr))
		return (1);
	// printf ("%d\n", vr.n_philo); 
	if (!data_init(&vr))
		return (1);
		
}
