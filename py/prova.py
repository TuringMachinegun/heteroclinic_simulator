# coding: utf-8


def make_fig(rate_resets, amp_resets):
ax1 = plt.subplot2grid((3, 1), (0, 0))
ax2 = plt.subplot2grid((3, 1), (1, 0))
ax3 = plt.subplot2grid((3, 1), (2, 0))
_, b1, _ = ax1.hist(rate_resets[i], bins=50, alpha=0.2)

ax1.axes.get_xlim()
ax2.axes.set_xlim(ax1.axes.get_xlim())
ax3.axes.set_xlim(ax1.axes.get_xlim())

ax2.hist(amp_resets[i], bins=b1, alpha=.2, color="red")
ax3.hist(rate_rests[i], bins=b1, alpha=.2)
ax3.hist(amp_resets[i], bins=b1, alpha=.2, color="red")

plt.draw()
