/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:57:17 by alvega-g          #+#    #+#             */
/*   Updated: 2023/12/18 17:48:25 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

/*

	$> <infile ls -l | wc -l >outfile
	./pipex infile "ls -l" "wc -l" outfile
	av[2] -> av[ac - 2] (n pipes)


	data->args[i][0] <- args to check (ls, wc, ...)
	
	if (data->path[i] + data->args[i][0] is accesible)
		all okay, store in data->command
	else
		check next data->path
		

	data->args[i][j][k]:
	
		i ->	{"ls -l"} 
				{"wc -l"}
			
		j ->->		{"ls"}
					{"-l"}
		
		k ->->->		{"l"}
						{"s"}

*/

void debug_print(t_data *data, int ac)
{
	ft_printf("Paths:\n");
	for (int i = 0; data->path[i]; i++)
		ft_printf("%s\n", data->path[i]);
	ft_printf("\nArguments:\n");
	for (int i = 0; i < (ac - 3); i++)
	{
		for (int j = 0; data->args[i][j]; j++)
			ft_printf("%s\n", data->args[i][j]);
		ft_printf("\n");
	}
	ft_printf("\nCommands:\n");
	for (int i = 0; data->command[i]; i++)
		ft_printf("%s\n", data->command[i]);
}

void leaks(void)
{
	system ("leaks -q pipex");
}

int main(int ac, char **av, char **envp)
{
	t_data *data;

	atexit(leaks);
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		ft_perror("Error: unable to malloc (data).");
	data->n_args = ac - 3;
	ft_parsing(data, envp, ac, av);
	debug_print(data, ac);
	
	ft_annihilation(data);
	return (0);
}
