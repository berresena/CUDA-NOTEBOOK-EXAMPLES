# CUDA-NOTEBOOK-EXAMPLES
MSc GPU Programming Lesson Notes and Codebook
--------------------------------------------------------------------------------------
*Compare And Swap*

## Senaryo 1: Önce Thread 1, Sonra Thread 2 Çalışırsa
* **Başlangıç:** a = 10
* **Thread 1:** 10 ekleyecek
  * Bellekteki değer: 10
  * Beklenen değer: 10
  * Yeni değer: 20
  * İşlem sonrası bellek: 20
  * Dönen değer: 10
* **Thread 2:** 15 ekleyecek
  * Bellekteki değer: 20
  * Beklenen değer: 20
  * Yeni değer: 35
  * İşlem sonrası bellek: 35
  * Dönen değer: 20

### İşlem Tablosu
| Bellekteki değer | Beklenen değer | Yeni değer | İşlem sonrası bellek | Dönen değer |
| :---: | :---: | :---: | :---: | :---: |
| 10 | 10 | 20 | 20 | 10 |
| 20 | 20 | 35 | 35 | 20 |

**Sonuç:** `a = 35`

---

## Senaryo 2: Önce Thread 2, Sonra Thread 1 Çalışırsa
* **Başlangıç:** a = 10
* **Thread 2:** 15 ekleyecek
  * Bellekteki değer: 10
  * Beklenen değer: 10
  * Yeni değer: 25
  * İşlem sonrası bellek: 25
  * Dönen değer: 10
* **Thread 1:** 10 ekleyecek
  * Bellekteki değer: 25
  * Beklenen değer: 25
  * Yeni değer: 35
  * İşlem sonrası bellek: 35
  * Dönen değer: 25

### İşlem Tablosu
| Bellekteki değer | Beklenen değer | Yeni değer | İşlem sonrası bellek | Dönen değer |
| :---: | :---: | :---: | :---: | :---: |
| 10 | 10 | 25 | 25 | 10 |
| 25 | 25 | 35 | 35 | 25 |

**Sonuç:** `a = 35`

---
kodda thread'leri özellikle `join()` ile sırayla beklettiğimiz için; işletim sisteminin rastgele thread planlaması (race condition) engellenmiş olur. Ana thread, birinci thread'in işini tamamen bitirmesini bekler ve ardından diğerini başlatır. Bu sayede programın çıktısı her çalıştırmada deterministik (öngörülebilir) bir şekilde aynı sırayla gerçekleşir.

