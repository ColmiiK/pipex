/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:56:08 by alvega-g          #+#    #+#             */
/*   Updated: 2023/12/20 12:01:30 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../lib/libft/include/libft.h"
# include <sys/wait.h>

typedef struct s_data
{
	char	**path;
	char	***args;
	char	**command;
	int		n_args;
	pid_t	pid;
	int		pipe_fd[2];
	int		fd_in;
	int		fd_out;
	int		i;

}			t_data;

void		ft_parsing(t_data *data, char **envp, int ac, char **av);
void		ft_perror(char *str);
void		ft_annihilation(t_data *data);
void		ft_execute(t_data *data, char *infile, char *outfile, char **envp);

#endif