/*
** my_pars.c for 42sh in /home/ovejer_n/Syst_unix/42sh
**
** Made by Ovejero Nicolas
** Login   <ovejer_n@epitech.net>
**
** Started on  Sun Apr 20 13:50:40 2014 Ovejero Nicolas
** Last update Wed Jun 11 11:06:00 2014 NicolasOVEJERO
*/

#include "gene.h"

char	*my_epur_str(char *line)
{
  int	i;
  int	j;
  char	*str;

  i = 0;
  j = 0;
  if ((str = malloc(sizeof(char) * strlen(line))) == NULL)
    return (NULL);
  while (line[i] == ' ' || line[i] == '\t')
    i++;
  if ((int)strlen(line) == i + 1)
    return (NULL);
  while (line[i])
    {
      if (line[i] == ' ' || line[i] == '\t')
	{
	  while (line[i] && (line[i] == ' ' || line[i] == '\t'))
	    i++;
	  str[j++] = ' ';
	}
      str[j++] = line[i++];
    }
  str[j - 1] = '\0';
  free(line);
  return (str);
}

int	pars_line_full(char *line)
{
  int	i;
  int	time_pipe;
  int	time_et;

  i = -1;
  time_pipe = 0;
  time_et = 0;
  while (line[++i])
    {
      if (line[i] == PIPE)
	time_pipe++;
      else if (line[i] == ET)
	time_et++;
      if ((time_pipe >= 3 && line[i - --time_pipe] == PIPE) ||
	  (time_et >= 3 && line[i - --time_et] == ET))
	{
	  printf("[42sh] : Syntax error\n");
	  return (-1);
	}
    }
  return (0);
}

int	pars_line(char *line)
{
  int	i;

  i = 0;
  while (line[i])
    {
      if (line[i] == SEMI_C && i == 0)
	{
	  printf("[42sh] : Syntax error with ';'\n");
	  return (-1);
	}
      if (line[i] == PIPE && (i == 0 || line[i + 1] == '\0'))
	{
	  printf("[42sh] : Syntax error with '|'\n");
	  return (-1);
	}
      if (line[i] == SEMI_C && line[i + 1] == SEMI_C)
	{
	  printf("[42sh] : Syntax error with ';;'\n");
	  return (-1);
	}
      i++;
    }
  return (pars_line_full(line));
}

int	my_pars(t_gene *utils)
{
  char	*line;
  char	temp[256];

  while (42)
    {
      getcwd(temp, sizeof(temp));
      write(1, "[42sh][", 7);
      my_putstr(temp);
      write(1, "]$ ", 3);
      if ((line = my_read(0)) == NULL)
        return (-1);
      if ((line = my_epur_str(line)) == NULL)
	free(line);
      else
	{
	  if (pars_line(line) == 0)
	    if (my_cmd(line, utils) == -1)
	      return (-1);
	  free(line);
	}
    }
  return (0);
}
