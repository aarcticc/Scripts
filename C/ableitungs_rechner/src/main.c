#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TERMS 100
#define MAX_INPUT 512

struct term {
	double coeff;	/* Coefficient */
	int exp;	/* Exponent */
};

struct polynomial {
	struct term terms[MAX_TERMS];
	int num_terms;
};

/**
 * parse_polynomial - Parse polynomial string into terms
 * @input: Input string (e.g., "3x^2+2x-5")
 * @poly: Pointer to polynomial structure
 *
 * Returns 0 on success, -1 on error
 */
static int parse_polynomial(const char *input, struct polynomial *poly)
{
	int i = 0;
	int term_idx = 0;
	char buffer[MAX_INPUT];
	char *pos = (char *)input;

	poly->num_terms = 0;

	while (*pos != '\0' && term_idx < MAX_TERMS) {
		double coeff = 0.0;
		int exp = 0;
		int sign = 1;

		/* Skip whitespace */
		while (*pos == ' ' || *pos == '\t')
			pos++;

		/* Handle sign */
		if (*pos == '+') {
			sign = 1;
			pos++;
		} else if (*pos == '-') {
			sign = -1;
			pos++;
		}

		/* Parse coefficient */
		i = 0;
		while (isdigit(*pos) || *pos == '.') {
			buffer[i++] = *pos;
			pos++;
		}

		if (i > 0) {
			buffer[i] = '\0';
			coeff = strtod(buffer, NULL);
		} else if (*pos == 'x') {
			coeff = 1.0;
		} else if (*pos == '\0' || *pos == '+' || *pos == '-') {
			if (i > 0)
				continue;
			else
				break;
		}

		/* Parse variable and exponent */
		if (*pos == 'x') {
			exp = 1;
			pos++;

			if (*pos == '^') {
				pos++;
				i = 0;
				while (isdigit(*pos)) {
					buffer[i++] = *pos;
					pos++;
				}
				if (i > 0) {
					buffer[i] = '\0';
					exp = atoi(buffer);
				}
			}
		} else {
			exp = 0;
		}

		/* Store term */
		poly->terms[term_idx].coeff = sign * coeff;
		poly->terms[term_idx].exp = exp;
		term_idx++;

		/* Skip whitespace */
		while (*pos == ' ' || *pos == '\t')
			pos++;
	}

	poly->num_terms = term_idx;
	return (term_idx > 0) ? 0 : -1;
}

/**
 * derive_polynomial - Compute derivative of polynomial
 * @poly: Input polynomial
 * @deriv: Output polynomial (derivative)
 *
 * Computes f'(x) from f(x)
 */
static void derive_polynomial(const struct polynomial *poly,
			      struct polynomial *deriv)
{
	int i;

	deriv->num_terms = 0;

	for (i = 0; i < poly->num_terms; i++) {
		if (poly->terms[i].exp > 0) {
			deriv->terms[deriv->num_terms].coeff =
				poly->terms[i].coeff * poly->terms[i].exp;
			deriv->terms[deriv->num_terms].exp =
				poly->terms[i].exp - 1;
			deriv->num_terms++;
		}
	}
}

/**
 * print_polynomial - Print polynomial in readable format
 * @poly: Polynomial to print
 * @name: Name of the polynomial (e.g., "f(x)", "f'(x)")
 */
static void print_polynomial(const struct polynomial *poly, const char *name)
{
	int i;

	printf("%s = ", name);

	if (poly->num_terms == 0) {
		printf("0\n");
		return;
	}

	for (i = 0; i < poly->num_terms; i++) {
		double coeff = poly->terms[i].coeff;
		int exp = poly->terms[i].exp;

		/* Print sign and coefficient */
		if (i == 0) {
			if (coeff >= 0)
				printf("%.0f", coeff);
			else
				printf("%.0f", coeff);
		} else {
			if (coeff >= 0)
				printf(" + %.0f", coeff);
			else
				printf(" - %.0f", -coeff);
		}

		/* Print variable and exponent */
		if (exp == 0) {
			/* Already printed coefficient */
		} else if (exp == 1) {
			printf("x");
		} else {
			printf("x^%d", exp);
		}
	}

	printf("\n");
}

int main(void)
{
	struct polynomial poly, deriv;
	char input[MAX_INPUT];

	printf("=== Polynomial Derivative Calculator ===\n");
	printf("Input format: 3x^2+2x-5 or 4x^3-x+7\n");
	printf("Enter polynomial: ");

	if (fgets(input, sizeof(input), stdin) == NULL)
		return 1;

	/* Remove newline */
	input[strcspn(input, "\n")] = '\0';

	if (parse_polynomial(input, &poly) < 0) {
		fprintf(stderr, "Error: Invalid polynomial format\n");
		return 1;
	}

	print_polynomial(&poly, "f(x)");

	derive_polynomial(&poly, &deriv);

	print_polynomial(&deriv, "f'(x)");

	return 0;
}