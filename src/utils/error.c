/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboulmie <bboulmie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 18:24:25 by bboulmie          #+#    #+#             */
/*   Updated: 2025/11/06 18:26:24 by bboulmie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	error_msg(const char *msg)
{
	write(2, msg, ft_strlen(msg));
	return (FAILURE);
}

void	fatal_error(const char *msg, t_app *app)
{
	error_msg(msg);
	cleanup(app);
	exit(FAILURE);
}