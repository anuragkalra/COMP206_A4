import sys
import copy
import time
from ctypes import *

def parseArgs(cmd_args):
	filter_width = int(cmd_args[3])
	filter_weights = []
	filter_width_squared = filter_width*filter_width
	for i in range(0, filter_width_squared):
		filter_weights.append(float(cmd_args[4+i]))
	return (filter_width, filter_weights)

t0 = time.time()

(pFilter_width, pFilter_weights) = parseArgs(sys.argv)

CFloatArrayType = c_float * len(pFilter_weights)
cFloatArrayInstance = CFloatArrayType( *pFilter_weights)

c_filter_weights = cFloatArrayInstance
c_filter_width = c_int(pFilter_width)

img_data = sys.argv[1]
out_name = sys.argv[2]

with open(img_data, "rb") as f:
	img_data_feed = f.read()

c_img_data = (c_ubyte * len(img_data_feed)).from_buffer_copy(img_data_feed)
c_out_img_data = (c_ubyte * len(img_data_feed)).from_buffer_copy(img_data_feed)

filter_lib = CDLL('libfast_filter.so')
filter_lib.doFiltering(c_img_data, c_filter_weights, c_filter_width, c_out_img_data)

with open(out_name, "wb") as d:
	d.write(bytearray(c_out_img_data))

t1 = time.time()

total = t1 - t0

print"Total execution time = "+str(total)


###########FUNCTION SIGNATURE##############################################
#void doFiltering( unsigned char* img_data, float* filter_weights,       
#                  int filter_width,        unsigned char* out_img_data );
###########################################################################