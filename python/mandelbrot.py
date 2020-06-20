from ctypes import *

lib = CDLL("python/mandelbrot.so", RTLD_GLOBAL)

mandelbrot = lib.mandelbrot
mandelbrot.argtypes = [c_int, c_int, c_double, c_double, c_double, c_double, c_char_p]

if __name__ == "__main__":
    mandelbrot(400,400,0,0,4,4, c_char_p(b"out.ppm"))





# https://docs.python.org/3/library/ctypes.html
# https://github.com/pjreddie/darknet/blob/master/python/darknet.py

# def c_array(ctype, values):
#     """d = c_array(c_float, [0.0]*256)"""
    
#     arr = (ctype*len(values))()
#     arr[:] = values
#     return arr

