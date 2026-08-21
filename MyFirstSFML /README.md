# 🟩 Hix5eT - SFML Coin Collector (Altın Toplama Prototipi)

C++ ve **SFML** kütüphanesi kullanılarak geliştirilmiş, akıcı bir momentum/fizik sistemine ve rastgele altın toplama mekaniğine sahip 2D oyun prototipi.

## 🚀 Özellikler
- **Gelişmiş Fizik Motoru:** İvmelenme, sürtünme ve maksimum hız sınırlamaları ile yumuşak hareket mekaniği.
- **İz Efekti (Trail Effect):** Oyuncunun hareket ederken arkasında bıraktığı dinamik kırmızı iz efekti.
- **Rastgele Altın Üretimi:** Ekran üzerinde rastgele konumlarda beliren altınlar ve toplandıkça yenilenen mekanik.
- **Sınır Kontrolleri:** Pencere duvarlarıyla etkileşim ve çarpışma yönetimi.

## 🛠️ Kullanılan Teknolojiler
- **C++** (C++17 standartları)
- **SFML** (Simple and Fast Multimedia Library - Graphics, Window, System modülleri)
- **VS Code & MSYS2 (UCRT64)**

## 📦 Kurulum ve Derleme

Projeyi yerel bilgisayarınızda derleyip çalıştırmak için şu adımları izleyebilirsiniz:

1. **Gereksinimler:** Sisteminizde MSYS2 UCRT64 ve SFML kütüphanesinin kurulu olduğundan emin olun.
2. **Kurulum Komutu:** Bu komutu MSYS2 UCRT64 terminalinde çalıştırarak kurulumu başlatabilirsiniz:
   ```bash
   pacman -Sy --needed --disable-download-timeout mingw-w64-ucrt-x86_64-toolchain mingw-w64-ucrt-x86_64-sfml
   ````

3. **Derleme Komutu:** Proje klasöründe terminali açarak şu komutu çalıştırın:
   ```bash
   g++ main.cpp -o oyun.exe -I/ucrt64/include -L/ucrt64/lib -lsfml-graphics -lsfml-window -lsfml-system -std=c++17


