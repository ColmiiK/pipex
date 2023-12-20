/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:57:17 by alvega-g          #+#    #+#             */
/*   Updated: 2023/12/20 16:21:45 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

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

	// atexit(leaks);
	data = (t_data *)malloc(sizeof(t_data));
	if (ac != 5)
		ft_perror("Error: incorrect number of arguments.");
	if (!data)
		ft_perror("Error: unable to malloc (data).");
	data->n_args = ac - 3;
	data->i = 0;
	ft_parsing(data, envp, ac, av);
	// debug_print(data, ac);
	ft_execute(data, envp);

	ft_annihilation(data);
	return (0);
}
