/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 12:29:56 by alvega-g          #+#    #+#             */
/*   Updated: 2024/01/02 13:46:07 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

static char	*ft_join_single(char **matrix, t_data *data, int index)
{
	int	i;
	int	j;

	data->temp = ft_calloc(1, 1);
	i = 0;
	j = 0;
	while (matrix[++i])
	{
		data->old_temp = data->temp;
		data->temp = ft_strjoin(data->temp, matrix[i]);
		free(data->old_temp);
		data->old_temp = data->temp;
		data->temp = ft_strjoin(data->temp, " ");
		free(data->old_temp);
	}
	data->old_temp = data->temp;
	data->temp = ft_strtrim(data->temp, "' ");
	free(data->old_temp);
	while (data->args[index][++j])
	{
		free(data->args[index][j]);
		data->args[index][j] = NULL;
	}
	return (data->temp);
}

static char	*ft_join_double(char **matrix, t_data *data, int index)
{
	int	i;
	int	j;

	data->temp = ft_calloc(1, 1);
	i = 0;
	j = 0;
	while (matrix[++i])
	{
		data->old_temp = data->temp;
		data->temp = ft_strjoin(data->temp, matrix[i]);
		free(data->old_temp);
		data->old_temp = data->temp;
		data->temp = ft_strjoin(data->temp, " ");
		free(data->old_temp);
	}
	data->old_temp = data->temp;
	data->temp = ft_strtrim(data->temp, "\" ");
	free(data->old_temp);
	while (data->args[index][++j])
	{
		free(data->args[index][j]);
		data->args[index][j] = NULL;
	}
	return (data->temp);
}

static void	ft_double_case(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (data->args[++i])
	{
		if (data->args[i][1][0] == '\"')
		{
			while (data->args[i][j])
				j++;
			if (j > 0 && (data->args[i][j - 1][ft_strlen(data->args[i][j - 1])
					- 1] == '\"'))
			{
				data->args[i][1] = ft_join_double(data->args[i], data, i);
				return ;
			}
		}
	}
}

static void	ft_single_case(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (data->args[++i])
	{
		if (data->args[i][1][0] == '\'')
		{
			while (data->args[i][j])
				j++;
			if (j > 0 && (data->args[i][j - 1][ft_strlen(data->args[i][j - 1])
					- 1] == '\''))
			{
				data->args[i][1] = ft_join_single(data->args[i], data, i);
				return ;
			}
		}
	}
}

void	ft_fix_awk(t_data *data, char *str)
{
	if (ft_strnstr(str, "\'", 5))
		ft_single_case(data);
	else
		ft_double_case(data);
}
