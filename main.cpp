#include "ImageProcessor.hpp"
#include "Opening.hpp"
#include <opencv2/highgui.hpp>
#include <string>
#include <iostream>
#include <ImageEntropy.hpp>
#include <Complement.hpp>
#include <Filling.hpp>
#include <Normalization.hpp>


using namespace std::string_literals;

void filling(){
    Image im{};
    std::string filepath;
    std::string filename;
    while(true) {
        std::cout << "4. Wypelnianie otworow za pomoca rekonstrukcji\n";
        std::cout << "Wczytaj obraz logiczny\nPodaj sciezke do pliku: ";
        std::cin >> filepath;
        std::cout << "\nPodaj nazwe pliku wyjsciowego: ";
        std::cin >> filename;
        im = Image::factory(filepath, filename).value_or(Image());
        if (im.getChannels() == 1) {
            break;
        }
    }

    Image out(im, filename);
    im.display();
    Filling::compute(out);
    out.display();
    out.save();
}

void opening(){
    Image im{};
    std::string filepath;
    std::string filename;
    size_t r;
    while(true) {
        std::cout << "3. Otwarcie kolowym elementem strukturalnym o zadanym promieniu\n";
        std::cout << "Wczytaj obraz logiczny lub monochromatyczny\nPodaj sciezke do pliku: ";
        std::cin >> filepath;
        std::cout << "Podaj nazwe pliku wyjsciowego: ";
        std::cin >> filename;
        std::cout << "Podaj promien otwarcia: ";
        std::cin >> r;
        im = Image::factory(filepath, filename).value_or(Image());
        if (im.getChannels() == 1) {
            break;
        }
    }

    Image out(im, filename);
    im.display();
    Opening o{r};
    o.compute(out);
    out.display();
    out.save();
}

void entropy(){
    Image im{};
    std::string filepath;
    std::string filename;
    size_t r;
    while(true) {
        std::cout << "\n2. Filtracja entropii w zadanym oknie\n";
        std::cout << "Wczytaj obraz kolorowy lub monochromatyczny\nPodaj sciezke do pliku: ";
        std::cin >> filepath;
        std::cout << "Podaj nazwe pliku wyjsciowego: ";
        std::cin >> filename;
        std::cout << "Podaj dlugosc boku okna: ";
        std::cin >> r;
        im = Image::factory(filepath, filename).value_or(Image());
        if (im.getWidth() != 0 && im.getHeight() != 0) {
            break;
        }
    }
    Image out(1, im.getWidth(), im.getHeight(), std::move(filename));
    im.display();
    ImageEntropy::compute(im, out, r);
    out.display();
    out.save();
}


void normalization(){
    Image im{};
    std::string filepath;
    std::string filename;
    Normalization::pointsContainer points{};
    std::cout << "\n1. Normalizacja względem minimum 3 punktow \n\n";
    std::cout << "Wczytaj obraz kolorowy lub monochromatyczny\nPodaj sciezke do pliku: ";
    std::cin >> filepath;
    std::cout << "Podaj nazwe pliku wyjsciowego: ";
    std::cin >> filename;
    const char ESC =27;
    char c;
    std::string line;
    bool stop = false;
    std::cout<<"Podaj wartosci wejsciowe i wyjsciowe 3 kolejnych punktow.  Wartosci z zakresu od 0 do 255 .\n";
    std::cin.ignore();
    while (!stop) {
        std::getline(std::cin, line);
        if (0 == line.length()) {
            stop = true;
            std::cout << "Pusta linia. koncze wczytywac\n";
            break;
        }
        char* line_endptr = nullptr;
        auto p1 = strtoul(line.c_str(), &line_endptr, 10);
        auto p2 = strtoul(line_endptr, nullptr, 10);
        points.emplace_back(p1, p2);
    }
    std::cout << "wczytano " << points.size() << " punktów\n";
    if(points.size() < 3) {
        std::cout << "przekazano za malo punktów. potrzeba przynajmniej 3\n";
        return;
    }


    im = Image::factory(filepath, filename).value_or(Image());
    if (im.getWidth() == 0 || im.getHeight() == 0) {
        std::cout << "nieprawidlowe wymiary obrazka\n";
        return ;
    }

    std::cout<<"Points:\n";
    for(auto& i : points){
        std::cout<<(int)i.first << " " << (int)i.second << "\n";
    }
    Image out(im, filename);
    im.display();
    std::sort(points.begin() , points.end());
    Normalization norm(points);
    norm.compute(out);
    out.display();
    out.save();
}


int main() {
    std::cout << "\t\t --- Przetwarzanie obrazow ---\n";
    std::cout << "Wybierz z dostepnych przeksztalcen: \n";
    std::cout << "\t1. Normalizacja względem minimum 3 punktow \n";
    std::cout << "\t2. Filtracja entropii w zadanym oknie\n";
    std::cout << "\t3. Otwarcie kolowym elementem strukturalnym o zadanym promieniu\n";
    std::cout << "\t4. Wypelnianie otworow za pomoca rekonstrukcji\n";


    enum operation{ NORM = 1, ENTROPY, OPEN, FILL} op;
    operation op1 = NORM;

    bool var = true;
    while(var) {
        std::cout<< "Podaj numer przeksztalcenia: ";
        std::cin >> reinterpret_cast<int&>(op);
        switch (op) {
            case NORM:
                normalization();
                var = false;
                break;
            case ENTROPY:
                entropy();
                var = false;
                break;
            case OPEN:
                opening();
                var = false;
                break;
            case FILL: {
                filling();
                var = false;
                break;
            }
            default:  std::cout << "Wybierz wartosc od 1 do 4\n";
        }
    }


    cv::waitKey(0);

    return 0;
}