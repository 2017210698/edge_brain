# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""

import numpy as np
import matplotlib.pyplot as plt
from scipy.signal import hilbert, chirp, convolve
from scipy import fftpack


t=np.arange(256)

print("-------------------------\n")
signal=1.2*np.sin(2*3.1415926*50*t/1000)+1


print("------------------------\n")

# signal=np.array([1,2,3,4,5,6])
hx = fftpack.hilbert(signal)
print("scipy hilbert:", hx)
print('\n')

x = fftpack.fft(signal)

# print("fft: \n")
# for i in range(x.shape[0]):
#   print("(",i,")",": ",x[i],end=" ")
#   if(i%4==0):
#     print("\n")

# y=np.abs(x)

# print("\nmag: ")
# for i in range(y.shape[0]):
#   print("(",i,")",": ",y[i],end=" ")
#   if(i%4==0):
#     print("\n")
h=[]
for i in t:
  if i==0:
    h.append(1)

  elif i<len(t)/2:
    h.append(2)
  elif i==len(t)/2:
    h.append(1)
  else:
    h.append(0)

# # for i in t:
# #   print(i,":",h[i],end=" ")

xh = -x*h
print("\n fft x:",x)
print("\n xh:",xh)

ifft=fftpack.ifft(xh)
print("\n")
print("my ifft:", ifft)

hx2 = np.imag(ifft)

print("\n")
print("my hilbert", hx2)

hxx=np.sqrt(signal**2 + hx2**2)

print("\n")
print("my mag:", hxx)

Hxfft=fftpack.fft(hxx)
print("\n")
print("my Hxfft:", Hxfft)

env_spec = np.abs(Hxfft)

print("\n")
print("my env_spec:", env_spec)


# duration = 1.0
# fs = 400.0
# samples = int(fs * duration)
# t = np.arange(samples) / fs

# signal = chirp(t, 20.0, t[-1], 100.0)
# signal *= (1.0 + 0.5 * np.sin(2.0 * np.pi * 3.0 * t))
# a=signal.tolist()

# for i in a:
#   print(i,end=",")

# hx = fftpack.hilbert(signal)
# hxx=np.sqrt(signal**2 + hx**2)
# env_spec = np.abs(np.fft.fft(hxx))
# N2 = len(env_spec)//2
# env_spec = env_spec[:N2]

# plt.plot(signal, label='siganl')
# plt.plot(hxx , label='envelope')
# plt.legend()

# plt.figure()
# plt.plot(env_spec)
# plt.show()