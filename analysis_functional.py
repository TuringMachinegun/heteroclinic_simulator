import numpy as np
import sim_data_transf_pb2 as pb
import os
from collections import Counter, OrderedDict
from itertools import permutations
import scipy.stats as stats
# import matplotlib.pyplot as plt
# import fixed_currents_sims as fcs
import re
import cPickle as pickle
from pathos.multiprocessing import ProcessingPool as Pool

ROOT = 0
CHILDIR = 1
FILES = 2

perms = [p for p in permutations(range(5))]
saddles = ["".join(s) for s in permutations("aabbc")]
perm_dict = {p: {s: "".join([s[i] for i in p])
                 for s in saddles}
             for p in perms}


def branch(saddle_seq, count):
    # double initial list
    # apply one transf to first half
    # another to the second
    # merge list
    # rinse and repeat
    if isinstance(saddle_seq, str):
        saddle_seq = [[saddle_seq]]

    saddle_seq1 = [x[:] for x in saddle_seq]
    saddle_seq2 = [x[:] for x in saddle_seq]

    change = {'b': 'a', 'c': 'b', 'a': 'b'}
    for seq1, seq2 in zip(saddle_seq1, saddle_seq2):
        saddle = list(seq1[-1])
        a1_idx = saddle.index('a')
        a2_idx = saddle.index('a', a1_idx + 1)

        new_saddle1 = [change[cl] for cl in saddle]
        new_saddle2 = [change[cl] for cl in saddle]
        new_saddle1[a1_idx] = 'c'
        new_saddle2[a2_idx] = 'c'

        seq1.append("".join(new_saddle1))
        seq2.append("".join(new_saddle2))

    final_seq = saddle_seq1 + saddle_seq2

    if count > 2:
        return branch(final_seq, count - 1)
    else:
        return final_seq


def make_alphabet(word_len):

    perms = set(["".join(x) for x in permutations("aabbc")])

    if word_len > 1:
        alphabet = reduce(list.__add__, [branch(x, word_len) for x
                                         in perms])
        alphabet = map(tuple, alphabet)
    else:
        alphabet = [(i,) for i in perms]

    alphabet.sort()
    return alphabet


class WordCounter():

    def __init__(self, alphabet):
        self.counter_initializer = dict.fromkeys(alphabet, 0)

    def __call__(self, words):
        word_counter = Counter(self.counter_initializer)
        word_counter.update(words)
        sorted_counter = sorted(word_counter.items())
        sorted_count = zip(*sorted_counter)[1]
        count = np.array(sorted_count, dtype=np.float64)
        return count


def dump_parse(dump, f):
    dump.ParseFromString(f.read())
    return dump


def load_amp_data(amp_dir):  # by initial condition
    """Load data by amplitude.

    Return a list, each entry of the list corresponding to a
    file in the amplitude directory. Each entry is a dict
    {"ids": all saddle ids in file, "tot_time" simulation time
    for file}

    """

    f_list = next(os.walk(amp_dir))[FILES][:]

    f_list.sort()
    # [os.path.join(amp_dir, f) for f in f_list]
    print "loading ", amp_dir

    data_by_init_cond = []

    for f in f_list:
        ofile = open(os.path.join(amp_dir, f), "rb")
        parsed = dump_parse(pb.Data_dump(), ofile)
        data_dict = {"ids": [s.saddle_id for s in
                             parsed.saddle_t_and_id], "tot_time":
                     parsed.saddle_t_and_id[-1].saddle_t}
        data_by_init_cond.append(data_dict)

    return data_by_init_cond


def words_from_letters(saddle_ids, word_len):
    return [tuple(saddle_ids[i + x] for x in range(word_len))
            for i in range(len(saddle_ids) - word_len + 1)]


def parse_word_data(word_counter, word_len, amp_data):
    """set alphabet of the analyzer to be of word lenght = word_len,
    (re-)process the data based on the new alphabet.
    """

    # words by initial condition
    wds_by_ic = [words_from_letters(ic["ids"], word_len) for
                 ic in amp_data]
    w_count_by_ic = np.array([word_counter(wds) for wds in
                              wds_by_ic])

    return w_count_by_ic


