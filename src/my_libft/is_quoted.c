/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_quoted.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenoni <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:35:02 by lmenoni           #+#    #+#             */
/*   Updated: 2025/06/13 13:35:04 by lmenoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_quoted(char *s, char *to_check)
{
	bool	in_quote;
	char	quote;

	quote = 0;
	in_quote = false;
	while (s != to_check)
	{
		if ((*s == '"' || *s == '\'') && (quote == *s || quote == 0))
		{
			in_quote = !in_quote;
			quote = *s;
		}
		if (!in_quote)
			quote = 0;
		s++;
	}
	if (*to_check == quote && in_quote)
		return (0);
	if (in_quote && quote == '\'')
		return (1);
	if (in_quote && quote == '"')
		return (2);
	return (0);
}
