/*******************************************************************************/
/*                                                                             */
/*                                                                             */
/*                                                                             */
/*                                                                             */
/*      LES CODEUSES DU DIMANCHE                                               */
/*      FONT UN MINISHELL                                                      */
/*                                                                             */
/*                                                                             */
/*                                                                             */
/*******************************************************************************/

#include "minishell.h"

char	*join_free(char *s1, char *s2, int len_s2)
{
	size_t	len_s1 = 0;
	char	*str;

	if (!s2 || len_s2 < 0)
	{
		free(s1); // libère ce qu’on avait déjà
		return (NULL);
	}
	if (s1)
		len_s1 = ft_strlen(s1);

	str = malloc(len_s1 + len_s2 + 1);
	if (!str)
	{
		free(s1); // on évite la fuite en cas d’échec
		return (NULL);
	}
	if (s1)
		ft_memcpy(str, s1, len_s1);
	ft_memcpy(str + len_s1, s2, len_s2);
	str[len_s1 + len_s2] = '\0';
	free(s1);
	return (str);
}

int	ft_strlen_plusplus(char *str)
{
	int	i;

	i = 0;

	while(str[i] && str[i] != '$' && str[i] != '"')
		i++;
	return (i);
}