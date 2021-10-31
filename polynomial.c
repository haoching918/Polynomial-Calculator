#include "polynomial.h"

void menu()
{
	printf("\nMenu:\n");
	printf("\t1) initialize a polynomial\n");
	printf("\t2) show a polynomial\n");
	printf("\t3) show particular coefficient\n");
	printf("\t4) delete/add term\n");
	printf("\t5) polynomial addition\n");
	printf("\t6) polynomial subtraction\n");
	printf("\t7) polynomial multiplication\n");
	printf("\t8) polynomial division\n");
	printf("\t0) exit\n");
	printf("\t9) show name book\n");
	printf("\n");
}

void show_nameBook()
{
	for (size_t i = 0; i < MAX_MEMBER; i++)
	{
		if (nameBook[i].used)
			printf("%s ", nameBook[i].name);
	}
	printf("\n");
}

void initialize(polynomial P[MAX_TERM])
{
	for (size_t i = 0; i < MAX_TERM; i++)
	{
		P[i].coef = 0;
		P[i].expo = 0;
	}
}

void init_poly()
{
	printf("Please name the polynomial: ");
	for (size_t i = 0; i < MAX_MEMBER; i++)
	{
		if (nameBook[i].used)
			continue;
		else
			nameBook[i].used = 1;

		fgets(nameBook[i].name, 32, stdin);
		nameBook[i].name[strlen(nameBook[i].name) - 1] = '\0';
		initialize(nameBook[i].p);

		char choice;
		for (size_t j = 0; j < MAX_TERM; j++)
		{
			printf("Please enter coefficient: ");
			scanf("%f", &nameBook[i].p[j].coef);
			CLEARBUF
			printf("Please enter exponent: ");
			scanf("%d", &nameBook[i].p[j].expo);
			CLEARBUF
			// if enter same exponent
			for (size_t k = 0; k < j; k++)
			{
				if (nameBook[i].p[k].expo == nameBook[i].p[j].expo)
				{
					nameBook[i].p[k].coef = nameBook[i].p[j].coef;
					nameBook[i].p[j].expo = 0;
					nameBook[i].p[j].coef = 0;
					j--;
					break;
				}
			}

			printf("Continue? (y/n): ");
			scanf("%c", &choice);
			if (choice == 'n')
				break;
		}
		poly_sort(nameBook[i].p);
		break;
	}
}

void poly_sort(polynomial P[MAX_TERM])
{
	for (size_t i = 0; i < MAX_TERM && P[i].coef != 0; i++)
	{
		for (size_t j = i; j < MAX_TERM && P[j].coef != 0; j++)
		{
			if (P[i].expo < P[j].expo)
			{
				polynomial tmp = P[i];
				P[i] = P[j];
				P[j] = tmp;
			}
		}
	}
}
polynomial *find_index()
{
	while (1)
	{
		char tmpName[32];
		printf("Please enter the poly name : ");

		fgets(tmpName, 32, stdin);
		tmpName[strlen(tmpName) - 1] = '\0';

		for (size_t i = 0; i < MAX_MEMBER; i++)
		{
			if (!strncmp(tmpName, nameBook[i].name, 32))
			{
				print_poly(nameBook[i].p);
				return nameBook[i].p;
			}
		}
		printf("polynomial not found\n");
	}
}

void print_poly(polynomial P[MAX_TERM])
{
	// first term
	if (P[0].coef == 0)
		return;

	if (P[0].coef > 0)
	{
		if (P[0].coef == 1)
			printf("x^%d ", P[0].expo);
		else
			printf("%.3fx^%d ", P[0].coef, P[0].expo);
	}
	else
	{
		if (P[0].coef == -1)
			printf("-x^%d ", P[0].expo);
		else
			printf("%.3fx^%d ", P[0].coef, P[0].expo);
	}

	// the rest
	for (size_t i = 1; i < MAX_TERM && P[i].coef != 0; i++)
	{
		if (P[i].coef > 0)
		{
			if (P[i].coef == 1)
				printf("+ x^%d ", P[i].expo);
			else
				printf("+ %.3fx^%d ", P[i].coef, P[i].expo);
		}
		else
		{
			if (P[i].coef == -1)
				printf("-x^%d ", P[i].expo);
			else
				printf("%.3fx^%d ", P[i].coef, P[i].expo);
		}
	}
	printf("\n");
}
void show_poly()
{
	find_index();
}

void coef()
{
	// create tmp P
	polynomial tmpP[MAX_TERM];
	memcpy(&tmpP, find_index(), sizeof(tmpP));

	// find exponent
	int32_t exponent = 0;
	while (1)
	{
		printf("Please enter exponent: ");
		if (scanf("%d", &exponent) != 1)
		{
			printf("incompatible input\n");
			CLEARBUF
			continue;
		}
		CLEARBUF

		for (size_t i = 0; i < MAX_TERM; i++)
		{
			if (tmpP[i].expo == exponent)
			{
				printf("coefficient: %.3f\n", tmpP[i].coef);
				return;
			}
		}
		printf("exponent not found\n");
	}
}

void shift(polynomial P[MAX_TERM], int32_t i)
{
	// shift the rest
	while (P[i + 1].coef != 0)
	{
		P[i] = P[i + 1];
		i++;
	}
	P[i].coef = 0;
	P[i].expo = 0;
}

void add_delete_term()
{
	// find nameBook index
	int32_t index = 0;
	char tmpName[32];
	printf("Please enter the poly name : ");
	fgets(tmpName, 32, stdin);
	tmpName[strlen(tmpName) - 1] = '\0';
	for (size_t i = 0; i < MAX_MEMBER; i++)
	{
		if (!strncmp(tmpName, nameBook[i].name, 32))
		{
			index = i;
			break;
		}
	}

	// get choice
	int32_t choice;
	while (1)
	{
		choice = 0;
		printf("1) add\n2) delete\n");
		printf("choice: ");
		if ((scanf("%d", &choice)) != 1 || (choice != 1 && choice != 2))
		{
			printf("Invalid input\n");
			CLEARBUF
			continue;
		}
		CLEARBUF
		break;
	}

	// add or delete
	if (choice == 1)
	{
		if (nameBook[index].p[MAX_MEMBER - 1].coef != 0)
		{
			printf("Already full\n");
			return;
		}
		for (size_t i = 0; i < MAX_MEMBER; i++)
		{
			if (nameBook[index].p[i].coef == 0)
			{
				printf("Please enter coefficient: ");
				scanf("%f", &nameBook[index].p[i].coef);
				CLEARBUF
				printf("Please enter exponent: ");
				scanf("%d", &nameBook[index].p[i].expo);
				CLEARBUF
				
				// if enter same exponent
				for (size_t k = 0; k < i; k++)
				{
					if (nameBook[index].p[k].expo == nameBook[index].p[i].expo)
					{
						nameBook[index].p[k].coef = nameBook[index].p[i].coef;
						nameBook[index].p[i].expo = 0;
						nameBook[index].p[i].coef = 0;
						i--;
						break;
					}
				}
				poly_sort(nameBook[index].p);
				return;
			}
		}
	}
	else if (choice == 2)
	{
		int32_t exponent;
		while (1)
		{
			exponent = 0;
			printf("Please enter exponent: ");
			if (scanf("%d", &exponent) != 1)
			{
				printf("incompatible input\n");
				CLEARBUF
				continue;
			}
			CLEARBUF

			for (size_t i = 0; i < MAX_TERM; i++)
			{
				if (nameBook[index].p[i].expo == exponent)
				{
					shift(nameBook[index].p, i);
					return;
				}
			}
		}
	}
}