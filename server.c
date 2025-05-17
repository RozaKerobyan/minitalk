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

void	get_msg(int sig, siginfo_t *info, void *context)
{
	static unsigned char	i;
	static int	bit;

	(void)context;
	if (sig == SIGUSR1)
		i |= (1 << bit);
	else if (sig == SIGUSR2)
		i &= ~(1 << bit);
	bit++;
	if (bit == 8)
	{
		if (i == '\0')
		{
			ft_printf("\n");
			kill(info->si_pid, SIGUSR1);
		}
		else
		{
			ft_printf("%c", i);
		}
		//kill(info->si_pid, SIGUSR1);
		bit = 0;
		i = 0;
	}
	kill(info->si_pid, SIGUSR2);
}

int	main(int argc, char *argv[])
{
	int					pid;			
	struct sigaction	sa;

	(void)argv;
	if (argc != 1)
	{
		ft_printf("❌ Error ❌\n");
		return (1);
	}
	pid = getpid();
	ft_printf("Server PID ➡️  %d\n", pid);
	sa.sa_sigaction = get_msg;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
	{
		pause();
	}
	return (0);
}
