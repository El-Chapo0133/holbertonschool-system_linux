#include <Python.h>
#include <float.h>
#include <stdio.h>
#include <stdlib.h>

void print_python_float(PyObject *po)
{
	PyFloatObject *pfo = NULL;
	char *str;

	setbuf(stdout, NULL);

	printf("[.] float object info\n");
	
	if (!po || po->ob_type != &PyFloat_Type)
	{
		printf("  [ERROR] Invalid Float Object\n");
		return;
	}

	pfo = (PyFloatObject *)po;
	if (!pfo)
	{
		printf("  [ERROR] Invalid Float Object\n");
		return;
	}
	str = PyOS_double_to_string(pfo->ob_fval, 'g', 16, 0, NULL);

	printf("  value: %s%s\n", str, strchr(str, '.') ? "" : ".0");
}

void print_python_bytes(PyObject *po)
{
	PyVarObject *pvo = (PyVarObject *)po;
	PyBytesObject *pbo = (PyBytesObject *)po;
	size_t size = pvo->ob_size, index;

	setbuf(stdout, NULL);
	printf("[.] bytes object info\n");
	
	if (po->ob_type != &PyBytes_Type)
	{
		printf("  [ERROR] Invalid Bytes Object\n");
		return;
	}

	printf("  size: %ld\n", size);
	printf("  trying string: %s\n", pbo->ob_sval);

	size = size < 9 ? size + 1 : 10;
	printf("  first %ld bytes: ", size);
	for (index = 0; index < size; index++)
	{
		printf("%02hhx", pbo->ob_sval[index]);
		if (index + 1 == size)
			printf("\n");
		else
			printf(" ");
	}
}


void print_python_list(PyObject *po)
{
	PyVarObject *pvo = (PyVarObject *)po;
	PyListObject *plo = (PyListObject *)po;
	size_t po_size = pvo->ob_size;
	size_t index;
	
	setbuf(stdout, NULL);
	printf("[*] Python list info\n");
	
	if (!po || po->ob_type != &PyList_Type)
	{
		printf("  [ERROR] Invalid List Object\n");
		return;
	}
	
	printf("[*] Size of the Python List = %ld\n", po_size);
	printf("[*] Allocated = %ld\n", plo->allocated);

	for (index = 0; index < po_size; index++)
	{
		printf("Element %ld: %s\n", index, 
			plo->ob_item[index]->ob_type->tp_name);
		if (plo->ob_item[index]->ob_type == &PyBytes_Type)
			print_python_bytes(plo->ob_item[index]);
		else if (plo->ob_item[index]->ob_type == &PyFloat_Type)
			print_python_float(plo->ob_item[index]);
	}
}
