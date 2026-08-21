#include <windows.h>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

// Grafik kütüphanesini garantiye alıyoruz
#pragma comment(lib, "gdi32.lib")

#define BTN_EKLE 1
#define BTN_SEC 2
#define LST_OYUNLAR 3

HWND hEdit, hListBox, hLabel, hBtnEkle, hBtnSec;
HFONT hFont; 
std::vector<std::wstring> oyunListesi;

// Pencerenin arkasına gradyan çizen sihirli fonksiyonumuz
void GradyanCiz(HDC hdc, RECT rect) {
    // Üst renk (Mor/Magenta): RGB(128, 0, 128)
    // Alt renk (Gece Mavisi/Neon Koyu Mavi): RGB(15, 32, 67)
    int r1 = 128, g1 = 0, b1 = 128;
    int r2 = 15, g2 = 32, b2 = 67;

    int yukseklik = rect.bottom - rect.top;

    for (int i = 0; i < yukseklik; i++) {
        // Renkler arasında satır satır geçiş hesaplıyoruz
        int r = r1 + (r2 - r1) * i / yukseklik;
        int g = g1 + (g2 - g1) * i / yukseklik;
        int b = b1 + (b2 - b1) * i / yukseklik;

        HPEN hPen = CreatePen(PS_SOLID, 1, RGB(r, g, b));
        HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

        MoveToEx(hdc, rect.left, i, NULL);
        LineTo(hdc, rect.right, i);

        SelectObject(hdc, hOldPen);
        DeleteObject(hPen);
    }
}

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
        case WM_CREATE: {
            srand(static_cast<unsigned int>(time(0)));

            // Modern fontumuz (Roboto)
            hFont = CreateFontW(
                20, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, 
                DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
                DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Butcher"
            );

            // Yazı rengi arka planda sırıtmasın diye transparan (saydam) yapıyoruz
            hLabel = CreateWindowW(L"Static", L"Oyun Adini Yaz:", WS_VISIBLE | WS_CHILD, 20, 20, 150, 20, hWnd, NULL, NULL, NULL);
            SendMessageW(hLabel, WM_SETFONT, (WPARAM)hFont, TRUE);

            hEdit = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 20, 45, 200, 25, hWnd, NULL, NULL, NULL);
            SendMessageW(hEdit, WM_SETFONT, (WPARAM)hFont, TRUE);

            hBtnEkle = CreateWindowW(L"Button", L"Ekle", WS_VISIBLE | WS_CHILD, 230, 45, 110, 25, hWnd, (HMENU)BTN_EKLE, NULL, NULL);
            SendMessageW(hBtnEkle, WM_SETFONT, (WPARAM)hFont, TRUE);

            hListBox = CreateWindowW(L"ListBox", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | WS_VSCROLL, 20, 90, 320, 150, hWnd, (HMENU)LST_OYUNLAR, NULL, NULL);
            SendMessageW(hListBox, WM_SETFONT, (WPARAM)hFont, TRUE);

            hBtnSec = CreateWindowW(L"Button", L"Oyun Sec!", WS_VISIBLE | WS_CHILD, 20, 260, 320, 45, hWnd, (HMENU)BTN_SEC, NULL, NULL);
            SendMessageW(hBtnSec, WM_SETFONT, (WPARAM)hFont, TRUE);
            break;
        }

        // Yazıların (Label) arkasındaki gri kutuyu yok edip gradyanla uyumlu yapmak için
        case WM_CTLCOLORSTATIC: {
            HDC hdcStatic = (HDC)wp;
            SetTextColor(hdcStatic, RGB(255, 255, 255)); // Yazıyı beyaz yapıyoruz
            SetBkMode(hdcStatic, TRANSPARENT); // Arkasını saydam yapıyoruz
            return (INT_PTR)GetStockObject(NULL_BRUSH);
        }

        // Pencere her açıldığında veya boyutu değiştiğinde gradyanı burası çizer
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            RECT rect;
            GetClientRect(hWnd, &rect);
            GradyanCiz(hdc, rect); // Gradyan fonksiyonumuzu çağırıyoruz
            EndPaint(hWnd, &ps);
            break;
        }

        // Pencere büyütülüp küçültüldüğünde renk bozulmasın diye ekranı tazeliyoruz
        case WM_SIZE:
            InvalidateRect(hWnd, NULL, TRUE);
            break;

        case WM_COMMAND: {
            if (LOWORD(wp) == BTN_EKLE) {
                wchar_t buffer[256];
                GetWindowTextW(hEdit, buffer, 256);
                std::wstring oyunAdi(buffer);

                if (!oyunAdi.empty()) {
                    oyunListesi.push_back(oyunAdi);
                    SendMessageW(hListBox, LB_ADDSTRING, 0, (LPARAM)buffer);
                    SetWindowTextW(hEdit, L"");
                    SetFocus(hEdit);
                }
            }
            else if (LOWORD(wp) == BTN_SEC) {
                if (oyunListesi.empty()) {
                    MessageBoxW(hWnd, L"Once listeye birkac oyun eklemelisin Emre!", L"Liste Bos", MB_OK | MB_ICONWARNING);
                } else {
                    int rastgeleIndeks = rand() % oyunListesi.size();
                    std::wstring secilenOyun = oyunListesi[rastgeleIndeks];

                    std::wstring mesaj = L"Bilgisayar senin icin secti:\n\n" + secilenOyun + L"\n\nSimdiden iyi oyunlar gamer!";
                    MessageBoxW(hWnd, mesaj.c_str(), L"Sansli Oyun Belirlendi!", MB_OK | MB_ICONINFORMATION);
                }
            }
            break;
        }

        case WM_DESTROY:
            DeleteObject(hFont);
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProcW(hWnd, msg, wp, lp);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {
    (void)hPrevInst; (void)args; (void)ncmdshow;

    WNDCLASSW wc = {0};
    wc.hbrBackground = NULL; // Arka planı boş bırakıyoruz ki gradyanımız üzerine çizilsin
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance = hInst;
    wc.lpszClassName = L"OyunSeciciClass";
    wc.lpfnWndProc = WindowProcedure;

    if (!RegisterClassW(&wc)) return -1;

    CreateWindowW(L"OyunSeciciClass", L"Emre TV - Neon Gamer Oyun Secici V2.0", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 380, 380, NULL, NULL, hInst, NULL);

    MSG msg = {0};
    while (GetMessageW(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    return 0;
}
