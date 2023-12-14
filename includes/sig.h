/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotainou <kotainou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 20:21:54 by kotainou          #+#    #+#             */
/*   Updated: 2023/12/14 16:21:59 by kotainou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIG_H
# define SIG_H

# include "minishell.h"

# include <signal.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_info		t_info;

typedef struct s_node		t_node;

void				signal_ctrl(void);
void				change_signal(int flag);
// void				sigint_handler_nonl(int sig);
// void				sigin_handler_heredoc(int sig);

#endif