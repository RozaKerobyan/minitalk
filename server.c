/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerobya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 19:06:47 by rkerobya          #+#    #+#             */
/*   Updated: 2025/05/09 17:56:21 by rkerobya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	get_msg(int sig)
{
	static int	i;
	static int	bit;

	if (sig == SIGUSR1)
		i |= (0x01 << bit);
	bit++;
	if (bit == 8)
	{
		if (i == '\0')
			ft_printf("\n");
		else
		{
			ft_printf("%c", i);
		}
		bit = 0;
		i = 0;
	}
}

int	main(int argc, char *argv[])
{
	int	pid;

	(void)argv;
	if (argc != 1)
	{
		ft_printf("❌ Error ❌\n");
		return (1);
	}
	pid = getpid();
	ft_printf("Server PID ➡️  %d\n", pid);
	while (argc == 1)
	{
		signal(SIGUSR1, get_msg);
		signal(SIGUSR2, get_msg);
		pause();
	}
	return (0);
}
