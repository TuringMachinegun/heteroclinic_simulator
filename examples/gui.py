import wx

import matplotlib
matplotlib.rcParams['toolbar'] = 'None'
matplotlib.use('tkAgg')
import matplotlib.pyplot as plt

import os
import sys
simulator_path = os.path.abspath(os.path.join("..", "python_wrapper", "bin"))
sys.path.append(simulator_path)

import visualizer as V
import lifnetsim as lns
import time

from multiprocessing import Process, Event, Value

deltas = [Value("d") for _ in range(5)]
noise_amp = Value("d")
trail_len = Value("i")
slowdown = Value("i")


class VisFrame(wx.Frame):

    def __init__(self, *args, **kwds):
        kwds["style"] = wx.DEFAULT_FRAME_STYLE ^ wx.RESIZE_BORDER
        wx.Frame.__init__(self, *args, **kwds)

        self.Bind(wx.EVT_CLOSE, self.on_close)

        self.ctr_panel = wx.Panel(self)
        self.delta_labels = [wx.StaticText(self.ctr_panel, label="%.1e" % 0)
                             for _ in range(5)]
        self.delta_sliders = [wx.Slider(self.ctr_panel, wx.ID_ANY, (i + 1) * 10 + 30, 1, 100)
                              for i in range(5)]
        for d_sl in self.delta_sliders:
            d_sl.Bind(wx.EVT_SLIDER, self.set_deltas)

        self.delta_box_staticbox = wx.StaticBox(
            self.ctr_panel, wx.ID_ANY, label="Delta currents")
        self.noise_lb = wx.StaticText(
            self.ctr_panel, wx.ID_ANY, label="%.1e" % 0)
        self.noise_slider = wx.Slider(self.ctr_panel, wx.ID_ANY, 50, 0, 100)
        self.noise_box_staticbox = wx.StaticBox(
            self.ctr_panel, wx.ID_ANY, label="Noise amplitude")

        self.noise_slider.Bind(wx.EVT_SLIDER, self.set_noise_amp)

        self.trailen_lb = wx.StaticText(
            self.ctr_panel, wx.ID_ANY, label="Trail length")
        self.trailen_sbt = wx.SpinCtrl(self.ctr_panel, min=1, max=50)

        self.trailen_sbt.Bind(wx.EVT_SPINCTRL, self.set_trail_len)

        self.slowdown_lb = wx.StaticText(
            self.ctr_panel, wx.ID_ANY, label="Slowdown")
        self.slowdown_spb = wx.SpinCtrl(self.ctr_panel, min=1, max=10)

        self.slowdown_spb.Bind(wx.EVT_SPINCTRL, self.set_slowdown)

        self.play_bt = wx.ToggleButton(self.ctr_panel, wx.ID_ANY, label="Play")
        self.playing = False
        self.play_bt.Bind(wx.EVT_TOGGLEBUTTON, self.play_pause_sim)
        self.vis_box_staticbox = wx.StaticBox(
            self.ctr_panel, wx.ID_ANY, label="Visualization")

        self.__set_properties()
        self.__do_layout()
        self.set_noise_amp(None)
        self.set_slowdown(None)
        self.set_deltas(None)
        self.set_trail_len(None)
        # end wxGlade

    def __set_properties(self):
        # begin wxGlade: MyFrame1.__set_properties
        self.SetTitle("Heteroclinic Computing Networks visualizer")
        self.SetSize((400, 500))
        for slider in self.delta_sliders:
            slider.SetMinSize((300, -1))
        self.noise_slider.SetMinSize((300, -1))
        # end wxGlade

    def __do_layout(self):
        # begin wxGlade: MyFrame1.__do_layout
        ctr_sizer = wx.BoxSizer(wx.VERTICAL)
        self.vis_box_staticbox.Lower()
        vis_box = wx.StaticBoxSizer(self.vis_box_staticbox, wx.HORIZONTAL)
        vis_grid = wx.FlexGridSizer(3, 2, 15, 10)
        self.noise_box_staticbox.Lower()
        noise_box = wx.StaticBoxSizer(self.noise_box_staticbox, wx.HORIZONTAL)
        noise_sizer = wx.BoxSizer(wx.HORIZONTAL)
        self.delta_box_staticbox.Lower()
        delta_box = wx.StaticBoxSizer(self.delta_box_staticbox, wx.HORIZONTAL)

        delta_grid = wx.FlexGridSizer(5, 2, 15, 10)

        for lb, sl in zip(self.delta_labels, self.delta_sliders):
            delta_grid.Add(lb, 0, 0, 0)
            delta_grid.Add(sl, 0, 0, 0)

        delta_box.Add(delta_grid, 1, wx.LEFT | wx.TOP | wx.EXPAND, 10)
        ctr_sizer.Add(delta_box, 1, wx.ALL | wx.EXPAND, 10)

        noise_sizer.Add(self.noise_lb, 0, 0, 30)
        noise_sizer.Add(self.noise_slider, 0, wx.LEFT, 20)
        noise_box.Add(noise_sizer, 1, wx.LEFT | wx.TOP, 10)
        ctr_sizer.Add(noise_box, 1, wx.ALL | wx.ALIGN_CENTER_VERTICAL | wx.SHAPED, 10)

        vis_grid.Add(self.trailen_lb, 0, wx.ALIGN_CENTER_VERTICAL, 0)
        vis_grid.Add(self.trailen_sbt, 0, 0, 0)
        vis_grid.Add(self.slowdown_lb, 0, wx.ALIGN_CENTER_VERTICAL, 0)
        vis_grid.Add(self.slowdown_spb, 0, 0, 0)
        vis_grid.Add(self.play_bt, 0, 0, 0)
        vis_box.Add(vis_grid, 1, wx.LEFT | wx.TOP | wx.ALIGN_CENTER_HORIZONTAL, 10)

        ctr_sizer.Add(vis_box, 1, wx.ALL | wx.EXPAND | wx.ALIGN_CENTER_HORIZONTAL, 10)

        self.ctr_panel.SetSizer(ctr_sizer)
        # end wxGlade

    def play_pause_sim(self, event):
        if playing.is_set():
            playing.clear()
        else:
            playing.set()

        self.play_bt.SetLabel("Play" if not playing.is_set() else "Pause")

    def set_deltas(self, event):
        values = [d_sl.GetValue() * 1e-6 for d_sl in self.delta_sliders]

        for i in range(5):
            self.delta_labels[i].SetLabel("%.1e" % values[i])
            deltas[i].value = values[i]

    def on_close(self, event):
        print "bye!"
        quitting.set()
        self.Destroy()

    def set_noise_amp(self, evucc):
        v = 10 ** -(14 - 5 * self.noise_slider.GetValue() / 100)
        noise_amp.value = v
        self.noise_lb.SetLabel("%.1e" % v)

    def set_trail_len(self, event):
        v = self.trailen_sbt.GetValue()
        trail_len.value = v

    def set_slowdown(self, event):
        v = self.slowdown_spb.GetValue()
        slowdown.value = v


