#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <Python.h>
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include "numpy/arrayobject.h"



//PyObject* build_np_array(int nd, const int* dims,
int main(int argc, char* argv[])
{
    setenv("PYTHONPATH", ".", 1);

    Py_Initialize();
    //Py_SetProgramName(argv[0]);
    import_array();

    PyObject* module = PyImport_ImportModule("object");
    assert(module != NULL);

    PyObject* klass = PyObject_GetAttrString(module, "Object");
    assert(klass != NULL);

    auto s = Py_BuildValue("s", "Namn");
    assert(s);
    //auto args = PyTuple_New(1);
    //assert(args);
    //int rv = PyTuple_SetItem(args, 0, s);
    //assert(rv == 0);

    //PyObject* obj = PyObject_CallObject(klass, args);
    //Py_DECREF(args);
    PyObject* obj = PyObject_CallFunctionObjArgs(klass, s);

    PyObject* result = PyObject_CallMethod(obj, "initialize", "(i)", 1);
    assert(result != NULL);

    PyObject* result2 = PyObject_CallMethod(obj, "run", nullptr);
    assert(result2 != NULL);



    const int ND = 3;
    const int C = 3;
    const int H = 4;
    const int W = 4;

    int arr[C][H][W];
    for (int c = 0; c < C; c++)
        for (int h = 0; h < H; h++)
            for (int w = 0; w < W; w++)
                arr[c][h][w] = 1;

    npy_intp dims[] = { C, H, W };

    PyObject *np_array = PyArray_SimpleNewFromData(
        ND, dims, NPY_INT32, reinterpret_cast<void*>(arr));
    assert(np_array);


    PyObject* result3 = PyObject_CallMethod(obj, "array_sum", "O", np_array);
    assert(result3 != NULL);

    printf("sum = %ld\n", PyLong_AsLong(result3));

    //PyObject *pReturn = PyObject_CallFunctionObjArgs(pFunc, pArray, NULL);
    //if (!pReturn)
        //goto fail_call;

    printf("1 + 2 = %ld\n", PyLong_AsLong(result));

    Py_DECREF(np_array);
    Py_DECREF(module);
    Py_DECREF(klass);
    Py_DECREF(obj);
    Py_DECREF(result);
    Py_DECREF(result2);

    Py_Finalize();

    return 0;
}
