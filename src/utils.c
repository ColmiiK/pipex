/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 13:02:38 by alvega-g          #+#    #+#             */
/*   Updated: 2023/12/18 17:50:37 by alvega-g         ###   ########.fr       */
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

	i = -1;
	while (++i <= data->n_args)
	{
		j = -1;
		if (data->args)
		{
			while (data->args[i][++j])
				free(data->args[i][j]);
			free(data->args[i]);
		}
	}
	if (data->args)
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
