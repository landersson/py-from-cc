#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <Python.h>
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include "numpy/arrayobject.h"


PyArrayObject* cast_to_array(PyObject * obj)
{
    assert(PyArray_CheckExact(obj));
    return reinterpret_cast<PyArrayObject *>(obj);
}

//PyObject* build_np_array(int nd, const int* dims,
int main(int argc, char* argv[])
{
    setenv("PYTHONPATH", ".", 1);

    Py_Initialize();
    //Py_SetProgramName(argv[0]);
    import_array();

    PyObject* module = PyImport_ImportModule("object");
    assert(module != nullptr);

    PyObject* klass = PyObject_GetAttrString(module, "Object");
    assert(klass != nullptr);

    PyObject* s = Py_BuildValue("s", "Namn");
    assert(s);
    //auto args = PyTuple_New(1);
    //assert(args);
    //int rv = PyTuple_SetItem(args, 0, s);
    //assert(rv == 0);
    //PyObject* obj = PyObject_CallObject(klass, args);
    //Py_DECREF(args);

    PyObject* obj = PyObject_CallFunctionObjArgs(klass, s, nullptr);
    assert(obj);

    {
        PyObject* result = PyObject_CallMethod(obj, "initialize", "(i)", 1);
        assert(result != nullptr);
        Py_DECREF(result);
    }

    {
        PyObject* result = PyObject_CallMethod(obj, "run", nullptr);
        assert(result != nullptr);
        printf("1 + 2 = %ld\n", PyLong_AsLong(result));
        Py_DECREF(result);
    }

    // create 3,4,4 int array
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

    {
        PyObject* result = PyObject_CallMethod(obj, "array_sum", "O", np_array);
        //PyObject *result = PyObject_CallFunctionObjArgs(pFunc, pArray, nullptr);
        assert(result != nullptr);
        printf("sum = %ld\n", PyLong_AsLong(result));
        Py_DECREF(result);
    }

    {
        PyObject* o = PyObject_CallMethod(obj, "detect", "O", np_array);
        assert(o);
        if (!PyObject_TypeCheck(o, &PyTuple_Type))
        {
            fprintf(stderr, "Error, object is not a tuple\n");
        }
        else
        {
            assert(PyTuple_Size(o) == 2);

            PyArrayObject *boxes = cast_to_array(PyTuple_GetItem(o, 0));
            PyArrayObject *probs = cast_to_array(PyTuple_GetItem(o, 1));

            printf("BOXES: nd=%d\n", PyArray_NDIM(boxes));
            printf("PROBS: nd=%d\n", PyArray_NDIM(probs));

            //if (!PyObject_TypeCheck(o, &PyArray_Type))
            //{
                //fprintf(stderr, "Error, object is not an ndarray\n");
            //}
            //else
            //{
                //PyArrayObject* a = reinterpret_cast<PyArrayObject*>(o);
                //printf("NDIM: %d\n", PyArray_NDIM(a));
            //}
        }
        Py_DECREF(o);
    }

    Py_DECREF(np_array);
    Py_DECREF(obj);
    Py_DECREF(klass);
    Py_DECREF(module);

    Py_Finalize();

    return 0;
}
