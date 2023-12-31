/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:57:17 by alvega-g          #+#    #+#             */
/*   Updated: 2024/01/02 13:46:10 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

static void	ft_setup(t_data *data, int ac, char **av)
{
	data = ft_memset(data, 0, sizeof(t_data));
	data->n_args = ac - 3;
	data->i = -1;
	data->j = -1;
	data->k = -1;
	data->flag = 1;
	data->fd_infile = open(av[1], O_RDONLY, 0644);
	data->fd_outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->fd_outfile == -1)
		exit(EXIT_FAILURE);
	dup2(data->fd_infile, STDIN_FILENO);
}

int	main(int ac, char **av, char **envp)
{
	t_data	*data;

	if (ac != 5)
		ft_perror("Error: incorrect number of arguments.");
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		ft_perror("Error: unable to malloc (data).");
	if (!envp || !*envp)
		ft_perror("Error: no environment.");
	ft_setup(data, ac, av);
	ft_parsing(data, envp, ac, av);
	ft_execute(data, envp);
	ft_annihilation(data);
	return (0);
}
