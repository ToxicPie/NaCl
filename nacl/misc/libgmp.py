from ctypes import *

# computes 10**4300
gmp = CDLL('libgmp.so')
x = create_string_buffer(b'\x00'*16)
gmp.__gmpz_init_set_ui(byref(x), 10)
gmp.__gmpz_pow_ui(byref(x), byref(x), 4300)
gmp.__gmp_printf(b'%Zd\n', byref(x))
gmp.__gmpz_clear(byref(x))
# objdump -T `whereis libgmp.so`
