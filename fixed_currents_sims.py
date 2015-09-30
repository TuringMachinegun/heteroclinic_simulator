import numpy as np
from itertools import permutations

rate = 100.0
saddles = 1000

differences = np.logspace(-5, -7, num=3)
sig_noise_ratios = np.logspace(0.5, -0.5, num=10)

amps_for_each_delta = []

for dif in differences:
    amplitudes = ((dif / sig_noise_ratios) ** 2) / rate
    amplitudes = np.insert(amplitudes, 0, 0.0)  # no noise condition
    amps_for_each_delta.append(amplitudes)

pulses = ["1.596", "0.358", "1.954"]
volts = ["0", "0.74039804", "0.96216636"]

if __name__ == "__main__":

    import os
    import sys
    import subprocess

    simulator_path = "/home/giovanni/Dropbox/PycharmProjects/"\
                     "s221_simulations/event_based_sims/"\
                     "new_sims/bin/sim_executable"

    amp_par = ["-a"]
    out_f_par = ["-o"]

    sim_start = int(sys.argv[1])
    sim_stop = int(sys.argv[2])

    print sim_start, sim_stop

    procs = []

    perms = set(x for x in permutations([0, 0, 1, 1, 2]))

    all_deltas = [[str(i * x) for i in range(1, 6)] for x in differences]
    enum_deltas = [x for x in enumerate(all_deltas)]

    with open("sims.txt", "a") as sim_cl_file,\
            open(os.devnull, "w") as FNULL,\
            open("deltas.txt", "wb") as deltas_f:

        # first level: deltas
        for i, deltas_inst in enum_deltas[sim_start:sim_stop + 1]:

            delta_dir = "deltas" + str(i)
            if not os.path.exists(delta_dir):
                os.mkdir(delta_dir)
            deltas_f.write("{}\tdeltas={}\n".format(delta_dir, deltas_inst))

            amps = amps_for_each_delta[i]

            with open(os.path.join(os.curdir,
                                   delta_dir,
                                   "parameters.txt"),
                      "a") as amps_f:

                # second level: amplitudes
                for j, amp in enumerate(amps):

                    if amp == 0:
                        rate = 0
                    else:
                        rate = 100

                    amp_dir = os.path.join(delta_dir, "amp{}".format(j))
                    if not os.path.exists(amp_dir):
                        os.mkdir(amp_dir)

                    amps_f.write(
                        "{}\ta^2={}\tlambda={}\n".format(j, amp, rate))

                    # third level: saddles
                    for p, saddle_perm in enumerate(perms):

                        saddle_pulses = [pulses[x] for x in saddle_perm]
                        saddle_volts = [volts[x] for x in saddle_perm]

                        saddle_name = "saddle{}.dat".format(
                            "".join([str(x) for x in saddle_perm]))
                        saddle_dir = os.path.join(amp_dir, saddle_name)

                        par_list = [simulator_path] \
                            + ["-d"] + deltas_inst \
                            + ["-a", str(amp)] \
                            + ["-o", saddle_dir] \
                            + ["-r", str(rate)] \
                            + ["-l", "saddles", str(saddles)] \
                            + ["-v"] + saddle_volts \
                            + ["-p"] + saddle_pulses

                        sim_cl_file.write(" ".join(par_list) + "\n")
                        p = subprocess.Popen(par_list, stdout=FNULL)

                        procs.append(p)
                        if len(procs) > 8:
                            procs[-1].wait()

                            for p_n, proc in enumerate(procs):
                                if not proc.poll():
                                    procs.pop(p_n)
                        print "amp:", j
            print "deltas:", i
