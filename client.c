/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerobya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:21:53 by rkerobya          #+#    #+#             */
/*   Updated: 2025/05/17 20:06:46 by rkerobya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	g_send_bit;

int	ft_atoi(char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
		{
			sign = -1;
		}
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - 48);
		i++;
	}
	return (result * sign);
}

static void	received_msg(int sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (sig == SIGUSR2)
		g_send_bit = 1;
}

void	send_to_msg(int pid, char c)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		g_send_bit = 0;
		if (c & (0x01 << i))
		{
			kill(pid, SIGUSR1);
		}
		else
		{
			kill(pid, SIGUSR2);
		}
		usleep(100);
		i++;
		while (g_send_bit == 0)
			pause();
	}
}

int	main(int argc, char *argv[])
{
	int					i;
	int					pid;
	struct sigaction	sa;

	i = 0;
	if (argc == 3)
	{
		sa.sa_flags = SA_SIGINFO;
		sa.sa_sigaction = received_msg;
		sigemptyset(&sa.sa_mask);
		sigaction(SIGUSR1, &sa, NULL);
		sigaction(SIGUSR2, &sa, NULL);
		pid = ft_atoi(argv[1]);
		while (argv[2][i] != '\0')
		{
			send_to_msg(pid, argv[2][i++]);
		}
		send_to_msg(pid, '\0');
	}
	else
	{
		ft_printf("Missing arguments! Use: ./client [PID] [MESSAGE] ⚠️  \n");
		return (1);
	}
	return (0);
}
