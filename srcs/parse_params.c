#include "../includes/tester.h"

t_parameters	init_parameters(int argc, char **argv)
{
	t_parameters p;

	p.valgrind = 1;
	p.answers = 1;
	p.test = 1;

	p.valg_timeout = 5;
	p.answer_timeout = 1000;

	return (p);
}
