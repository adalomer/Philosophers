Dining Philosophers Problem" (Yemek Yiyen Filozoflar Problemi), bilgisayar bilimlerinde klasik bir senkronizasyon problemidir. Bu problemde, bir grup filozof bir masada oturur ve her filozofun önünde bir çatal bulunur. Filozoflar yemek yemek, düşünmek ve uyumak gibi eylemler gerçekleştirir. Ancak, bir filozofun yemek yiyebilmesi için hem solundaki hem de sağındaki çatalı alması gerekir. Bu durum, kaynak paylaşımı ve senkronizasyon sorunlarına yol açar.

Problem Tanımı ve Terimler
Filozof (Philosopher):

Her filozof bir iş parçacığı (thread) olarak temsil edilir.

Filozoflar yemek yemek, düşünmek ve uyumak gibi eylemler gerçekleştirir.

Çatal (Fork):

Her çatal bir mutex (kilit) olarak temsil edilir.

Bir filozofun yemek yiyebilmesi için hem solundaki hem de sağındaki çatalı alması gerekir.

Senkronizasyon:

Birden fazla filozofun aynı anda aynı çatalı almasını engellemek için mutex kilitleri kullanılır.

Deadlock (Kilitlenme):

Tüm filozoflar aynı anda sol çatalı alırsa, sağ çatalı alamazlar ve hepsi sonsuza kadar bekler. Bu duruma deadlock denir.

Starvation (Açlık):

Bazı filozoflar sürekli olarak çatal alamaz ve yemek yiyemez. Bu duruma starvation denir.

Kodun İşleyişi
Başlangıç:

Her filozof bir thread olarak başlatılır ve philosopher_routine fonksiyonunu çalıştırır.

Çatal Alma:

Filozof önce solundaki çatalı alır (pthread_mutex_lock(&data->forks[philo->id]);).

Daha sonra sağındaki çatalı alır (pthread_mutex_lock(&data->forks[(philo->id + 1) % data->num_philos]);).

Yemek Yeme:

Filozof yemek yediğini belirtir (printf(...)).

Belirli bir süre boyunca yemek yer (ft_usleep(data->time_to_eat);).

Yemek yeme sayısını artırır (philo->meals_eaten++;).

Çatal Bırakma:

Filozof yemek yedikten sonra çatalları bırakır (pthread_mutex_unlock(...)).

Uyuma ve Düşünme:

Filozof uyuduğunu ve düşündüğünü belirtir (printf(...)).

Belirli bir süre boyunca uyur ve düşünür (ft_usleep(data->time_to_sleep);).

Kontrol Edilmesi Gereken Noktalar
Deadlock (Kilitlenme):

Tüm filozoflar aynı anda sol çatalı alırsa, sağ çatalı alamazlar ve hepsi sonsuza kadar bekler.

Çözüm: Filozoflardan bazılarının önce sağ çatalı almasını sağlamak veya zaman aşımı mekanizmaları kullanmak.

Starvation (Açlık):

Bazı filozoflar sürekli olarak çatal alamaz ve yemek yiyemez.

Çözüm: Adil bir çatal dağıtım mekanizması kullanmak veya öncelikli erişim sağlamak.

Senkronizasyon:

Birden fazla filozofun aynı anda aynı çatalı almasını engellemek için mutex kilitleri kullanılır.

Çözüm: Mutex kilitlerini doğru bir şekilde kullanmak ve kilitlenmeleri önlemek.

Performans:

Çok sayıda filozof ve çatal olduğunda, senkronizasyon mekanizmaları performansı etkileyebilir.

Çözüm: Daha verimli senkronizasyon mekanizmaları kullanmak veya paralel işleme tekniklerini uygulamak.

Alınması Gereken Aksiyonlar
Deadlock Önleme:

Filozoflardan bazılarının önce sağ çatalı almasını sağlamak.

Zaman aşımı mekanizmaları kullanmak.

Starvation Önleme:

Adil bir çatal dağıtım mekanizması kullanmak.

Öncelikli erişim sağlamak.

Senkronizasyon:

Mutex kilitlerini doğru bir şekilde kullanmak.

Kilitlenmeleri önlemek için ekstra kontroller eklemek.

Performans Optimizasyonu:

Daha verimli senkronizasyon mekanizmaları kullanmak.

Paralel işleme tekniklerini uygulamak.