playing = Event()
quitting = Event()


def sim_loop():
    pulses = [1.596, 1.596, 0.358, 0.358, 1.954]
    volts = [0.0, 0.0, 0.74039804, 0.74039804, 0.96216636]
    init_deltas = [1e-4, 2e-4, 3e-4, 4e-4, 5e-4]
    sim = lns.LifNetSim(volts, pulses, init_deltas)

    plt.ion()
    bho_figure = plt.figure(figsize=[6, 6])
    sax = bho_figure.add_subplot(111)
    vis = V.HCPlotter()
    vis.init_plot(sax, label_offset=0.15)
    sax.axis("off")
    sax.set_xlim([-1.25, 1.25])
    sax.set_ylim([-1.25, 1.25])
    bho_figure.canvas.draw()

    while not quitting.is_set():
        if playing.is_set():
            bho_figure.canvas.draw()
            sim.deltas = lns.DoubleVector([d.value for d in deltas])
            sim.set_noise(100, noise_amp.value)
            sim.run("saddles", 1)
            vis.trail_len = trail_len.value
            vis.switch(sim.saddle)
            time.sleep(slowdown.value * 0.001 * sim.time)

if __name__ == "__main__":

    app = wx.App(0)
    vis_frame = VisFrame(None, wx.ID_ANY, "")
    app.SetTopWindow(vis_frame)
    vis_frame.Show()

    plotter_thread = Process(target=sim_loop)
    plotter_thread.start()

    app.MainLoop()
