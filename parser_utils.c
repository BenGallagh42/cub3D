/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomasat <kkomasat@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 22:50:53 by kkomasat          #+#    #+#             */
/*   Updated: 2025/12/07 23:48:55 by kkomasat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_trim_trailing(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	len--;
	while (len >= 0 && (str[len] == ' ' || str[len] == '\t' || \
str[len] == '\n' || str[len] == '\r'))
	{
		str[len] = '\0';
		len--;
	}
}

void	skip_spaces(char *line, int *i)
{
	while (line[*i] && (line[*i] == ' ' || line[*i] == '\t'))
		(*i)++;
}

static int	chk_whitespaces(char ch)
{
	if ((ch == ' ') || (ch == '\n') || (ch == '\t') || (ch == '\r'))
		return (TRUE);
	return (FALSE);
}

int	chk_extention(char *filename, char *ext)
{
	char	*tmp;

	tmp = ft_strrchr(filename, '.');
	if (!tmp)
		return (FALSE);
	if (ft_strcmp(tmp, ext) == 0)
		return (TRUE);
	return (FALSE);
}

int	chk_empty_line(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (TRUE);
	while (line[i])
	{
		if (!chk_whitespaces(line[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}
