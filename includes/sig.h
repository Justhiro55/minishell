/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotainou <kotainou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 20:21:54 by kotainou          #+#    #+#             */
/*   Updated: 2023/12/01 20:21:55 by kotainou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

# include <signal.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <unistd.h>
# include <stdlib.h>

void				setup_signals(void);