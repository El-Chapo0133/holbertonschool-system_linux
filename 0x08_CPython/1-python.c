#include <Python.h>
#include <stdio.h>
#include <stdlib.h>


void print_python_list(PyObject *po)
{
	size_t po_size = ((PyVarObject *)po)->ob_size;
	size_t index;
	
	printf("[*] Python list info\n");
	printf("[*] Size of the Python list = %ld\n", po_size);
	printf("[*] Allocated = %ld\n", po->allocated);

	for (index = 0; index < po_size; index++)
	{
		printf("Element %ld: %s\n", index, 
				((PyListObject *)po)->ob_item[index]->ob_type->tp_name);
	}
}
