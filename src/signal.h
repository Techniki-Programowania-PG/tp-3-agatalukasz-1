#ifndef SIGNAL_H
#define SIGNAL_H

#include <vector>
#include <complex>

std::vector<double> generate_sine(double amplitude, double frequency, double duration, int sample_rate);
std::vector<double> generate_cosine(double amplitude, double frequency, double duration, int sample_rate);
std::vector<double> generate_square(double amplitude, double frequency, double duration, int sample_rate);
std::vector<double> generate_sawtooth(double amplitude, double frequency, double duration, int sample_rate);


std::vector<std::complex<double>> dft(const std::vector<double>& x);
std::vector<double> idft(const std::vector<std::complex<double>>& spectrum);

#endif