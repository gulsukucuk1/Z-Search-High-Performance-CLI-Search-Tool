# Z-Search: High-Performance CLI Search Tool

Z-Search, modern C++20 standartları ve Windows çekirdek seviyesi optimizasyonları kullanılarak geliştirilmiş, **ripgrep (rg)** performansına meydan okuyan yüksek performanslı bir komut satırı arama aracıdır.

## 🚀 Öne Çıkan Teknik Özellikler

* **Zero-Copy I/O (mmap):** Dosyalar RAM'e kopyalanmaz. Windows `CreateFileMapping` ve `MapViewOfFile` API'leri ile doğrudan işlemcinin adres alanına haritalanır.
* **C++20 Parallel Execution:** `std::execution::par` mimarisi kullanılarak işlemcinin tüm çekirdekleri (Work-Stealing Scheduler) %100 verimle çalıştırılır.
* **Case-Insensitive SIMD Search:** `std::string_view` ve optimize `std::search` algoritmalarıyla büyük/küçük harf duyarsız aramalar bellek kopyalaması yapılmadan jet hızında gerçekleştirilir.

## 💻 Kurulum ve Derleme (Windows)

Projenin başarıyla derlenebilmesi için **Visual Studio 2022** üzerinde şu ayarların yapılması gerekmektedir:
1. Proje Özellikleri -> C/C++ -> Dil (Language) -> **C++ Dil Standardı: ISO C++20 Standard (/std:c++20)**
2. Proje Özellikleri -> C/C++ -> Genel -> **Ek İçerme Dizinleri (Additional Include Directories):** `$(ProjectDir)include`
3. Derleme modunu **Release** ve mimariyi **x64** olarak seçerek `Ctrl + Shift + B` ile derleyin.

## 🛠️ Kullanım Komutları

Derlenen `Z-Search.exe` dosyasını terminal (CMD veya PowerShell) üzerinden şu parametrelerle çalıştırabilirsiniz:

```bash
# Genel Kullanım Formatı:
Z-Search.exe "<Aranacak_Klasör_Yolu>" "<Aranacak_Kelime>"

# Örnek 1: Masaüstünde harf duyarsız arama yapma
Z-Search.exe "C:\Users\Gülsu\Desktop" "gulsu"

# Örnek 2: Proje klasöründe "include" kelimesini aratma
Z-Search.exe "C:\Users\Gülsu\Desktop\Z-Search" "include"
