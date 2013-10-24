#include <Python.h>

#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


static PyObject	*shannon_entropy(PyObject *, PyObject *);


static PyMethodDef entropy_methods[] = {
	{"shannon_entropy",
	    shannon_entropy, METH_VARARGS, "Calculate entropy of bytestring."},
	{NULL, NULL, 0, NULL}
};


PyMODINIT_FUNC
initentropy(void)
{
	Py_InitModule("entropy", entropy_methods);
}

static PyObject *
shannon_entropy(PyObject *self, PyObject *args)
{
	const char	*data;
	float		 ent = 0, p;
	size_t		*counts;
	size_t		 n, i;

	if (!PyArg_ParseTuple(args, "s#", &data, &n))
		return (NULL);

	if (!(counts = malloc(sizeof(*counts) * 256))) {
		return (PyErr_NoMemory());
	}
	memset(counts, '\0', sizeof(*counts) * 256);
	for (i = 0; i < n; i++)
		counts[(unsigned char)data[i]] += 1;

	for (i = 0; i < 256; i++) {
		if (!counts[i])
			continue;
		p = (float)counts[i] / n;
		ent -= p * logf(p) / logf(256);
	}
	free(counts);
	return (Py_BuildValue("f", ent));
}
