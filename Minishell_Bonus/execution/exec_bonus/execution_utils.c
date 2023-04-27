/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 16:49:26 by pfaria-d          #+#    #+#             */
/*   Updated: 2023/04/27 17:08:49 by pfaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_or(char *cmd)
{
	if (ft_strncmp(cmd, "||", 3) == 0)
		return (1);
	return (0);
}

int	is_and(char *cmd)
{
	if (ft_strncmp(cmd, "&&", 3) == 0)
		return (1);
	return (0);
}

int	is_pipe(char *cmd)
{
	if (ft_strncmp(cmd, "|", 2) == 0)
		return (1);
	return (0);
}

int	not_execute_builtin(t_shell *shell, char **command, char *tmp,
	struct stat buff)
{
	if (access(command[0], F_OK) == 0 && S_ISREG(buff.st_mode))
		tmp = ft_strdup(command[0]);
	else
		tmp = find_path_bonus(command[0], shell);
	if (!tmp)
	{
		if (shell->index_of_pipes > 0)
			close_fds(shell->fd[shell->index_of_pipes - 1]);
		return (EXIT_FAILURE);
	}
	if (shell->index_of_pipes != shell->nb_of_pipes)
		pipe(shell->fd[shell->index_of_pipes]);
	shell->pid[shell->index_of_commands] = fork();
	signal(SIGINT, &do_nothing);
	signal(SIGQUIT, &do_nothing);
	if (shell->pid[shell->index_of_commands] == 0)
	{
		redirection_bonus(shell);
		execve(tmp, command, shell->array_env);
	}
	if (shell->index_of_pipes != shell->nb_of_pipes)
		shell->last_index = shell->index_of_pipes;
	free(tmp);
	return (EXIT_SUCCESS);
}
