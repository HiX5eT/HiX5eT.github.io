#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib> 
#include <ctime>  

struct IzNoktasi {
    sf::Vector2f pozisyon;
    float opaklik;
};

int main() {
    std::srand(static_cast<unsigned>(std::time(0)));

    sf::RenderWindow pencere(sf::VideoMode({800, 600}), "HiX5eT - Altin Toplama Oyunu");
    pencere.setFramerateLimit(60);

    sf::RectangleShape oyuncu({50.f, 50.f});
    oyuncu.setFillColor(sf::Color::Green);
    oyuncu.setPosition({375.f, 275.f});

    // --- ALTINLAR ---
    std::vector<sf::RectangleShape> altinlar;
    for (int i = 0; i < 5; ++i) {
        sf::RectangleShape altin({20.f, 20.f});
        altin.setFillColor(sf::Color::Yellow);
        altin.setPosition({(float)(std::rand() % 780), (float)(std::rand() % 580)});
        altinlar.push_back(altin);
    }

    std::vector<IzNoktasi> izListesi;
    float izBirikmeSayaci = 0.f;
    sf::Vector2f hiz(0.f, 0.f);
    float maksimumHiz = 450.f, ivmelenme = 2500.f, surtunme = 2000.f;
    sf::Clock saat;

    while (pencere.isOpen()) {
        float dt = saat.restart().asSeconds();
        
        // --- OLAYLAR ---
        while (const std::optional olay = pencere.pollEvent()) {
            if (olay->is<sf::Event::Closed>()) pencere.close();
        }

        // --- HAREKET ---
        sf::Vector2f girdiYonu(0.f, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) girdiYonu.y -= 1.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) girdiYonu.y += 1.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) girdiYonu.x -= 1.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) girdiYonu.x += 1.f;

        if (girdiYonu.x != 0.f || girdiYonu.y != 0.f) {
            float uzunluk = std::sqrt(girdiYonu.x * girdiYonu.x + girdiYonu.y * girdiYonu.y);
            girdiYonu /= uzunluk;
            hiz += girdiYonu * ivmelenme * dt;
        } else {
            // Surtunme
            if (std::abs(hiz.x) > 0.f) hiz.x -= (hiz.x > 0 ? 1 : -1) * surtunme * dt;
            if (std::abs(hiz.y) > 0.f) hiz.y -= (hiz.y > 0 ? 1 : -1) * surtunme * dt;
            if (std::abs(hiz.x) < 10.f) hiz.x = 0.f;
            if (std::abs(hiz.y) < 10.f) hiz.y = 0.f;
        }
        
        // Hız limiti
        float hizUzunluk = std::sqrt(hiz.x * hiz.x + hiz.y * hiz.y);
        if (hizUzunluk > maksimumHiz) hiz = (hiz / hizUzunluk) * maksimumHiz;
        oyuncu.move(hiz * dt);

        // --- ALTIN ÇARPIŞMA ---
        for (auto it = altinlar.begin(); it != altinlar.end();) {
            if (oyuncu.getGlobalBounds().findIntersection(it->getGlobalBounds())) {
                it = altinlar.erase(it);
                std::cout << "Altin toplandi! Kalan: " << altinlar.size() << std::endl;
                // Yeni altın ekle
                sf::RectangleShape yeniAltin({20.f, 20.f});
                yeniAltin.setFillColor(sf::Color::Yellow);
                yeniAltin.setPosition({(float)(std::rand() % 780), (float)(std::rand() % 580)});
                altinlar.push_back(yeniAltin);
            } else {
                ++it;
            }
        }

        // --- ÇİZİM ---
        pencere.clear(sf::Color::Black);
        for (const auto &altin : altinlar) pencere.draw(altin);
        pencere.draw(oyuncu);
        pencere.display();
    }
    return 0;
}
