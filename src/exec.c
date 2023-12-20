/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 15:43:44 by alvega-g          #+#    #+#             */
/*   Updated: 2023/12/20 16:27:08 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

/*	
	Create the pipe
	Fork the process
	Child:
		Close read end of pipe
		Redirect STDOUT from command (ls, wc, etc.) into the write end of pipe
		Execve into said command
	Parent:
		Close write end of pipe
		
	data->fd_in = open(infile, O_RDONLY);
	if (data->fd_in == -1)
		ft_perror("Error: unable to open the infile.");
	dup2(data->fd_in, STDIN_FILENO);
	
	close(data->fd_in);
	
	data->fd_out = open(outfile, O_WRONLY | O_CREAT, 0644);
	if (data->fd_out == -1)
		ft_perror("Error: unable to open the outfile.");
	
	dup2(data->fd_temp, STDOUT_FILENO);
	close(data->fd_out);
	
	execve(data->command[data->i], data->args[data->i], NULL);
	
	void	ft_first(t_data *data, char *infile, char **envp) // First command
	{
		int fd;
		fd = open(infile, O_RDONLY, 0644);
		dup2(fd, STDIN_FILENO);
		dup2(data->pipe_fd[1], STDOUT_FILENO);
		close(data->pipe_fd[0]);
		execve(data->command[0], data->args[0], envp);
	}

	void	ft_last(t_data *data, char *outfile, char **envp) // Last command
	{
		int fd;

		fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(fd, STDOUT_FILENO);
		dup2(data->pipe_fd[0], STDIN_FILENO);
		close(data->pipe_fd[1]);
		execve(data->command[data->n_args - 1], data->args[data->n_args - 1], envp);
	}
*/



void	ft_forking(char **envp, char *cmd, char **args)
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

void	ft_execute(t_data *data, char **envp)
{
	int i;

	i = -1;

			// fd_in / fd_out 
	
	while (++i < data->n_args) // Execute multiple pipes
	{
		ft_forking(envp, data->command[i], data->args[i]);
	}
}
