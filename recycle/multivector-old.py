# from https://github.com/enkimute/ganja.js/blob/master/codegen/python/r3.py

def mul(a,b):
    c=[0, 0,0,0, 0,0,0, 0]; 
    c[0]   =   +a[0]*b[0]  +a[1]*b[1]  +a[2]*b[2]  +a[3]*b[3]  -a[4]*b[4] -a[5]*b[5] -a[6]*b[6] -a[7]*b[7]; 
    c[1]   =   +a[0]*b[1]  +a[1]*b[0]  -a[2]*b[4]  +a[3]*b[6]  +a[4]*b[2] -a[5]*b[7] -a[6]*b[3] -a[7]*b[5]; 
    c[2]   =   +a[0]*b[2]  +a[1]*b[4]  +a[2]*b[0]  -a[3]*b[5]  -a[4]*b[1] +a[5]*b[3] -a[6]*b[7] -a[7]*b[6]; 
    c[3]   =   +a[0]*b[3]  -a[1]*b[6]  +a[2]*b[5]  +a[3]*b[0]  -a[4]*b[7] -a[5]*b[2] +a[6]*b[1] -a[7]*b[4]; 
    c[4]   =   +a[0]*b[4]  +a[1]*b[2]  -a[2]*b[1]  +a[3]*b[7]  +a[4]*b[0] -a[5]*b[6] +a[6]*b[5] +a[7]*b[3]; 
    c[5]   =   +a[0]*b[5]  +a[1]*b[7]  +a[2]*b[3]  -a[3]*b[2]  +a[4]*b[6] +a[5]*b[0] -a[6]*b[4] +a[7]*b[1]; 
    c[6]   =   +a[0]*b[6]  -a[1]*b[3]  +a[2]*b[7]  +a[3]*b[1]  -a[4]*b[5] +a[5]*b[4] +a[6]*b[0] +a[7]*b[2]; 
    c[7]   =   +a[0]*b[7]  +a[1]*b[5]  +a[2]*b[6]  +a[3]*b[4]  +a[4]*b[3] +a[5]*b[1] +a[6]*b[2] +a[7]*b[0];    
    return c;

def vector(a):
    return [0,a[0],a[1],a[2],0,0,0,0];

from math import *
t = 2*pi

v = vector([cos(t/8), sin(t/8), 0]);
a = vector([cos(t/8), sin(t/8), 0]);
b = vector([cos(t/8)*sin(t/8), sin(t/8)*sin(t/8), cos(t/8)]);

#multiply([b,a,v,a,b])
ba=mul(b,a); bav=mul(ba,v); bava=mul(bav,a); bavab=mul(bava,b); 

ba=mul(b,a); ab=mul(a,b); bav=mul(ba,v); bavab=mul(bav,ab); 
r=bavab;

