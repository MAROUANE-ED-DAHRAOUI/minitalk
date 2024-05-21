/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-dahr <med-dahr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:48:07 by med-dahr          #+#    #+#             */
/*   Updated: 2024/05/16 16:58:28 by med-dahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	take_pid(int pid)
{
	if (pid > 9)
		take_pid(pid / 10);
	write(1, &"0123456789"[pid % 10], 1);
}

void	handler_msg(int sig_msg, siginfo_t *info, void *notg)
{
	static char		chr = 0;
	static int		client_pid;
	static int		last_pid;
	static int		cnt = 7;

	(void)notg;
	client_pid = info->si_pid;
	if (client_pid != last_pid)
	{
		last_pid = client_pid;
		cnt = 7;
		chr = 0;
	}
	if (sig_msg == SIGUSR2)
		chr |= (1 << cnt);
	cnt--;
	if (cnt == -1)
	{
		write(1, &chr, 1);
		chr = 0;
		cnt = 7;
	}
}

void	signal_config(void)
{
	struct sigaction	action;

	action.sa_sigaction = &handler_msg;
	action.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &action, 0) == -1)
		write(1, "Error\n", 6);
	if (sigaction(SIGUSR2, &action, 0) == -1)
		write(1, "Error SIGUSR2\n", 6);
}

int	main(void)
{
	write(1, "SERVER PID : ", 13 - 1);
	take_pid(getpid());
	write(1, "\n", 1);
	signal_config();
	while (1)
		pause();
	return (0);
}
