#! /usr/bin/env python

from aubio import tempo, source

def get_beat(filename):
    win_s = 512                 # fft size
    hop_s = win_s // 2          # hop size

    samplerate = 44100

    s = source(filename, samplerate, hop_s)
    samplerate = s.samplerate
    o = tempo("default", win_s, hop_s, samplerate)

    # tempo detection delay, in samples
    # default to 4 blocks delay to catch up with
    delay = 4. * hop_s

    # list of beats, in samples
    beats = []

    # total number of frames read
    total_frames = 0
    while True:
        samples, read = s()
        is_beat = o(samples)
        if is_beat:
            this_beat = int(total_frames - delay + is_beat[0] * hop_s)
            #print("%f" % (this_beat / float(samplerate)))
            beats.append("%f" % (this_beat / float(samplerate)))
        total_frames += read
        if read < hop_s: break
    return beats