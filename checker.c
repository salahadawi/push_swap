/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 15:58:18 by sadawi            #+#    #+#             */
/*   Updated: 2020/01/10 16:56:24 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "libft/ft_printf.h"
#include "libft/get_next_line.h"
#include "checker.h"

int	check_array_int(int argc, char **argv)
{
	int i;
	int j;

	i = 0;
	if (ft_strequ(argv[1], "-v"))
		i++;
	while (argc > ++i)
	{
		j = 0;
		if (ft_atoilong(argv[i]) > 2147483647 ||
			ft_atoilong(argv[i]) < -2147483648)
			return (0);
		if (argv[i][j] == '-' && ft_isdigit(argv[i][j + 1]))
			j++;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j++]))
				return (0);
		}
	}
	return (1);
}

int	check_duplicate(int argc, char **argv)
{
	int i;
	int j;

	j = 0;
	if (ft_strequ(argv[1], "-v"))
		j++;
	while (argc > ++j)
	{
		i = j;
		while (argc > ++i)
			if (ft_atoi(argv[j]) == ft_atoi(argv[i]))
				return (1);
	}
	return (0);
}

int	check_error(int argc, char **argv)
{
	if (argc < 2)
		return (1);
	if (!check_array_int(argc, argv))
		return (1);
	if (check_duplicate(argc, argv))
		return (1);
	return (0);
}

int	create_stacks(int argc, char **argv, int **ab)
{
	int i;

	i = 0;
	if (ft_strequ(argv[1], "-v"))
		argc--;
	if (!(ab[0] = (int*)ft_memalloc(sizeof(int) * (argc - 1))))
		return (1);
	if (!(ab[1] = (int*)ft_memalloc(sizeof(int) * (argc - 1))))
		return (1);
	if (!(ab[2] = (int*)ft_memalloc(sizeof(int))))
		return (1);
	if (!(ab[3] = (int*)ft_memalloc(sizeof(int))))
		return (1);
	ab[2][0] = argc - 1;
	ab[3][0] = 0;
	while (argc > ++i)
		ab[0][i - 1] = ft_atoi(argv[i + (ft_strequ(argv[1], "-v"))]);
	return (0);
}

int	check_order(int **ab)
{
	int i;

	i = 0;
	if (*ab[3])
		return (0);
	while (*ab[2] > ++i)
		if (ab[0][i - 1] > ab[0][i])
			return (0);
	return (1);
}

int	check_input(char *input)
{
	if (ft_strequ(input, "sa") || ft_strequ(input, "sb") ||
		ft_strequ(input, "ss") || ft_strequ(input, "pa") ||
		ft_strequ(input, "pb") || ft_strequ(input, "ra") ||
		ft_strequ(input, "rb") || ft_strequ(input, "rr") ||
		ft_strequ(input, "rra") || ft_strequ(input, "rrb") ||
		ft_strequ(input, "rrr"))
		return (1);
	return (0);
}

void	handle_operation(int **ab, char *input)
{
	if (ft_strequ(input, "sa"))
		handle_sa(&ab);
	if (ft_strequ(input, "sb"))
		handle_sb(&ab);
	if (ft_strequ(input, "ss"))
		handle_ss(&ab);
	if (ft_strequ(input, "pa"))
		handle_pa(&ab);
	if (ft_strequ(input, "pb"))
		handle_pb(&ab);
	if (ft_strequ(input, "ra"))
		handle_ra(&ab);
	if (ft_strequ(input, "rb"))
		handle_rb(&ab);
	if (ft_strequ(input, "rr"))
		handle_rr(&ab);
	if (ft_strequ(input, "rra"))
		handle_rra(&ab);
	if (ft_strequ(input, "rrb"))
		handle_rrb(&ab);
	if (ft_strequ(input, "rrr"))
		handle_rrr(&ab);
}

void	debug_print(int **ab)
{
	int i;

	i = 0;
	ft_printf("%sStack a:    %sStack b:\n", "\x1B[31m", "\x1B[32m");
	while (*ab[2] > i || *ab[3] > i)
	{
		if (*ab[2] > i)
			ft_printf("%s%-8d  ", "\x1B[31m", ab[0][i]);
		else
			ft_printf("          ");
		if (*ab[3] > i)
			ft_printf("%s  %d", "\x1B[32m", ab[1][i]);
		ft_putendl("");
		i++;
	}
}

int	handle_input(int **ab, char *input, int debug_mode)
{
	if (!check_input(input))
		return (1);
	handle_operation(ab, input);
	if (debug_mode)
		debug_print(ab);
	return (0);
}

int	handle_sorting(int **ab, int debug_mode)
{
	char *input;

	while (1)
	{
		if (get_next_line(0, &input) == 0)
			break ;
		if (handle_input(ab, input, debug_mode))
			return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	int *ab[4];

	if (argc == 1 || (argc == 2 && ft_strequ(argv[1], "-v")))
		return (0);
	if (check_error(argc, argv))
	{
		write(2, "Error\n", 6);
		return (1);
	}
	if (create_stacks(argc, argv, ab))
		return (1);
	if (ft_strequ(argv[1], "-v"))
		debug_print(ab);
	if (handle_sorting(ab, ft_strequ(argv[1], "-v")))
	{
		if (check_order(ab))
			write(1, "OK\n", 3);
		else
			write(1, "KO\n", 3);
	}
	else
		write(2, "Error\n", 6);
	return (0);
}