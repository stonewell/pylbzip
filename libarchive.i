%module archive
%include "typemaps.i"

%typemap(argout) archive_error_t * err {
    PyObject *o, *o2, *o3;
    o = PyLong_FromLong(*$1);
    if ((!$result)) {
        $result = Py_None;
    }

    if (!PyTuple_Check($result)) {
        PyObject *o2 = $result;
        $result = PyTuple_New(1);
        PyTuple_SetItem($result,0,o2);
    }

    o3 = PyTuple_New(1);
    PyTuple_SetItem(o3,0,o);
    o2 = $result;
    $result = PySequence_Concat(o2,o3);
    Py_DECREF(o2);
    Py_DECREF(o3);
}

%typemap(in,numinputs=0) archive_error_t * err(archive_error_t temp) {
    $1 = &temp;
}

%{
#include "libarchive.h"
%}

%include "libarchive.h"
