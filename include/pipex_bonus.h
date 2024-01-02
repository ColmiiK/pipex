/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:56:08 by alvega-g          #+#    #+#             */
/*   Updated: 2024/01/02 16:53:00 by alvega-g         ###   ########.fr       */
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
	char	*temp;
	char	*old_temp;
	int		i;
	int		j;
	int		k;
	int		flag;
	int		here_flag;
}			t_data;

void		ft_parsing(t_data *data, char **envp, int ac, char **av);
void		ft_fix_awk(t_data *data, char *str);
void		ft_perror(char *str);
void		ft_annihilation(t_data *data);
void		ft_execute(t_data *data, char **envp);
void		ft_here_doc(char *limit);

#endif