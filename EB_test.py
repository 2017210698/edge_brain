import csv
import numpy as np
 
f = open('eb_testdata.csv', 'r')
csvreader = csv.reader(f)
final_list = list(csvreader)
testData=[]
for ele in final_list:
  b=" ".join(ele)
  testData.append(b)

testData=' '.join(testData)


# print(type(testData))
testData=np.array(testData)
print(testData)

# from scipy import signal
# def high_pass_filter(one_channel_data, sampling_rate):
#     # 低通滤波
#     b, a = signal.butter(4, 2 * 20 / sampling_rate, 'lowpass')
#     filtedData = signal.filtfilt(b, a, one_channel_data)  # data为要过滤的信号
#     filted_data = one_channel_data - filtedData
#     return filted_data

# sampling_rate=1000
# high_pass_filter(testData, sampling_rate)

# import numpy as np
# def outlier_detection(data):
#     median = np.median(data)
#     b = 1.4826  # 可调
#     mad = b * np.median(np.abs(data - median))
#     lower_limit = median - (3 * mad)
#     upper_limit = median + (3 * mad)
#     for i in range(len(data)):
#         if(data[i]>upper_limit or data[i]<lower_limit):
#             data[i]=median
#     return data

# def ACF(sig, window_size = 2048, lmin=10, lmax=100, sampling_rate = 3200):  # sig:取一帧的信号
#     # 定义所分析音频的最小频率以及最大频率
#     lmin = round((lmin / sampling_rate) * window_size)
#     lmax = round((lmax / sampling_rate) * window_size)
#     r = np.convolve(sig, sig[::-1])  # 利用卷积计算相关函数
#     r = r / (np.mat(sig) * np.mat(sig).T)  # 相关函数的归一化
#     #     print(r)
#     r_half = r[:, :window_size]  # 自相关函数是对称的，取一半即可，后半部分为正
#     #     print(r_half)
#     max_ind = np.argmax(r_half[:, lmin:lmax])
#     #     print(max_ind)
#     max_f = lmin + max_ind - 1
#     pitch = max_f / window_size * sampling_rate
#     return abs(pitch)

import numpy as np
def fft_analysis(data, pitch, sampling_rate=3200, window_size=2048):  # 基频
    #滤波
    data = high_pass_filter(data)

    #减数据的均值
    data = data - np.mean(data)

    # FFT分析及画图程序
    df = sampling_rate / (window_size)  # 频率成分间隔
    fft_freq = [df * n for n in range(window_size)]  # 频率成分组合
    fft_transformed = abs(np.fft.fft(data, n=window_size))  # fft分析
    d = int(len(fft_transformed) / 2)
    fft_freq = fft_freq[:d]
    fft_transformed = fft_transformed[:d]  # 取FFT分析结果前一半，因为前后是对称的

    # 提取频率成分和对应幅值
    fft_freq_num = []
    if((0.5 * pitch / df) >= 5):
        freq_interval = 5  # 频率间隔
    elif((0.5 * pitch / df) >= 4):
        freq_interval = 4  # 频率间隔
    elif ((0.5 * pitch / df) >= 3):
        freq_interval = 3  # 频率间隔
    elif ((0.5 * pitch / df) >= 2):
        freq_interval = 2  # 频率间隔
    elif ((0.5 * pitch / df) >= 1):
        freq_interval = 1  # 频率间隔
    else:
        freq_interval = 0  # 频率间隔

    # 计算0.5倍频
    min_index = int(0.5 * pitch / df) - freq_interval
    max_index = int(0.5 * pitch / df) + freq_interval
    signal_mid = fft_transformed[min_index:max_index]
    fft_freq_num.append(abs(np.max(signal_mid)))
    # 计算1-30倍频
    for i in np.arange(1, 31):
        min_index = int(i * pitch / df) - freq_interval
        max_index = int(i * pitch / df) + freq_interval
        signal_mid = fft_transformed[min_index:max_index]
        fft_freq_num.append(abs(np.max(signal_mid)))
    fft_freq_num = np.array(fft_freq_num).reshape(len(fft_freq_num))
    return fft_freq_num