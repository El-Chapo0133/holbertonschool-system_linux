#include <dirent.h>
#include <stdio.h>

/**
 * count_element_in_dir - count element in directory *d, then rewind
 * @d: DIR where to count element
 *
 * Return: quantity of element in DIR
 */
int count_element_in_dir(DIR *d) {
	int result = 0;
	while (readdir(d) != NULL) { result += 1; }
	/* re-place d at start */
	rewinddir(d);
	return (result);
}
