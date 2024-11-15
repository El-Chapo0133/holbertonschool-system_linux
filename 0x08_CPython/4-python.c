#include <Python.h>
#include <stdio.h>
#include <stdlib.h>


int is_py_ascii_object_compact(PyASCIIObject *pao)
{
	return (pao->state.ascii);
}
	
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
	if (is_py_ascii_object_compact(pao))
		printf("  type: compact ascii");
	else
		printf("  type: compact unicode object");

	printf("  length: %lu\n", pao->length);
	printf("  value: %s\n", PyUnicode_AS_UNICODE(po));
}
