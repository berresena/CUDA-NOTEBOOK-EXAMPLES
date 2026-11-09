#include <iostream>
#include <cstdio>
#include <thread>
using namespace std;

// Compare and Swap fonksiyonu
int compare_and_swap(int* regval, int oldval, int newval) {
    int old_reg_val = *regval;
    //printleri anlamak için yazdım. böylece tablo mantığı kuruldu.
    printf("CAS(Compare and Swap)\n");
    printf("Bellekteki mevcut deger: %d\n", old_reg_val);
    printf("Beklenen deger: %d\n", oldval);
    printf("Yeni deger: %d\n", newval);
    if (old_reg_val == oldval) {
        *regval = newval;
        printf("Degerler esit. Bellek guncellendi\n");
    }
    /*else { //BU KISMI YORUM SATIRINDAN ÇIKARABİLİRİZ AMA BELLEK DEĞERİ GÜNCELLENMEYİNCE ÇALIŞMASINA GEREK YOK.
        printf("Degerler esit degil. Bellek degismedi\n");
    }*/
    printf("Islem sonrasi bellek: %d\n", *regval);
    printf("Donen deger: %d\n", old_reg_val);

    return old_reg_val;
}

// Thread 1: a'ya 10 ekler
void thread1(int* a) {
    printf("\nTHREAD 1 CALISIYOR\n");
    int old = *a;
    compare_and_swap(a, old, old + 10);
}
// Thread 2: a'ya 15 ekler
void thread2(int* a) {
    printf("\nTHREAD 2 CALISIYOR\n");
    int old = *a;
    compare_and_swap(a, old, old + 15);
}

int main() {

    int a;

    // SENARYO 1
    printf("\nSENARYO 1 =\n");
    printf("Önce Thread 1, sonra Thread 2\n");
    a = 10;
    printf("Baslangic a = %d\n", a);
    thread t1(thread1, &a);
    t1.join();
    thread t2(thread2, &a);
    t2.join();
    printf("\nSenaryo 1 Sonuc: a = %d\n", a);

    // SENARYO 2
    printf("\nSENARYO 2\n");
    printf("Önce Thread 2, sonra Thread 1\n");
    a = 10;//başlangıç değerini atadık. Önceki senaryodan gelen değer böylece bu senaryoda kullanılmadı.
    printf("Baslangic a = %d\n", a);
    thread t3(thread2, &a);
    t3.join();//burada 3 ve 4 denmesinin sebebi aynı kodda üstte senaryo 1 için 1 ve 2 değerlerinin kullanılmış olması.
    thread t4(thread1, &a);
    t4.join();
    printf("\nSenaryo 2 Sonuc: a = %d\n", a);

    return 0;
}