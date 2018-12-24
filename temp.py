# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""

import numpy as np
import matplotlib.pyplot as plt
from scipy.signal import hilbert, chirp, convolve
from scipy import fftpack


# signal=np.array([1,2,3,4,5,6])
# hx = fftpack.hilbert(signal)
# print("scipy hilbert", hx)
# print('\n')


# t=np.arange(32)

# print("-------------------------\n")
# signal=1.2*np.sin(2*3.1415926*50*t/1000)+1


# print("------------------------\n")

# x = fftpack.fft(signal)
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

# for i in x:
#   print(i,end=",")

# h = [1,2,2,1,0,0]
# xh = -x*h
# print("\n xh:",xh)
# hx2 = np.imag(fftpack.ifft(xh))
# print("\n")
# print("my hilbert", hx2)



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

# from scipy import signal
# # def high_pass_filter(one_channel_data, samping_rate):
# #     # 低通滤波
#     b, a = signal.butter(4, 2 * 20 / sampling_rate, 'lowpass')
#     filtedData = signal.filtfilt(b, a, one_channel_data)  # data为要过滤的信号
#     filted_data = one_channel_data - filtedData
#     # return filted_data


# high_pass_filter(signal, 20000)



# from scipy import signal
# sampling_rate=1000
# duration = 1.0
# fs = 400.0
# samples = int(fs * duration)
# t = np.arange(samples) / fs

# signalb = chirp(t, 20.0, t[-1], 100.0)
# signala = signalb*(1.0 + 0.5 * np.sin(2.0 * np.pi * 3.0 * t))
# print("\nsignala:",signala)


# b, a = signal.butter(4, 2 * 80 / sampling_rate, 'lowpass')
# print("\nb:a:",b,a)

# filtedData = signal.filtfilt(b, a, signala)  # data为要过滤的信号
# filted_data = signala - filtedData
# print("\nfilted_data:",filted_data)

# b, a = signal.butter(4, 2 * 80 / sampling_rate, 'lowpass')
# print("\nb:a:",b,a)
# flitG = signal.filtfilt(b, a, signala)  # data为要过滤的信号

# print("\nfilteG:",flitG)



# t=np.arange(400)

# print("-------------------------\n")
# signala=1.2*np.sin(2*3.1415926*50*t/1000)+1.3*np.sin(2*3.1415926*200*t/1000)
# print("\nsignala:",signala)

# from scipy.signal import butter, filtfilt
# # input_signal = [1,2,3,4,5,1,2,3,4,5,1,2,3,4,1,2,3,4,5,1,2,3,4,5,1,2,3,4,5,1,2,3,4,5]
# [b,a] = butter(4, 2*80/1000, 'lowpass');
# print("\nb:a:",b,a)
# y = filtfilt(b, a, signala, padtype = 'odd', padlen=3*(max(len(b),len(a))-1))

# print(y)


r=np.random.randint(10,50,40)
# .reshape(2,20)
print(r)
a=np.mean(r)
print(a)
r=r-a
print(r)
# r_half=r[:, 8:10]
# print(r_half)
# max_ind=np.argmax(r_half[20:30])