def load_word_idx_dict(alphabet):
    """Make permutations dictionary.
    """

    dict_path = "./perm_dicts"
    dict_fname = "{}_ordered.pkl".format(len(alphabet[0]))

    # if dictionary was computed before, load it
    if os.path.isfile(os.path.join(dict_path, dict_fname)):

        with open(os.path.join(dict_path, dict_fname), "r") as dict_f:
            return pickle.load(dict_f)
    else:
        raise OSError("file not found")
        print "no {} in {}".format(dict_fname, dict_path)


def make_word_idx_dict(alphabet):

    dict_path = "./perm_dicts"
    dict_fname = "{}_ordered.pkl".format(len(alphabet[0]))

    w_idx = {w: i for i, w in enumerate(alphabet)}

    def idx_perm(perm_i, word_i):
        """Permute each saddle in word with permutation perm and return new
        word index on enumerated alphabet.
        """
        new_word = tuple(perm_dict[perm_i][s] for s in word_i)
        idx = w_idx[new_word]
        return idx

    perm_word_idx_d = np.array(
        [[idx_perm(p, w) for w in alphabet] for p in perms], dtype=np.uint32)

    if not os.path.exists(dict_path):
        os.mkdir(dict_path)

    with open(os.path.join(dict_path, dict_fname), "wb") as dict_f:
        pickle.dump(perm_word_idx_d, dict_f)


def p_wIi(words_count):
    """Given a count of each word in the alphabet, Return histogram with
    probability of each word (given an assumed input) in the
    alphabet.

    words_count is a list of tuples in the form (word, count), and
    is assumed to be sorted.
    """
    return words_count / np.sum(words_count)


def p_w(words_count, perm_word_idx_dict):

    all_p_wIi = np.array(words_count[perm_word_idx_dict], dtype=np.float)
    all_p_wIi /= np.sum(all_p_wIi, axis=1)[:, None]

    return np.mean(all_p_wIi, axis=0)


def avg_p_ws(wds_counts_by_ic, perm_word_idx_dict):
    p_ws = map(lambda x: p_w(x, perm_word_idx_dict), wds_counts_by_ic)

    return np.mean(p_ws, axis=0)


def avg_p_wIis(wds_counts_by_ic):
    tot_w_count = np.sum(wds_counts_by_ic, axis=0)
    return tot_w_count / np.sum(tot_w_count)


def analyze(amp_data, alphabet, word_counter, perm_word_idx_dict):

    w_count_by_ic = parse_word_data(word_counter, len(alphabet[0]), amp_data)
    sim_times = np.array([s["tot_time"] for s in amp_data])

    full_entropy = stats.entropy(avg_p_ws(w_count_by_ic,
                                          perm_word_idx_dict), base=2)
    noise_entropy = stats.entropy(avg_p_wIis(w_count_by_ic),
                                  base=2)
    mutual_info = full_entropy - noise_entropy

    info_rate = mutual_info / np.mean(sim_times)

    return full_entropy, noise_entropy, mutual_info, info_rate


def analyze_delta(root_dir, alphabet, word_counter, perm_word_idx_dict):

    all_amp_dirs = sorted(os.walk(root_dir).next()[CHILDIR],
                          key=lambda d: int(re.split('(\d+)', d)[1]))

    amp_abs_dirs = [os.path.join(root_dir, d) for d in all_amp_dirs]

    pool = Pool(len(amp_abs_dirs))

    amps_data = pool.map(load_amp_data, amp_abs_dirs)
    analyses = pool.map(lambda x: analyze(x, alphabet, word_counter,
                                          perm_word_idx_dict), amps_data)

    return np.array(analyses).T


def analyze_deltas(stop):
    all_dirs = os.walk(".").next()[CHILDIR]
    delta_dirs = [d for d in all_dirs if (d[:6] == "deltas")]

    print delta_dirs
    delta_dirs = sorted(delta_dirs, key=lambda d:
                        int(re.split('(\d+)', d)[1]))

    delta_dirs = delta_dirs[:stop]
    analyses = map(lambda d: analyze_delta(d, alph, wc, dic), delta_dirs)
    return analyses
