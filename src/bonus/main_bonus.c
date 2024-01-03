/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:57:17 by alvega-g          #+#    #+#             */
/*   Updated: 2024/01/03 11:21:19 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex_bonus.h>

static void	ft_setup(t_data *data, int ac, char **av)
{
	data = ft_memset(data, 0, sizeof(t_data));
	data->i = -1;
	data->j = -1;
	data->k = -1;
	data->flag = 1;
	data->here_flag = 0;
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
	{
		ft_here_doc(av[2]);
		data->here_flag = 1;
	}
	else
		data->fd_infile = open(av[1], O_RDONLY, 0644);
	data->fd_outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	data->n_args = ac - 3 - data->here_flag;
	if (data->fd_outfile == -1)
		exit(EXIT_FAILURE);
	dup2(data->fd_infile, STDIN_FILENO);
}

int	main(int ac, char **av, char **envp)
{
	t_data	*data;

	if (ac < 5)
		ft_perror("Error: too few arguments.");
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		ft_perror("Error: unable to malloc (data).");
	if (!envp || !*envp)
		ft_perror("Error: no environment.");
	ft_setup(data, ac, av);
	ft_parsing(data, envp, ac, av);
	ft_execute(data, envp);
	return (0);
}
