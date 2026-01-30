// Video bellek adresi
char* const VGA_MEMORY = (char*)0xB8000;

// Ekrana yazı yazma fonksiyonu
void print_at(const char* str, int row, int col, char color) {
    int offset = (row * 80 + col) * 2;
    for (int i = 0; str[i] != '\0'; i++) {
        VGA_MEMORY[offset] = str[i];
        VGA_MEMORY[offset + 1] = color;
        offset += 2;
    }
}

// Donanım portundan veri okuma (Assembly köprüsü)
unsigned char inb(unsigned short port) {
    unsigned char result;
    __asm__ volatile("inb %1, %0" : "=a"(result) : "Nd"(port));
    return result;
}

// Türk Bayrağı Çizimi
void draw_milli_bayrak(int r, int c) {
    // 1. Kırmızı Zemin Çizimi
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 18; j++) {
            int offset = ((r + i) * 80 + (c + j)) * 2;
            VGA_MEMORY[offset] = ' ';
            VGA_MEMORY[offset + 1] = 0x44; // Parlak Kırmızı
        }
    }
    // 2. Ay ve Yıldız Sembolleri (Beyaz karakterlerle simüle ediyoruz)
    print_at(" ( ", r + 3, c + 3, 0x4F); // Beyaz Ay
    print_at(" * ", r + 4, c + 9, 0x4F); // Beyaz Yıldız
}

// Klavye Dinleyici
void check_keyboard() {
    // 0x64 portu klavye durumunu kontrol eder
    if (inb(0x64) & 0x01) {
        unsigned char scancode = inb(0x60); // 0x60 portu basılan tuşu verir
        
        if (scancode == 0x01) { // ESC tuşu
            print_at(" ESC BASILDI!   ", 20, 30, 0x0C);
        }
        else if (scancode == 0x1C) { // Enter tuşu
            print_at(" ENTER BASILDI! ", 20, 30, 0x0B);
        }
        else if (scancode == 0x39) { // Boşluk (Space) tuşu
            print_at(" SPACE BASILDI! ", 20, 30, 0x0E);
        }
    }
}

extern "C" void kmain() {
    // Ekranı temizle
    for (int i = 0; i < 80 * 25 * 2; i += 2) {
        VGA_MEMORY[i] = ' ';
        VGA_MEMORY[i+1] = 0x07;
    }

    // Görselleri çiz
    draw_milli_bayrak(5, 5);
    
    // Bilgileri yaz
    print_at("OSUMA MILLI KERNEL v1.0.2", 2, 25, 0x0E);
    print_at("Klavye Testi: ESC, ENTER veya SPACE bas!", 18, 20, 0x07);
    print_at("Sistem Durumu: DINLEMEDE...", 22, 1, 0x0A);

    // Ana Döngü (Sürekli klavyeyi kontrol eder)
    while(1) {
        check_keyboard();
    }
}