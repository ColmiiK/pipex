/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:56:08 by alvega-g          #+#    #+#             */
/*   Updated: 2023/12/26 18:38:59 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../lib/libft/include/libft.h"
# include <sys/wait.h>

typedef struct s_data
{
	char	**path;
	char	***args;
	char	**command;
	int		n_args;
	int		fd_infile;
	int		fd_outfile;
}			t_data;

void		ft_parsing(t_data *data, char **envp, int ac, char **av);
void		ft_fix_awk(t_data *data);
void		ft_perror(char *str);
void		ft_annihilation(t_data *data);
void		ft_execute(t_data *data, char **envp);

#endif