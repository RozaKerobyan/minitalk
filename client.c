/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerobya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:21:53 by rkerobya          #+#    #+#             */
/*   Updated: 2025/05/09 18:29:16 by rkerobya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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

void	send_to_msg(int pid, char c)
{
	int	i;

	i = 0;
	while (i < 8)
	{
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
	}
}

int	main(int argc, char *argv[])
{
	int	i;
	int	pid;

	i = 0;
	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		while (argv[2][i] != '\0')
		{
			send_to_msg(pid, argv[2][i]);
			i++;
		}
		send_to_msg(pid, '\0');
	}
	else
	{
		ft_printf("⚠️  Oops! You need to enter two arguments. ⚠️  \n");
		ft_printf("1️⃣  -> First: the PID number.\n");
		ft_printf("2️⃣  -> Second: Enter text to send to the server.");
		return (1);
	}
	return (0);
}
