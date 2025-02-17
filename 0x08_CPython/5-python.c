#include <Python.h>
#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0

void print_python_int(PyObject *po)
{
	PyVarObject *pvo = (PyVarObject *)po;
	PyLongObject *plo = (PyLongObject *)po;
	ssize_t index, size, is_neg;
	unsigned long result = 0, buffer;
	int shift;

	setbuf(stdout, NULL);

	if (!PyLong_Check(po))
	{
		printf("Invalid Int Object\n");
		return;
	}
	size = pvo->ob_size;
	is_neg = size < 0;
	size = is_neg ? -size : size;

	/* Checks for overflows */
	if (size > 3 || (size == 3 && plo->ob_digit[2] > 0xf))
	{
		printf("C unsigned long int overflow\n");
		return;
	}
	/* loop over each digits and move them with the shift */
	for (index = 0; index < size; index++)
	{
		shift = PyLong_SHIFT * index;
		buffer = ((unsigned long)plo->ob_digit[index]) * (1UL << (shift));
		result += buffer;
	}

	if (is_neg)
		printf("-");
	printf("%lu\n", result);
}
