# 🍝 Philosophers - Dining Philosophers Problem

<div align="center">

![42 Score](https://img.shields.io/badge/Score-100%2F100-success?style=for-the-badge&logo=42)
![Norminette](https://img.shields.io/badge/Norminette-passing-success?style=for-the-badge)
![Language](https://img.shields.io/badge/Language-C-blue?style=for-the-badge&logo=c)

*Edsger Dijkstra'nın ünlü "Yemek Yiyen Filozoflar Problemi"nin çözümü*

[Kurulum](#-kurulum) • [Kullanım](#-kullanım) • [Kavramlar](#-temel-kavramlar) • [Algoritmalar](#-çözüm-algoritması)

</div>

---

## 📖 Proje Hakkında

**Philosophers**, 42 okulunun en zorlu projelerinden biri olup, çoklu thread programlama, mutex'ler, ve race condition'lar gibi kritik sistem programlama konularını ele alır. 

### 🎯 Problemin Özeti

Yuvarlak bir masada N filozof oturmaktadır. Her filozofun önünde bir tabak spagetti ve iki çatal arasında bir çatal vardır. Filozoflar sadece üç şey yapar:

- 🍴 **Yemek yemek** (iki çatala birden ihtiyaç duyar)
- 💭 **Düşünmek** 
- 😴 **Uyumak**

**Amaç**: Hiçbir filozofun açlıktan ölmemesini sağlamak!

## ✨ Özellikler

### Mandatory Part
- ✅ Thread tabanlı çözüm (her filozof bir thread)
- ✅ Mutex ile senkronizasyon
- ✅ Data race koruması
- ✅ Deadlock önleme
- ✅ Gerçek zamanlı durum raporlama
- ✅ Hassas zamanlama (<10ms gecikme)

### Bonus Part
- ✅ Process tabanlı çözüm (her filozof bir process)
- ✅ Semaphore kullanımı
- ✅ Shared memory ile IPC

## 🚀 Kurulum

```bash
# Repository'yi klonlayın
git clone https://github.com/adalomer/Philosophers.git
cd Philosophers

# Derleyin
make

# Temizlik
make clean    # Object dosyalarını temizle
make fclean   # Tüm derlenmiş dosyaları temizle
make re       # Yeniden derle
```

## 💻 Kullanım

### Temel Kullanım

```bash
./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]
```

### Parametreler

| Parametre | Açıklama | Birim |
|-----------|----------|-------|
| `number_of_philosophers` | Filozof sayısı (ve çatal sayısı) | - |
| `time_to_die` | Bir yemek yemeden geçebilecek maksimum süre | ms |
| `time_to_eat` | Yemek yeme süresi | ms |
| `time_to_sleep` | Uyku süresi | ms |
| `number_of_times_each_philosopher_must_eat` | Her filozofun yemesi gereken minimum sayı (opsiyonel) | - |

### 📝 Örnekler

```bash
# 5 filozof, 800ms içinde ölüm, 200ms yemek, 200ms uyku
./philo 5 800 200 200

# Aynı senaryo, her filozof 7 kez yemeli
./philo 5 800 200 200 7

# Zor test: Tek filozof (ölmeli)
./philo 1 800 200 200

# Ölüm testi: Çok kısa süre
./philo 4 310 200 100

# Hız testi: Çok sayıda filozof
./philo 200 800 200 200
```

## 🎮 Çıktı Formatı

Her durum değişikliği şu formatta raporlanır:

```
[timestamp_in_ms] [philosopher_id] [action]
```

### Aksiyonlar

- 🍴 `has taken a fork` - Çatal aldı
- 🍝 `is eating` - Yemek yiyor
- 😴 `is sleeping` - Uyuyor
- 💭 `is thinking` - Düşünüyor
- 💀 `died` - Öldü

### Örnek Çıktı

```
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
200 1 is sleeping
0 3 has taken a fork
0 3 has taken a fork
0 3 is eating
400 1 is thinking
```

## 🧠 Temel Kavramlar

### Thread ve Mutex

Her filozof bir **thread** olarak temsil edilir ve kendi rutinini çalıştırır. Çatallar ise **mutex** kilitleri olarak implement edilir.

```c
pthread_mutex_t fork;
pthread_mutex_lock(&fork);    // Kilitle
// Kritik bölge
pthread_mutex_unlock(&fork);  // Kilidi aç
```

### Kritik Problemler

#### 1. 🔒 Deadlock (Kilitlenme)
Tüm filozoflar aynı anda sol çatalı alırsa, sağ çatalı alamazlar ve program kilitlenir.

**Çözüm**: Filozofların yarısı önce sol çatalı, diğer yarısı önce sağ çatalı alır.

```c
if (philo->id % 2 == 0) {
    pthread_mutex_lock(&data->forks[philo->id]);              // Sol çatal
    pthread_mutex_lock(&data->forks[(philo->id + 1) % n]);    // Sağ çatal
} else {
    pthread_mutex_lock(&data->forks[(philo->id + 1) % n]);    // Sağ çatal
    pthread_mutex_lock(&data->forks[philo->id]);              // Sol çatal
}
```

#### 2. 🍽️ Starvation (Açlık)
Bazı filozoflar sürekli çatal alamaz ve hiç yemek yiyemez.

**Çözüm**: Adil çatal dağıtımı ve öncelik mekanizması kullanılır.

#### 3. 🏃 Race Condition
Birden fazla thread'in aynı veriye aynı anda erişmesi.

**Çözüm**: Her paylaşımlı kaynak mutex ile korunur.

```c
pthread_mutex_lock(&philo->meal_lock);
philo->last_meal_time = get_current_time();
philo->meals_eaten++;
pthread_mutex_unlock(&philo->meal_lock);
```

## 🏗️ Proje Yapısı

```
Philosophers/
├── Makefile
├── README.md
├── philo.h               # Header dosyası
├── main.c                # Ana program
├── init.c                # Başlatma fonksiyonları
├── routine.c             # Filozof rutini
├── actions.c             # Yemek, uyku, düşünme
├── monitor.c             # Ölüm kontrolü
├── utils.c               # Yardımcı fonksiyonlar
└── time.c                # Zaman fonksiyonları
```

## 🔍 Algoritma Akışı

### 1. İnitialization Phase

```c
// Filozofları ve mutex'leri oluştur
init_philosophers(&data);
init_forks(&data);

// Her filozof için thread başlat
for (i = 0; i < data.num_philos; i++)
    pthread_create(&threads[i], NULL, philosopher_routine, &philos[i]);
```

### 2. Philosopher Routine

```c
void *philosopher_routine(void *arg) {
    t_philo *philo = (t_philo *)arg;
    
    while (!check_death(philo)) {
        think(philo);
        take_forks(philo);
        eat(philo);
        release_forks(philo);
        sleep_philo(philo);
    }
    return (NULL);
}
```

### 3. Çatal Alma Stratejisi

```c
void take_forks(t_philo *philo) {
    // Sol çatalı al
    pthread_mutex_lock(&data->forks[philo->id]);
    print_status(philo, "has taken a fork");
    
    // Sağ çatalı al
    pthread_mutex_lock(&data->forks[(philo->id + 1) % data->num_philos]);
    print_status(philo, "has taken a fork");
}
```

### 4. Yemek Yeme

```c
void eat(t_philo *philo) {
    print_status(philo, "is eating");
    
    pthread_mutex_lock(&philo->meal_lock);
    philo->last_meal_time = get_time();
    philo->meals_eaten++;
    pthread_mutex_unlock(&philo->meal_lock);
    
    ft_usleep(data->time_to_eat);
}
```

### 5. Death Monitor

```c
// Ana thread sürekli kontrol eder
while (simulation_running) {
    for (i = 0; i < num_philos; i++) {
        if (time_since_last_meal(&philos[i]) > time_to_die) {
            print_status(&philos[i], "died");
            stop_simulation();
            break;
        }
    }
}
```

## 🧪 Test Senaryoları

### Temel Testler

```bash
# ✅ Hiç kimse ölmemeli
./philo 5 800 200 200

# ✅ Hiç kimse ölmemeli
./philo 4 410 200 200

# ✅ Hiç kimse ölmemeli, 7 yemekten sonra dur
./philo 5 800 200 200 7
```

### Ölüm Testleri

```bash
# ❌ Filozof 2, ~310ms'de ölmeli
./philo 4 310 200 100

# ❌ Tek filozof, ~800ms'de ölmeli (çatal yetersiz)
./philo 1 800 200 200
```

### Stress Testler

```bash
# Çok sayıda filozof
./philo 200 800 200 200

# Çok hızlı döngü
./philo 4 410 200 100

# Uzun simülasyon
./philo 4 410 200 200 1000
```

### Helgrind (Data Race Testi)

```bash
valgrind --tool=helgrind ./philo 5 800 200 200
```

## 🐛 Debug İpuçları

### Yaygın Hatalar

1. **Data Race**
   ```c
   // ❌ YANLIŞ
   philosopher->last_meal = get_time();
   
   // ✅ DOĞRU
   pthread_mutex_lock(&philosopher->meal_lock);
   philosopher->last_meal = get_time();
   pthread_mutex_unlock(&philosopher->meal_lock);
   ```

2. **Usleep Hassasiyeti**
   ```c
   // ❌ YANLIŞ - usleep uzun süreler için hassas değil
   usleep(200 * 1000);  // 200ms
   
   // ✅ DOĞRU - hassas bekleme fonksiyonu
   void ft_usleep(long long time_in_ms) {
       long long start = get_time();
       while (get_time() - start < time_in_ms)
           usleep(100);
   }
   ```

3. **Timestamp Tutarlılığı**
   ```c
   // ✅ Program başından itibaren geçen süreyi kullan
   long long get_timestamp(t_data *data) {
       return (get_time() - data->start_time);
   }
   ```

## 📚 Kullanılan Fonksiyonlar

### Thread Yönetimi
- `pthread_create()` - Thread oluşturma
- `pthread_join()` - Thread bekleme
- `pthread_detach()` - Thread ayırma

### Mutex Yönetimi
- `pthread_mutex_init()` - Mutex başlatma
- `pthread_mutex_lock()` - Kilitleme
- `pthread_mutex_unlock()` - Kilidi açma
- `pthread_mutex_destroy()` - Mutex yok etme

### Zamanlama
- `gettimeofday()` - Zaman ölçümü
- `usleep()` - Microsaniye bekleme

## 📖 Kaynaklar

- [POSIX Threads Tutorial](https://www.cs.cmu.edu/afs/cs/academic/class/15492-f07/www/pthreads.html)
- [Dining Philosophers Problem - Wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- [Mutex vs Semaphore](https://www.geeksforgeeks.org/mutex-vs-semaphore/)
- [Race Conditions](https://en.wikipedia.org/wiki/Race_condition)

## 🎓 Öğrenilen Konular

- ✅ Multi-threading
- ✅ Mutex ve senkronizasyon
- ✅ Race condition yönetimi
- ✅ Deadlock önleme teknikleri
- ✅ Starvation çözümleri
- ✅ Hassas zamanlama
- ✅ Memory leaks önleme
- ✅ Thread-safe programlama

## 👤 Geliştirici

**Ömer Ali Adalı**  
42 İntra: `omadalı`  
GitHub: [@adalomer](https://github.com/adalomer)

## 📄 Lisans

Bu proje 42 Network'ün eğitim amaçlı bir projesidir.

---

<div align="center">

**⭐ Projeyi beğendiyseniz yıldız vermeyi unutmayın! ⭐**

*"I think, therefore I am... hungry"* - Philosopher #42

</div>
