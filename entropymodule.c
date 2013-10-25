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

#if PY_MAJOR_VERSION >= 3
static struct PyModuleDef	moduledef = {
	PyModuleDef_HEAD_INIT,
	"entropy",
	NULL,
	0,
	entropy_methods,
	NULL,
	NULL,
	NULL,
	NULL
};


PyMODINIT_FUNC
PyInit_entropy(void)
{
	return (PyModule_Create(&moduledef));
}
#else
PyMODINIT_FUNC
initentropy(void)
{
	Py_InitModule("entropy", entropy_methods);
}
#endif

static PyObject *
shannon_entropy(PyObject *self, PyObject *args)
{
	const char	*data;
	double		 ent = 0, p;
	size_t		*counts;
	size_t		 n, i;

	if (!PyArg_ParseTuple(args, "s#", &data, &n))
		return (NULL);

	if (!(counts = calloc(256, sizeof(*counts))))
		return (PyErr_NoMemory());
	memset(counts, '\0', sizeof(*counts) * 256);

	for (i = 0; i < n; i++)
		counts[(unsigned char)data[i]] += 1;

	for (i = 0; i < 256; i++) {
		if (!counts[i])
			continue;
		p = (double)counts[i] / n;
		ent -= p * logf(p);
	}
	free(counts);

	ent /= logf(256);
	return (Py_BuildValue("d", ent));
}
