/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:57:17 by alvega-g          #+#    #+#             */
/*   Updated: 2023/12/14 11:20:33 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

/*

	$> <infile ls -l | wc -l >outfile
	./pipex infile "ls -l" "wc -l" outfile
	av[2] -> av[ac - 2] (n pipes)

*/


void ft_parse_cmds(t_data *data, int ac, char **av)
{
	int i;
	int j;

	i = -1;
	j = 1;
	data->command = (char ***)malloc(sizeof(char **) * (ac - 3));
	if (!data->command)
	{
		ft_printf("Error: unable to malloc.\n");
		exit(EXIT_FAILURE);
	}
	while (++j < (ac - 1))
		data->command[++i] = ft_split(av[j], ' ');
	return ;
}

void ft_parse_path(t_data *data, char **envp)
{
	int i;
	
	i = -1;
	while (envp[++i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
		{
			data->path = ft_split(envp[i], ':');
			data->path[0] += 5;
			return ;
		}
	}
}

void debug_print(t_data *data, int ac)
{
	ft_printf("Paths:\n");
	for (int i = 0; data->path[i]; i++)
		ft_printf("%s\n", data->path[i]);
	ft_printf("\nCommands:\n");
	for (int i = 0; i < (ac - 3); i++)
	{
		for (int j = 0; data->command[i][j]; j++)
			ft_printf("%s\n", data->command[i][j]);
	}
}


int main(int ac, char **av, char **envp)
{
	t_data *data;

	data = (t_data *)malloc(sizeof(t_data *));
	ft_parse_path(data, envp);
	ft_parse_cmds(data, ac, av);

	debug_print(data, ac);
	exit(EXIT_SUCCESS);
}
