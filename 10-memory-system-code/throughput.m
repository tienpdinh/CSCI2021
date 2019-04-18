% produce a plot of the timing data for a run of matrix_timing.c
% run in GNU Octave or Matlab
rng = 1:32;                             % how many rows to plot

d=load('timing_data.dat');
plot(d(rng,1),d(rng,2),'o-');
xlabel('Stride');
ylabel('Throughput');
print -dpng throughput.png
