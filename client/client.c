/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotarev <azolotarev@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 04:58:56 by azolotarev        #+#    #+#             */
/*   Updated: 2025/03/28 20:01:14 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

static char	g_acknowledge = -1;

static void	handler(int sig)
{
	g_acknowledge = sig;
}

static int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

static void	send_msg_len(int len, pid_t pid)
{
	int		i;
	char	bit;
	char	sig;

	i = sizeof(int) * 8 - 1;
	while (i >= 0)
	{
		bit = (len >> i) & 0b1;
		if (bit == 0)
			sig = SIGUSR1;
		else
			sig = SIGUSR2;
		g_acknowledge = -1;
		kill(pid, sig);
		while (g_acknowledge == -1)
			pause();
		if (g_acknowledge != sig)
			exit(228);
		i--;
	}
}

static	void	send_msg(char *msg, pid_t pid)
{
	int		i;
	int		j;
	char	bit;
	char	sig;
	int		len;

	len = ft_strlen(msg);
	if (len == 0)
		return ;
	send_msg_len(len, pid);
	i = 0;
	while (i < ft_strlen(msg))
	{
		j = 8 - 1;
		while (j >= 0)
		{
			bit = (msg[i] >> j) & 0b1;
			if (bit == 0)
				sig = SIGUSR1;
			else
				sig = SIGUSR2;
			g_acknowledge = -1;
			kill(pid, sig);
			while (g_acknowledge == -1)
				pause();
			if (g_acknowledge != sig)
				exit(228);
			j--;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	if (argc != 3)
		return (0);
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	send_msg(argv[2], atoi(argv[1]));
	return (0);
}
