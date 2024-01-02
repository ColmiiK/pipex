/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 13:02:38 by alvega-g          #+#    #+#             */
/*   Updated: 2024/01/02 17:03:03 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex_bonus.h>

static void	ft_annihilation_2(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i <= data->n_args)
	{
		j = 0;
		while (data->args[i][j])
		{
			free(data->args[i][j]);
			j++;
		}
		free(data->args[i]);
		i++;
	}
	free(data->args);
}

void	ft_annihilation(t_data *data)
{
	int	i;

	i = -1;
	if (data->path)
	{
		while (data->path[++i])
			free(data->path[i]);
		if (data->path)
			free(data->path);
	}
	ft_annihilation_2(data);
	i = -1;
	if (data->command)
	{
		while (data->command[++i])
			free(data->command[i]);
	}
	if (data->command)
		free(data->command);
	free(data);
	return ;
}

static void	ft_here_doc_child(char *limit, int fd[2])
{
	char	*line;

	ft_putstr_fd(">", 0);
	line = get_next_line(STDIN_FILENO);
	if (ft_strncmp(line, limit, ft_strlen(limit)) == 0)
		exit(EXIT_SUCCESS);
	ft_putstr_fd(line, fd[1]);
	free(line);
}

void	ft_here_doc(char *limit)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		ft_perror("Error: pipe");
	pid = fork();
	if (pid == -1)
		ft_perror("Error: fork");
	if (pid == 0)
	{
		close(fd[0]);
		while (true)
			ft_here_doc_child(limit, fd);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		wait(NULL);
	}
}

void	ft_perror(char *str)
{
	ft_putendl_fd(str, STDERR_FILENO);
	exit(EXIT_FAILURE);
}
