#include "signal.h"
#include <cmath>
#include <algorithm>
#include <vector>
#include <complex>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

std::vector<double> generate_sine(double amplitude, double frequency, double duration, int sample_rate) {
    int total_samples = static_cast<int>(duration * sample_rate);
    std::vector<double> signal(total_samples);
    for (int i = 0; i < total_samples; ++i) {
        double t = static_cast<double>(i) / sample_rate;
        signal[i] = amplitude * std::sin(2 * M_PI * frequency * t);
    }
    return signal;
}

std::vector<double> generate_cosine(double amplitude, double frequency, double duration, int sample_rate) {
    int total_samples = static_cast<int>(duration * sample_rate);
    std::vector<double> signal(total_samples);
    for (int i = 0; i < total_samples; ++i) {
        double t = static_cast<double>(i) / sample_rate;
        signal[i] = amplitude * std::cos(2 * M_PI * frequency * t);
    }
    return signal;
}

std::vector<double> generate_square(double amplitude, double frequency, double duration, int sample_rate) {
    int total_samples = static_cast<int>(duration * sample_rate);
    std::vector<double> signal(total_samples);
    for (int i = 0; i < total_samples; ++i) {
        double t = static_cast<double>(i) / sample_rate;
        signal[i] = amplitude * (std::sin(2 * M_PI * frequency * t) >= 0 ? 1.0 : -1.0);
    }
    return signal;
}

std::vector<double> generate_sawtooth(double amplitude, double frequency, double duration, int sample_rate) {
    int total_samples = static_cast<int>(duration * sample_rate);
    std::vector<double> signal(total_samples);
    for (int i = 0; i < total_samples; ++i) {
        double t = static_cast<double>(i) / sample_rate;
        signal[i] = amplitude * (2 * fmod(frequency * t, 1.0) - 1);
    }
    return signal;
}

std::vector<std::complex<double>> dft(const std::vector<double>& x) {
    int n = x.size();
    std::vector<std::complex<double>> result(n);
    for (int k = 0; k < n; ++k) {
        std::complex<double> sum(0.0, 0.0);
        for (int j = 0; j < n; ++j) {
            double angle = 2.0 * M_PI * k * j / n;
            std::complex<double> term(x[j] * std::cos(angle), -x[j] * std::sin(angle));
            sum += term;
        }
        result[k] = sum;
    }
    return result;
}

std::vector<double> idft(const std::vector<std::complex<double>>& spectrum) {
    int n = spectrum.size();
    std::vector<double> result(n);
    for (int k = 0; k < n; ++k) {
        std::complex<double> sum(0.0, 0.0);
        for (int j = 0; j < n; ++j) {
            double angle = 2.0 * M_PI * k * j / n;
            std::complex<double> term(std::cos(angle), std::sin(angle));
            sum += spectrum[j] * term;
        }
        result[k] = std::real(sum) / n;
    }
    return result;
}