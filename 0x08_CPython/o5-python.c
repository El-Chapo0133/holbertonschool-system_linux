#include <Python.h>
#include <stdio.h>

void print_python_int(PyObject *p)
{
	PyVarObject *pvo = (PyVarObject *)po;
	PyLongObject *plo = (PyLongObject *)po;
	ssize_t size, index, is_neg;
	unsigned long result = 0, buffer;

	setbuf(stdout, NULL);
	if (!PyLong_Check(p))
	{
		printf("Invalid Int Object\n");
		return;
	}
	sz = ((PyVarObject *)p)->ob_size;
	neg = sz < 0;
	sz = neg ? -sz : sz;
	if (sz > 3 || (sz == 3 && ((PyLongObject *)p)->ob_digit[2] > 0xf))
	{
		printf("C unsigned long int overflow\n");
		return;
	}
	for (i = 0; i < sz; i++)
	{
		int sh = PyLong_SHIFT * i;
		unsigned long sub =
			((unsigned long)((PyLongObject *)p)->ob_digit[i]) * (1UL << (sh));
		num += sub;
	}
	if (neg)
		printf("-");
	printf("%lu\n", num);
}
