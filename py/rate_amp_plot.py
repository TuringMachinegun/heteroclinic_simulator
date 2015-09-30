import numpy as np
import matplotlib.pyplot as plt
import sim_data_transf_pb2 as pb
import sys
import os

sim_root = "../sim_data/"
rate_path = "rate100"
amp_path = "amp1e-6"
rate_files = [open(os.path.join(sim_root, rate_path, x), "rb")
              for x in os.listdir(os.path.join(sim_root, rate_path))
              if os.path.splitext(x)[1] == ".dat"]
rate_files.sort(key=lambda x: x.name)
amp_files = [open(os.path.join(sim_root, amp_path, x), "rb")
             for x in os.listdir(os.path.join(sim_root, amp_path))
             if os.path.splitext(x)[1] == ".dat"]
amp_files.sort(key=lambda x: x.name)

rate_dumps = [pb.Data_dump() for _ in rate_files]
amp_dumps = [pb.Data_dump() for _ in amp_files]

for i, f in enumerate(rate_files):
    rate_dumps[i].ParseFromString(f.read())
for i, f in enumerate(amp_files):
    amp_dumps[i].ParseFromString(f.read())

rate_resets = np.array([x.oscillator[0].reset_t for x in rate_dumps])
rate_resets = rate_resets[:, 1:] - rate_resets[:, :-1]

amp_resets = np.array([x.oscillator[0].reset_t for x in amp_dumps])
amp_resets = amp_resets[:, 1:] - amp_resets[:, :-1]

rate_stdevs = np.std(rate_resets, axis=1)
amp_stdevs = np.std(amp_resets, axis=1)


def make_fig(i, rate_resets, amp_resets):
    global ax1, ax2, ax3
    w = np.ones_like(rate_resets[i]) / rate_resets[i].size

    ax1 = plt.subplot2grid((3, 1), (0, 0))
    ax2 = plt.subplot2grid((3, 1), (1, 0))
    ax3 = plt.subplot2grid((3, 1), (2, 0))
    _, b1, _ = ax1.hist(rate_resets[i], weights=w, bins=50, alpha=0.2)

    ax1.axes.get_xlim()
    ax1.set_xticklabels([])
    ax2.axes.set_xlim(ax1.axes.get_xlim())
    ax2.set_xticklabels([])
    ax3.axes.set_xlim(ax1.axes.get_xlim())

    ax2.hist(amp_resets[i], bins=b1,  weights=w, alpha=.2, color="red")
    ax3.hist(rate_resets[i], bins=b1,  weights=w, alpha=.2)
    ax3.hist(amp_resets[i], bins=b1,  weights=w, alpha=.2, color="red")

    plt.draw()
