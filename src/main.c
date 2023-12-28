/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:57:17 by alvega-g          #+#    #+#             */
/*   Updated: 2023/12/28 11:06:33 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

/*	./pipex infile.txt "awk '{print $2}'" "cat -e" outfile.txt

	TODO:
	-> Conditional jumps (unitialized values (data->args[i][0]))
	-> command not found
	
	-> Remove Linux fix in parsing commands (usr)
	-> Implement here_doc (Create temporal file at start, use it as the first fd instead of STDIN_FILENO)
	-> Check norminette
	-> Catch edge cases (awk printf, etc.)

	if (ft_strnstr(av[1], "here_doc", ft_strlen(av[1])))
	{
		data->fd_infile = open(a)
	}

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

static void ft_setup(t_data *data, int ac, char **av)
{
	data = ft_memset(data, 0, sizeof(t_data));
	data->n_args = ac - 3;
	data->i = -1;
	data->j = -1;
	data->k = -1;
	data->flag = 1;
	data->fd_infile = open(av[1], O_RDONLY, 0644);
	data->fd_outfile = open (av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->fd_outfile == -1)
		exit(EXIT_FAILURE);
	dup2(data->fd_infile, STDIN_FILENO);
}

void ft_leaks(void)
{
	system("leaks -q pipex");
}
int main(int ac, char **av, char **envp)
{
	t_data *data;

	if (ac != 5)
		ft_perror("Error: incorrect number of arguments.");
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		ft_perror("Error: unable to malloc (data).");
	ft_setup(data, ac, av);
	ft_parsing(data, envp, ac, av);
	//debug_print(data, ac);
	// atexit(ft_leaks);
	ft_execute(data, envp);
	ft_annihilation(data);
	return (0);
}
