from itertools import permutations

import matplotlib.pyplot as plt
from matplotlib.cm import get_cmap
from matplotlib.colors import LinearSegmentedColormap
import numpy as np

cmap = LinearSegmentedColormap.from_list('mycmap', [(0, 'black'),
                                                    (1.0, 'red')])


def next_sad(saddle, which):
    """saddle is a string, which is a boolean telling which of the two
    heteroclinic connection to follow. Returns new saddle.
    """
    s = list(saddle)
    temp_s = ["x"] * 5
    a_found = not which
    for i, c in enumerate(s):
        if c == "b":
            temp_s[i] = "a"
        elif c == "c":
            temp_s[i] = "b"
        elif c == "a":
            if a_found:
                temp_s[i] = "b"
            else:
                temp_s[i] = "c"
            a_found = not a_found
    return "".join(temp_s)


class HCPlotter():

    def __init__(self, **kwargs):
        self.trail_len = kwargs.get("trail_len", 10)

    def init_plot(self, ax, **kwargs):
        circle_radius = kwargs.get("circle_radius", 1.0)
        node_radius = kwargs.get("node_radius", 0.05)
        loffset = kwargs.get("label_offset", 0.15)
        self.cmap = get_cmap(kwargs.get("cmap", cmap))
        self.lw_hl = kwargs.get("lw_hl", 3.0)

        self.ax = ax

        saddles = sorted(["".join(x) for x in set(permutations("aabbc"))])
        s_to_1 = [next_sad(x, 0) for x in saddles]
        s_to_2 = [next_sad(x, 1) for x in saddles]
        e_1 = zip(saddles, s_to_1)
        e_2 = zip(saddles, s_to_2)
        transitions = sorted(e_1 + e_2)

        angles = np.linspace(0, 2 * np.pi, len(saddles), endpoint=False)
        xs = np.sin(angles) * circle_radius
        ys = np.cos(angles) * circle_radius
        circles = [plt.Circle((x, y), node_radius,
                              color=self.cmap(0), zorder=20)
                   for x, y in zip(xs, ys)]
        for c in circles:
            c.hl_val = 0.0

        self.saddles = dict(zip(saddles, circles))
        for c in self.saddles.values():
            ax.add_artist(c)

        lxs = np.sin(angles) * (1 + node_radius * 2 + loffset)
        lys = np.cos(angles) * (1 + node_radius * 2 + loffset)
        self.labels = [self.ax.text(x, y, s,
                                    rotation=-(360 * r) / (2 * np.pi) + 90,
                                    va="center", ha="center")
                       if r < np.pi else
                       self.ax.text(x, y, s,
                                    rotation=-(360 * r) / (2 * np.pi) - 90,
                                    va="center", ha="center")
                       for x, y, s, r in zip(lxs, lys, saddles, angles)]

        arrows = []
        self.base_lw = 0.1

        for t in transitions:
            x1, y1 = self.saddles[t[0]].center
            x2, y2 = self.saddles[t[1]].center
            th = np.arctan2((x2 - x1), (y2 - y1))
            x3 = x2 - np.sin(th) * node_radius
            y3 = y2 - np.cos(th) * node_radius
            dx = x3 - x1
            dy = y3 - y1
            arrows.append(self.ax.arrow(x1, y1, dx, dy,
                                        length_includes_head=True, lw=self.base_lw,
                                        head_width=0.03, color="black"))

        for a in arrows:
            a.hl_val = 0.0
        self.hconns = dict(zip(transitions, arrows))

    def set_properties(self, obj_list, **kwargs):
        for obj in obj_list:
            obj.set(**kwargs)

    def hl_saddle(self, saddle):
        for s, c in self.saddles.items():
            if s == saddle:
                c.hl_val = 1.0
                c.set_color(self.cmap(c.hl_val))
            elif c.hl_val > 0:
                new_hl_val = c.hl_val - 1.0 / self.trail_len
                c.hl_val = new_hl_val if (new_hl_val > 0) else 0
                c.set_color(self.cmap(c.hl_val))

    def hl_hconn(self, hconn):
        for c, a in self.hconns.items():
            if c == hconn:
                a.hl_val = self.trail_len
                a.set_color(self.cmap(1.0))
                a.set_linewidth(self.lw_hl)
                a.set_zorder(self.trail_len)
            elif a.hl_val > 0:
                new_hl_val = a.hl_val - 1
                a.hl_val = new_hl_val if (new_hl_val > 0) else 0.0
                norm_hl = float(a.hl_val) / self.trail_len
                a.set_color(self.cmap(norm_hl))
                a.set_linewidth(norm_hl * self.lw_hl
                                if norm_hl * self.lw_hl > self.base_lw
                                else self.base_lw)

                a.set_zorder(a.hl_val)

    def switch(self, saddle):
        self.hl_saddle(saddle)
        if hasattr(self, "last_saddle"):
            self.hl_hconn((self.last_saddle, saddle))
        self.last_saddle = saddle

# fig = plt.figure(figsize=[6, 6])
# ax = fig.add_subplot("111")
