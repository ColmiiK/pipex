/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 13:02:38 by alvega-g          #+#    #+#             */
/*   Updated: 2023/12/26 13:44:48 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	ft_perror(char *str)
{
	ft_printf("%s\n", str);
	exit(EXIT_FAILURE);
}

void ft_annihilation_2(t_data *data)
{
	int i;
	int j;

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


static char *ft_join(char **matrix, t_data *data, int index)
{
	char *temp;
	char *old_temp;
	int i;
	int j;

	temp = ft_calloc(1, 1);
	i = 0;
	j = 0;
	while (matrix[++i])
	{
		old_temp = temp;
		temp = ft_strjoin(temp, matrix[i]);
		free(old_temp);
		temp[ft_strlen(temp)] = ' ';
	}
	free(temp);
	temp[ft_strlen(temp) - 2] = 0;
	temp = ft_strtrim(temp, "'");
	while (data->args[index][++j])
	{
		free(data->args[index][j]);
		data->args[index][j] = NULL;
	}
	return (temp);
}

void ft_fix_awk(t_data *data)
{
	int i;
	int j;

	i = -1;
	j = 0;
	while (data->args[++i])
	{
		if (data->args[i][1][0] == '\'')
		{
			while (data->args[i][j])
				j++;
			if (j > 0 && data->args[i][j - 1][ft_strlen(data->args[i][j - 1]) - 1] == '\'')
			{
				data->args[i][1] = ft_join(data->args[i], data, i);
				return ;
			}
		}
	}
}