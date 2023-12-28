/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 12:50:00 by alvega-g          #+#    #+#             */
/*   Updated: 2023/12/28 11:44:50 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex_bonus.h>

static void	ft_access_cmds(t_data *data)
{
	char	*temp;

	while (data->args[++data->i][0])
	{
		data->j = -1;
		while (data->path[++data->j])
		{
			temp = ft_strjoin(data->path[data->j], data->args[data->i][0]);
			if (ft_strnstr(temp, "usr", 5))
				temp[1] = '.';
			if (access(temp, F_OK) != -1 && access(temp, X_OK) != -1)
			{
				data->flag = 0;
				data->command[++data->k] = ft_strdup(temp);
				if (!data->command[data->k])
					ft_perror("Error: unable to strdup (data->command[k]).");
			}
			free(temp);
		}
		if (data->flag == 1)
			data->command[++data->k] = ft_strdup("");
		data->flag = 1;
	}
	data->command[data->k + 1] = NULL;
}

static void	ft_parse_cmds(t_data *data, int ac, char **av)
{
	int	i;
	int	j;

	i = -1;
	j = 1;
	data->args = (char ***)ft_calloc(ac - 1, sizeof(char **));
	if (!data->args)
		ft_perror("Error: unable to malloc (data->args).");
	while (++j < (ac - 1))
		data->args[++i] = ft_split(av[j], ' ');
	data->args[++i] = malloc(sizeof(char *));
	if (!data->args[i])
		ft_perror("Error: unable to malloc (data-args[i])");
	data->args[i][0] = NULL;
	data->command = (char **)ft_calloc(ac - 2, sizeof(char *));
	if (!data->command)
		ft_perror("Error: unable to malloc (data->command).");
	return ;
}

static void	ft_parse_envp(t_data *data, char **envp)
{
	int	i;
	int	j;

	i = -1;
	while (envp[++i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
		{
			data->path = ft_split(envp[i] + 5, ':');
			i = -1;
			while (data->path[++i])
			{
				j = ft_strlen(data->path[i]);
				data->path[i] = ft_realloc(data->path[i], j + 1, j + 2);
				if (!data->path[i])
					ft_perror("Error: unable to realloc (data->path[i]).");
				data->path[i][j] = '/';
				data->path[i][j + 1] = 0;
			}
			return ;
		}
	}
}

void	ft_parsing(t_data *data, char **envp, int ac, char **av)
{
	int i;

	i = -1;
	ft_parse_envp(data, envp);
	ft_parse_cmds(data, ac, av);
	ft_access_cmds(data);
	while (data->args[++i] && data->args[i][0])
	{
		if (ft_strnstr(data->args[i][0], "awk", 4))
			ft_fix_awk(data);
	}
	return ;
}
