#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <python3.5/Python.h>
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include "numpy/arrayobject.h"

int main()
{
    setenv("PYTHONPATH", ".", 1);

    Py_Initialize();
    import_array();

    PyObject* module = PyImport_ImportModule("object");
    assert(module != NULL);

    PyObject* klass = PyObject_GetAttrString(module, "Object");
    assert(klass != NULL);

    PyObject* obj = PyObject_CallObject(klass, nullptr);
    //PyObject* obj = PyInstance_New(klass, NULL, NULL);
    //assert(instance != NULL);

    PyObject* result = PyObject_CallMethod(obj, "initialize", "(i)", 1);
    assert(result != NULL);

    PyObject* result2 = PyObject_CallMethod(obj, "run", nullptr);
    assert(result2 != NULL);



    printf("1 + 2 = %ld\n", PyLong_AsLong(result));

    Py_DECREF(module);
    Py_DECREF(klass);
    Py_DECREF(obj);
    Py_DECREF(result);
    Py_DECREF(result2);

    Py_Finalize();

    return 0;
}
