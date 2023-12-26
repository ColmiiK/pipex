/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 15:43:44 by alvega-g          #+#    #+#             */
/*   Updated: 2023/12/26 18:38:29 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex_bonus.h>

static void	ft_forking(char **envp, char *cmd, char **args)
{
	pid_t pid;
	int pipe_fd[2];
	
	if (pipe(pipe_fd) == -1)
		ft_perror("Error: pipe.");
	pid = fork();
	if (pid == -1)
		ft_perror("Error: fork.");
	
	if (pid == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		execve(cmd, args, envp);
	}
	else
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
	}	
}

static void	ft_last_fork(t_data *data, char **envp, char *cmd, char **args)
{
	pid_t pid;
	pid = fork();
	if (pid == -1)
		ft_perror("Error: last fork.");
	if (pid == 0)
	{
		dup2(data->fd_outfile, STDOUT_FILENO);
		execve(cmd, args, envp);
	}
	else
		return ;
	
}

void	ft_execute(t_data *data, char **envp)
{
	int i;

	i = -1;
	while (++i < (data->n_args - 1))
		ft_forking(envp, data->command[i], data->args[i]);
	ft_last_fork(data, envp, data->command[i], data->args[i]);
	return ;
}
