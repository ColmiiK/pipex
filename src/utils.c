/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 13:02:38 by alvega-g          #+#    #+#             */
/*   Updated: 2023/12/26 13:21:52 by alvega-g         ###   ########.fr       */
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

// static void ft_join(t_data *data, char **matrix, int index)
// {
// 	char *temp;
// 	int i;
// 	int j;

// 	i = 0;
// 	j = 1;
// 	temp = ft_calloc(1, 1);
// 	while (matrix[++i])
// 	{
// 		temp = ft_strjoin(temp, matrix[i]);
// 		temp[ft_strlen(temp)] = ' ';
// 	}
// 	temp[ft_strlen(temp) - 2] = 0;
// 	data->args[index][1] = ft_strdup(temp + 1);
// 	free(temp);
// 	while (data->args[index][++j])
// 	{
// 		free(data->args[index][j]);
// 		data->args[index][j] = NULL;
// 	}
// }
static void ft_join(char **matrix, t_data *data, int index)
{
	char *temp;
	char *old_temp;
	int i;
	int j;

	temp = ft_calloc(1, 1);
	i = 0;
	j = 1;
	while (matrix[++i])
	{
		old_temp = temp;
		temp = ft_strjoin(temp, matrix[i]);
		free(old_temp);
		temp[ft_strlen(temp)] = ' ';
	}
	temp[ft_strlen(temp) - 2] = 0;
	temp = ft_strtrim(temp, "'");
	ft_printf("%s\n", temp);
	data->args[index][1] = temp;
	while (data->args[index][++j])
	{
		free(data->args[index][j]);
		data->args[index][j] = NULL;
	}
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
				// ft_join(data, data->args[i], i);
				ft_join(data->args[i], data, i);
				return ;
			}
		}
	}
}