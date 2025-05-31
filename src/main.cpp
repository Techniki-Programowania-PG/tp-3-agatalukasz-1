#include "signal.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib> 
#include <string>
#include <map>
#include <complex>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Uzycie: " << argv[0] << " <sin|cos|square|sawtooth>" << std::endl;
        return 1;
    }

    std::string signal_type = argv[1];
    double amplitude = 1.0;
    double frequency = 1.0;
    double duration = 5.0;
    int sample_rate = 100;
    std::vector<double> signal;
    std::string title;
    std::string title_freq = "Amplituda Widma DFT";
    std::string title_idft = "Sygnal po IDFT";

    if (signal_type == "sin") {
        signal = generate_sine(amplitude, frequency, duration, sample_rate);
        title = "Sygnal Sinusoidalny";
    }
    else if (signal_type == "cos") {
        signal = generate_cosine(amplitude, frequency, duration, sample_rate);
        title = "Sygnal Cosinusoidalny";
    }
    else if (signal_type == "square") {
        signal = generate_square(amplitude, frequency, duration, sample_rate);
        title = "Sygnal Prostok¹tny";
    }
    else if (signal_type == "sawtooth") {
        signal = generate_sawtooth(amplitude, frequency, duration, sample_rate);
        title = "Sygnal Piloksztaltny";
    }
    else {
        std::cerr << "Nieznany typ sygnalu: " << signal_type << std::endl;
        std::cerr << "Dostepne opcje: sin, cos, square, sawtooth" << std::endl;
        return 1;
    }

    // Zapisanie danych
    std::ofstream data_file("signal_data.txt");
    if (data_file.is_open()) {
        for (size_t i = 0; i < signal.size(); ++i) {
            double t = static_cast<double>(i) / sample_rate;
            data_file << t << " " << signal[i] << std::endl;
        }
        data_file.close();
        std::cout << "Dane zapisano do signal_data.txt" << std::endl;
    }
    else {
        std::cerr << "Nie mozna otworzyc pliku do zapisu." << std::endl;
        return 1;
    }

    // Wywolanie gnuplot
    std::string gnuplot_command = "gnuplot -p -e \"plot 'signal_data.txt' with lines title '" + title + "'\"";
    int result = system(gnuplot_command.c_str());
    if (result == 0) {
        std::cout << "Wywolano Gnuplot." << std::endl;
    }
    else {
        std::cerr << "Problem z wywolaniem Gnuplot." << std::endl;
    }

    // Oblicz DFT
    std::vector<std::complex<double>> spectrum = dft(signal);

    // Zapisz amplitude widma do pliku
    std::ofstream spectrum_file("dft_spectrum.txt");
    if (spectrum_file.is_open()) {
        for (size_t k = 0; k < spectrum.size(); ++k) {
            double magnitude = std::abs(spectrum[k]);
            double freq = static_cast<double>(k) * sample_rate / spectrum.size(); // Przyblizona czestotliwosc
            spectrum_file << freq << " " << magnitude << std::endl;
        }
        spectrum_file.close();
        std::cout << "Amplituda widma DFT zapisana do dft_spectrum.txt" << std::endl;
    }
    else {
        std::cerr << "Nie mozna otworzyc pliku dft_spectrum.txt do zapisu." << std::endl;
        return 1;
    }

    // Wywolaj Gnuplot do narysowania amplitudy widma DFT
    std::string gnuplot_command_freq = "gnuplot -p -e \"plot 'dft_spectrum.txt' with lines title '" + title_freq + "'\"";
    int result_freq = system(gnuplot_command_freq.c_str());
    if (result_freq != 0) {
        std::cerr << "Problem z wywolaniem Gnuplot do wizualizacji DFT." << std::endl;
    }

    // Oblicz IDFT
    std::vector<double> reconstructed_signal = idft(spectrum);

	// Zapisanie zrekponstruowanego sygnalu do pliku
    std::ofstream idft_file("idft_signal.txt");
    if (idft_file.is_open()) {
        for (size_t i = 0; i < reconstructed_signal.size(); ++i) {
            double t = static_cast<double>(i) / sample_rate;
            idft_file << t << " " << reconstructed_signal[i] << std::endl;
        }
        idft_file.close();
        std::cout << "Sygnal po IDFT zapisano do idft_signal.txt" << std::endl;
        std::string gnuplot_command_idft = "gnuplot -p -e \"plot 'idft_signal.txt' with lines title '" + title_idft + "'\"";
        int result_idft = system(gnuplot_command_idft.c_str());
        if (result_idft != 0) {
            std::cerr << "Problem z wywolaniem Gnuplot do wizualizacji IDFT." << std::endl;
        }
    }
    else {
        std::cerr << "Nie mozna otworzyc pliku idft_signal.txt do zapisu." << std::endl;
        return 1;
    }

    return 0;
}