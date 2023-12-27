/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 11:22:24 by alvega-g          #+#    #+#             */
/*   Updated: 2023/12/27 12:30:57 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;

	new_ptr = NULL;
	if (new_size == 0)
		return (free(ptr), NULL);
	if (ptr == NULL)
		new_ptr = malloc(new_size);
	else
	{
		new_ptr = malloc(new_size);
		if (new_ptr)
		{
			if (old_size < new_size)
				ft_memcpy(new_ptr, ptr, old_size);
			else
				ft_memcpy(new_ptr, ptr, new_size);
			free(ptr);
		}
	}
	return (new_ptr);
}
