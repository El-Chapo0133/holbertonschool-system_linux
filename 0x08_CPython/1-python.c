#include <Python.h>
#include <stdio.h>
#include <stdlib.h>


void print_python_list(PyObject *po)
{
	PyVarObject *pvo = (PyVarObject *)po;
	PyListObject *plo = (PyListObject *)po;
	size_t po_size = pvo->ob_size;
	size_t index;
	
	printf("[*] Python list info\n");
	printf("[*] Size of the Python List = %ld\n", po_size);
	printf("[*] Allocated = %ld\n", plo->allocated);

	for (index = 0; index < po_size; index++)
	{
		printf("Element %ld: %s\n", index, 
			plo->ob_item[index]->ob_type->tp_name);
	}
}
