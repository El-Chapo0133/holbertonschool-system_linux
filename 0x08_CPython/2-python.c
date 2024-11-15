#include <Python.h>
#include <stdio.h>
#include <stdlib.h>


void print_python_bytes(PyObject *po)
{
	PyVarObject *pvo = (PyVarObject *)po;
	PyBytesObject *pbo = (PyBytesObject *)po;
	size_t size = pvo->ob_size, index;

	printf("[,] bytes object info\n");
	
	if (po->ob_type != &PyBytes_Type)
	{
		printf("  [ERROR] Invalid Bytes Object\n");
		return;
	}

	printf("  size: %ld\n", size);
	printf("  trying string: %s\n"m pbo->ob_sval);

	size = size < 9 ? size + 1 : 10;
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
	
	printf("[*] Python list info\n");
	printf("[*] Size of the Python list = %ld\n", po_size);
	printf("[*] Allocated = %ld\n", po->allocated);

	for (index = 0; index < po_size; index++)
	{
		printf("Element %ld: %s\n", index, 
			plo->ob_item[index]->ob_type->tp_name);
	}
}
