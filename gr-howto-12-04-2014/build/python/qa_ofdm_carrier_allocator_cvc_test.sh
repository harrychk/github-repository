#!/bin/sh
export GR_DONT_LOAD_PREFS=1
export srcdir=/home/chk/out-of-tree/gr-howto/python
export PATH=/home/chk/out-of-tree/gr-howto/build/python:$PATH
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$DYLD_LIBRARY_PATH
export DYLD_LIBRARY_PATH=$LD_LIBRARY_PATH:$DYLD_LIBRARY_PATH
export PYTHONPATH=/home/chk/out-of-tree/gr-howto/build/swig:$PYTHONPATH
/usr/bin/python2 /home/chk/out-of-tree/gr-howto/python/qa_ofdm_carrier_allocator_cvc.py 
