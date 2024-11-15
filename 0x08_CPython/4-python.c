#include <Python.h>
#include <stdio.h>
#include <stdlib.h>

void print_python_string(PyObject *po)
{
	PyASCIIObject *pao = NULL;

	setbuf(stdout, NULL);
	printf("[.] string object info\n");

	if (!po || po->ob_type != &PyUnicode_Type)
	{
		printf("  [ERROR] Invalid String Object\n");
		return;
	}

	pao = (PyASCIIObject *)po;
	printf("  length: %lu\n", pao->length);
	if (pao->state.ascii)
	{
		printf("  type: compact ascii\n");
		printf("  value: %s\n", PyUnicode_1BYTE_DATA(po));
	}
	else
	{
		printf("  type: compact unicode object\n");
		printf("  value: %hn\n", PyUnicode_2BYTE_DATA(po));
	}
}
