# TSPLINE python-bindings

## dependencies:

- [pybind11](http://pybind11.readthedocs.io/en/latest/index.html#)   
pybind11 is a header only library which creates bindings from c++ to python. (very similar to boost-python)  
__INSTALL__: download or clone from github: [pybind11-github](https://github.com/pybind/pybind11) and copy or link to the python-include-dir (eg. /usr/include/python2.7)

## compile:
to compile the TSPLINE python-bindings run cmake with the following option:
```
cmake .. -DMAKE_PYTHON_BINDINGS=ON
```
