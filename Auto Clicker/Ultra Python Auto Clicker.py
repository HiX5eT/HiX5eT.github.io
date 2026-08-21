import tkinter as tk
from tkinter import ttk
import threading
import time
import pyautogui
from pynput import keyboard
import os
from PIL import Image, ImageTk


class UltraAutoClickerGUI:
    def __init__(self, root):
        self.root = root
        self.root.title("Ultra Python Auto Clicker v1.4")
        self.root.geometry("350x320")
        self.root.resizable(False, False)

        # --- PENCERE İKONU EKLEME ---
        # Program çalışınca sol üstte ve görev çubuğunda logonun görünmesini sağlar
        if os.path.exists("logo.ico"):
            try:
                self.root.iconbitmap("logo.ico")
            except Exception:
                pass  # İkon yüklenemezse programın çökmesini engeller

        self.tıklama_durumu = False
        self.baslat_tusu = 's'

        self.arayuz_olustur()
        self.arka_plan_islemlerini_baslat()

    def arayuz_olustur(self):
        # --- JPG ARKA PLAN RESMİ ---
        if os.path.exists("arkaplan.jpg"):
            try:
                pil_resim = Image.open("arkaplan.jpg")
                pil_resim = pil_resim.resize((350, 320), Image.Resampling.LANCZOS)
                self.bg_resim = ImageTk.PhotoImage(pil_resim)
                bg_label = tk.Label(self.root, image=self.bg_resim)
                bg_label.place(x=0, y=0, relwidth=1, relheight=1)
            except Exception as e:
                self.root.configure(bg="#2c3e50")
        else:
            self.root.configure(bg="#2c3e50")

        # --- ARAYÜZ ELEMANLARI ---
        baslik = tk.Label(self.root, text="ULTRA PYTHON AUTO CLICKER", font=("Helvetica", 13, "bold"), fg="#ecf0f1",
                          bg="#1a252f")
        baslik.pack(pady=15)

        # 1. Kısım: Tıklama Hızı
        hiz_frame = tk.Frame(self.root, bg="#1a252f")
        hiz_frame.pack(pady=5)

        hiz_label = tk.Label(hiz_frame, text="Tıklama Aralığı (MS):", font=("Helvetica", 10), fg="#ecf0f1",
                             bg="#1a252f")
        hiz_label.pack(side=tk.LEFT, padx=5)

        self.hiz_entry = tk.Entry(hiz_frame, width=8, font=("Helvetica", 10), justify="center")
        self.hiz_entry.insert(0, "100")
        self.hiz_entry.pack(side=tk.LEFT, padx=5)

        # 2. Kısım: Kısayol Tuşu Değiştirme
        tus_frame = tk.Frame(self.root, bg="#1a252f")
        tus_frame.pack(pady=10)

        tus_label = tk.Label(tus_frame, text="Kısayol Tuşu Değiştir:", font=("Helvetica", 10), fg="#ecf0f1",
                             bg="#1a252f")
        tus_label.pack(side=tk.LEFT, padx=5)

        self.tus_entry = tk.Entry(tus_frame, width=5, font=("Helvetica", 10, "bold"), justify="center")
        self.tus_entry.insert(0, self.baslat_tusu.upper())
        self.tus_entry.pack(side=tk.LEFT, padx=5)

        guncelle_btn = tk.Button(tus_frame, text="Ayarla", command=self.tusu_guncelle, font=("Helvetica", 9),
                                 bg="#3498db", fg="white", bd=0, padx=5)
        guncelle_btn.pack(side=tk.LEFT, padx=5)

        # Bilgilendirme Alanı
        self.bilgi_label = tk.Label(self.root, text=f"Şu anki Kısayol: '{self.baslat_tusu.upper()}'",
                                    font=("Helvetica", 11, "bold"), fg="#e74c3c", bg="#1a252f")
        self.bilgi_label.pack(pady=10)

        # Dinamik Durum Çubuğu
        self.durum_label = tk.Label(self.root, text="Durum: DURDURULDU", font=("Helvetica", 10, "bold"), fg="#bdc3c7",
                                    bg="#34495e", width=30, height=2)
        self.durum_label.pack(pady=10)

    def tusu_guncelle(self):
        yeni_tus = self.tus_entry.get().strip().lower()
        if len(yeni_tus) == 1:
            self.baslat_tusu = yeni_tus
            self.bilgi_label.config(text=f"Şu anki Kısayol: '{yeni_tus.upper()}'", fg="#e74c3c")
            self.tus_entry.delete(0, tk.END)
            self.tus_entry.insert(0, yeni_tus.upper())
        else:
            self.bilgi_label.config(text="HATA: Tek bir harf girin!", fg="#f1c40f")

    def clicker_dongusu(self):
        while True:
            if self.tıklama_durumu:
                try:
                    ms = float(self.hiz_entry.get()) / 1000.0
                except ValueError:
                    ms = 0.1

                pyautogui.click()
                time.sleep(ms)
            else:
                time.sleep(0.1)

    def tus_dinleyici(self, tus):
        try:
            if hasattr(tus, 'char') and tus.char == self.baslat_tusu:
                self.tıklama_durumu = not self.tıklama_durumu
                if self.tıklama_durumu:
                    self.durum_label.config(text="Durum: AKTİF (Tıklanıyor...)", fg="#2ecc71")
                else:
                    self.durum_label.config(text="Durum: DURDURULDU", fg="#bdc3c7")
        except Exception as e:
            pass

    def arka_plan_islemlerini_baslat(self):
        click_thread = threading.Thread(target=self.clicker_dongusu, daemon=True)
        click_thread.start()

        klavye_thread = keyboard.Listener(on_press=self.tus_dinleyici)
        klavye_thread.start()


if __name__ == "__main__":
    root = tk.Tk()
    app = UltraAutoClickerGUI(root)
    root.mainloop() 
#NOT:logo ve kütüphaneleri manuel eklemeniz gerekir
