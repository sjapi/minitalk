/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotarev <azolotarev@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 04:03:05 by azolotarev        #+#    #+#             */
/*   Updated: 2025/03/27 07:24:36 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdio.h> // tmp for printf
#include "server.h"

static t_msg	g_msg;

static void	handler(int sig, siginfo_t *info, void *ucontext)
{
	char			bit;

	bit = sig == SIGUSR2;
	if (g_msg.pid != info->si_pid)
		reset_msg(&g_msg, info->si_pid);
	if (g_msg.bits_received < INT_BITS)
		g_msg.msg_len = (g_msg.msg_len << 1) | bit;
	if (g_msg.bits_received == INT_BITS)
		msg_str_alloc(&g_msg);
	if (g_msg.bits_received >= INT_BITS)
		msg_str_add_bit(&g_msg, bit);
	g_msg.bits_received++;
	if (g_msg.bits_received == g_msg.msg_len * 8 + INT_BITS)
		msg_str_print_reset(&g_msg);
	// notify client that I've received signal
	kill(info->si_pid, sig);
	(void)ucontext;
}

static void	listen(void)
{
	while (1)
		usleep(500000);
}

int	main(void)
{
	struct sigaction	action;

	action.sa_sigaction = handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	printf("pid: %d\n", getpid());
	return (listen(), 0);
}
