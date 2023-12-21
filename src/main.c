/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:57:17 by alvega-g          #+#    #+#             */
/*   Updated: 2023/12/21 13:01:02 by alvega-g         ###   ########.fr       */
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

static void ft_setup(t_data *data, int ac, char **av)
{
	data->n_args = ac - 3;
	data->fd_infile = open(av[1], O_RDONLY, 0644);
	data->fd_outfile = open (av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(data->fd_infile, STDIN_FILENO);
}

int main(int ac, char **av, char **envp)
{
	t_data *data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		ft_perror("Error: unable to malloc (data).");
	if (ac != 5)
		ft_perror("Error: incorrect number of arguments.");
	//atexit(leaks);
	ft_setup(data, ac, av);
	ft_parsing(data, envp, ac, av);
	// debug_print(data, ac);
	ft_execute(data, envp);
	ft_annihilation(data);
	return (0);
}
