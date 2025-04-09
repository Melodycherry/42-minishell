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




/***************************************************************************/
// C est les copy map et malloc de tableau de so_long, 
//a voir si on peut utiliser la base pour copier le double tableau de l envp
/***************************************************************************/


// char	**cpy_map(t_mlx *mlx)
// {
// 	int		i;
// 	char	**cpy_map;

// 	i = 0;
// 	cpy_map = malloc(sizeof(char *) * (mlx->map.row + 1));
// 	if (!cpy_map)
// 		return (NULL);
// 	while (i < mlx->map.row)
// 	{
// 		cpy_map[i] = ft_strdup(mlx->map.map_tab[i]);
// 		if (cpy_map[i] == NULL)
// 			free_mid_tab(cpy_map, i);
// 		i++;
// 	}
// 	cpy_map[i] = 0;
// 	return (cpy_map);
// }

// void	malloc_map(char *arg, t_mlx *mlx)
// {
// 	int	i;

// 	i = 0;
// 	mlx->map.map_tab = malloc(sizeof(char *) * (mlx->map.row + 1));
// 	if (!mlx->map.map_tab)
// 		return (perror("Error: malloc failed"));
// 	mlx->inputs.fd = open(arg, O_RDONLY);
// 	if (mlx->inputs.fd == -1)
// 		return (ft_putstr_fd("Error : incorrect fd\n", 2));
// 	while (i < mlx->map.row)
// 	{
// 		mlx->inputs.line = get_next_line(mlx->inputs.fd);
// 		if (mlx->inputs.line == NULL)
// 			break ;
// 		mlx->map.map_tab[i] = ft_strndup(mlx->inputs.line, mlx->map.col);
// 		if (mlx->map.map_tab[i] == NULL)
// 			free_mid_tab(mlx->map.map_tab, i);
// 		free (mlx->inputs.line);
// 		i++;
// 	}
// 	mlx->map.map_tab[i] = NULL;
// 	close(mlx->inputs.fd);
// }