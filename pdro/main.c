/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 18:46:31 by eleleux           #+#    #+#             */
/*   Updated: 2023/01/30 15:50:46 by pfaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	readline_manager(t_shell *shell)
{
	free(shell->line_readed);
	shell->line_readed = readline(MAG "Minishell >> " WHT);
	if (!shell->line_readed)
		return (EXIT_FAILURE);
	if (shell->line_readed[0] != '\0')
		add_history(shell->line_readed);
	return (EXIT_SUCCESS);
}

int	main(int ac, char **av, char **envp)
{
	(void)av;
	t_shell	shell;

	if (ac != 1)
		return (printf("Minishell is pure, no arguments please\n"));
	allocate_shell(&shell, envp);
	while (ft_strncmp(shell.line_readed, "exit", 5))
	{
		readline_manager(&shell);
		if (!shell.line_readed)
			break ;
		token_parsing(shell.user_command, shell.line_readed);
		if (shell.user_command->nb_elem != 0)
			tokenisation(shell.user_command, shell.sorted_env_l);
		if (execute_directory_cmd(&shell) == TRUE)
			execute_directory_cmd(&shell);
		execute_env_cmd(&shell);
		if (shell.user_command->nb_elem != 0)
			clear_toklst(shell.user_command);
	}
	clean_memory(&shell);
	return (0);
}
