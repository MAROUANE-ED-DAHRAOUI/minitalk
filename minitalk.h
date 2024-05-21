/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-dahr <med-dahr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:19:35 by med-dahr          #+#    #+#             */
/*   Updated: 2024/05/16 16:06:01 by med-dahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h> //for kill(), struct sigaction,usleep()....
# include <stdlib.h> //for exit()
# include <unistd.h> //for write()

typedef struct T_tools
{
	int	len;
	int	bit;
	int	id;
}		t_tls;

//client
void	send_bits(int pid, char *msg);
void	send_sig(char k, int pid);
int		extract_pid(char k, int num);

//server
void	handler_msg(int sig_msg, siginfo_t *info, void *notg);
void	signal_config(void);
void	take_pid(int pid);

#endif