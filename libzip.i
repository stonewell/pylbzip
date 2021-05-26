%module libzip
%include "typemaps.i"

%{
    #include "zipconf.h"
    #include "zip.h"
%}

%include "zipconf.h"

%apply int * INOUT {int*_Nullable}

%include "zip.h"

