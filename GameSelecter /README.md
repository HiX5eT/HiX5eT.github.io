# 🎮 C++ Oyun Seçici (Oyun Seçici CLI)

C++ dilinde geliştirilmiş; birden fazla oyun veya uygulama arasında hızlıca seçim yapmanızı, terminal üzerinden akıcı bir menüyle yönetmenizi sağlayan pratik bir komut satırı aracı (CLI).

## 🚀 Özellikler

- ⌨️ **Kolay Kullanım:** Terminal tabanlı, sade ve anlaşılır arayüz.
- ⚡ **Hızlı Başlangıç:** İstediğiniz oyunu veya uygulamayı tek tuşla hızlıca başlatma imkanı.
- 🧩 **Modüler Yapı:** Yeni oyunlar ve kısayollar kolayca eklenebilir.

## 🛠️ Kullanılan Teknolojiler

- **C++:** Yüksek performanslı konsol uygulaması mantığı ve standart kütüphaneler.

## 💻 Nasıl Derlenir ve Çalıştırılır?

Projeyi GCC/MinGW kullanarak derlerken dış bağımlılık (DLL hatası) yaşamamak için **statik bağlama** bayrağını kullanmanız önerilir:

```bash
g++ oyunsecici.cpp -o OyunSecici.exe -static
Derleme sonrasında oluşan çalıştırılabilir dosyayı doğrudan çalıştırabilirsiniz:

Bash
./OyunSecici.exe
⚠️ Not: Eğer derleme sırasında -static bayrağını kullanmazsanız ve libgcc_s_seh-1.dll bulunamadı hatası alırsanız, MinGW bin klasörünüzdeki ilgili .dll dosyasını .exe dosyasının yanına atarak veya yukarıdaki komutu -static ile tekrar derleyerek sorunu çözebilirsiniz.

Geliştiren: HıX5eT
