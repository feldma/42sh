/*
** my_cmd.c for 42sh in /home/ovejer_n/rendu/PSU_2013_42sh/tmp_work/gene
**
** Made by ovejer_n
** Login   <ovejer_n@epitech.net>
**
** Started on  Mon May 12 21:27:38 2014 ovejer_n
** Last update Wed Jun 11 11:58:58 2014 NicolasOVEJERO
*/

#include "gene.h"

int	check_cmd(char **tab_fct, t_gene *utils)
{
  int	i;
  char	**tab_f;
  t_tab	tab_i;

  i = -1;
  utils->time = 0;
  init_tab(tab_i.tab_bf);
  if ((tab_f = tab()) == NULL)
    return (-2);
  while (tab_f[++i])
    if (strcmp(tab_f[i], tab_fct[0]) == 0)
      return (tab_i.tab_bf[i](tab_fct, utils));
  if (strcmp("kill", tab_fct[0]) == 0)
    if (my_kill(tab_fct, utils) == -1)
      return (-1);
  if (strncmp(tab_fct[0], "/", 1) == 0 || strncmp(tab_fct[0], "./", 2) == 0)
    return (exec_live(tab_fct, utils));
  return (exec_alias(tab_fct, utils, utils->nb));
}

int	pars_pr(char *cmd_line, t_gene *utils, int i)
{
  char	**chev_g;
  int	nb;

  if ((nb = nb_car_spe(cmd_line, RED_G)) != 0 &&
      nb_car_spe(cmd_line, PIPE) == 0 && cmd_line[0] != RED_G)
    {
      if ((chev_g = my_str_to_wordtab(cmd_line, RED_G)) == NULL)
	return (-2);
      if (chevg_base(chev_g, utils) == -1)
	return (-1);
      my_free_dtab(chev_g);
    }
  else if (nb_car_spe(cmd_line, RED_G) != 0 &&
	   nb_car_spe(cmd_line, PIPE) != 0 && cmd_line[0] != RED_G)
    return (pars_chevg_pipe(cmd_line, utils));
  else if (cmd_line[0] == RED_G)
    {
      start_chev(cmd_line, utils, i);
      if (i != 1)
      	return (my_pipe(epure_end(utils->chev, strlen(utils->chev)), utils));
    }
  else
    return (my_pipe(epure_end(cmd_line, strlen(cmd_line)), utils));
  return (0);
}

int	pars_cmd(char **tab_sd, t_gene *utils)
{
  int	i;
  int	rrrr;

  i = -1;
  rrrr = 0;
  utils->pipe.save = 0;
  utils->nb = 1;
  while (tab_sd[++i])
    if ((strcmp(tab_sd[i], DRED_D) == 0 || tab_sd[i][0] == RED_D) && i == 0)
      {
	(strcmp(tab_sd[i++], DRED_D) == 0) ?
	  (tab_sd[i] = strdup(bonjour(tab_sd[i], 2, utils))) :
	  (tab_sd[i] = strdup(bonjour(tab_sd[i], 1, utils)));
	rrrr += 2;
      }
    else if (strcmp(tab_sd[i], DRED_D) == 0 || tab_sd[i][0] == RED_D)
      {
	i++;
	(strcmp(tab_sd[i - 1], DRED_D) == 0) ? _my_open(tab_sd[i], 2, utils) :
	  _my_open(tab_sd[i], 1, utils);
      }
    else
      ++rrrr;
  return (other(tab_sd, utils, i, --rrrr));
}

int	my_cmd(char *line, t_gene *utils)
{
  if (pars_semicolon(line, utils) == -1)
    {
      if (pars_sp_da(line, utils) == -2)
	return (-1);
    }
  return (0);
}
