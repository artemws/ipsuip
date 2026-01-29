# Документация проекта IPS UIP

## Введение

**IPS UIP** - это приложение на базе Qt6 для загрузки и обработки IP-адресов из базы данных [suip.biz](https://suip.biz). Приложение предоставляет удобный графический интерфейс для выбора стран и материков, с последующей загрузкой соответствующих IP-адресов и их сохранения в файл.

### Целевая аудитория

- **Разработчики**: Для интеграции функционала IP-адресов в свои проекты
- **DevOps-инженеры**: Для автоматизации сбора и обработки IP-адресов
- **Пользователи**: Для ручного выбора и загрузки IP-адресов по географическому признаку

---

## 1. Архитектурная схема проекта

### 1.1 Общая архитектура

```
┌─────────────────────────────────────────────────────────────────────┐
│                           IPS UIP                                  │
├─────────────────────────────────────────────────────────────────────┤
│  GUI Layer (Qt6/QML)                                              │
│  ┌─────────────────┐  ┌─────────────────┐  ┌─────────────────┐     │
│  │   MainWindow    │  │  Countries     │  │   Mainland      │     │
│  │   (QML)         │  │   (QML)        │  │   (QML)         │     │
│  └─────────────────┘  └─────────────────┘  └─────────────────┘     │
├─────────────────────────────────────────────────────────────────────┤
│  Controller Layer (C++)                                           │
│  ┌─────────────────────────────────────────────────────────────┐    │
│  │                 MainWindowController                       │    │
│  │  - Управление состоянием UI                                │    │
│  │  - Обработка событий пользователя                           │    │
│  │  - Взаимодействие с бизнес-логикой                       │    │
│  └─────────────────────────────────────────────────────────────┘    │
├─────────────────────────────────────────────────────────────────────┤
│  Business Logic Layer (C++)                                       │
│  ┌─────────────────┐  ┌─────────────────┐  ┌─────────────────┐     │
│  │   Functions    │  │HTTP Client      │  │Parallel Parsing │     │
│  │                │  │                 │  │                 │     │
│  │  - IP валидация │  │ - SSL запросы   │  │ - Многопоточная │     │
│  │  - Парсинг данных│  │ - suip.biz API  │  │   обработка    │     │
│  │  - Конвертация  │  │                 │  │                 │     │
│  └─────────────────┘  └─────────────────┘  └─────────────────┘     │
├─────────────────────────────────────────────────────────────────────┤
│  Data Layer (C++)                                                 │
│  ┌─────────────────┐  ┌─────────────────┐  ┌─────────────────┐     │
│  │   Data Models   │  │   Code Data    │  │   File I/O      │     │
│  │                │  │                 │  │                 │     │
│  │  - IP_a struct  │  │ - Коды стран    │  │ - Сохранение    │     │
│  │  - Enums        │  │ - Коды материков│  │   в файлы       │     │
│  │                 │  │                 │  │                 │     │
│  └─────────────────┘  └─────────────────┘  └─────────────────┘     │
├─────────────────────────────────────────────────────────────────────┤
│  External Services                                                │
│  ┌─────────────────────────────────────────────────────────────┐    │
│  │                     suip.biz API                          │    │
│  │  - REST API для получения IP-адресов                      │    │
│  │  - SSL/TLS шифрование                                    │    │
│  │  - Географическая фильтрация                              │    │
│  └─────────────────────────────────────────────────────────────┘    │
└─────────────────────────────────────────────────────────────────────┘
```

### 1.2 Ключевые компоненты

#### 1.2.1 GUI Layer (Qt6/QML)
- **MainWindow.qml**: Основное окно приложения с элементами управления
- **Countries.qml**: Диалог выбора стран
- **Mainland.qml**: Диалог выбора материков
- **CountriesDialog.qml**: Расширенный диалог выбора стран
- **MainlandsDialog.qml**: Расширенный диалог выбора материков

#### 1.2.2 Controller Layer
- **MainWindowController**: Класс для управления состоянием и взаимодействием между QML и C++

#### 1.2.3 Business Logic Layer
- **functions.h/cpp**: Основная бизнес-логика
  - Валидация IP-адресов
  - Парсинг данных с suip.biz
  - Конвертация между форматами (CIDR, Range)
- **http_client_sync_ssl.h/cpp**: HTTP клиент с поддержкой SSL
- **parallel_parsing.h/cpp**: Многопоточная обработка данных

#### 1.2.4 Data Layer
- **enum_variants.h**: Перечисления для типов парсинга и вариантов работы
- **Code data**: Статические данные с кодами стран и материков

### 1.3 Поток данных

1. **Пользователь взаимодействует с GUI** (выбор стран/материков, указание пути)
2. **Controller** получает события и обновляет состояние
3. **Business Logic** выполняет запросы к suip.biz API
4. **HTTP Client** отправляет запросы и получает данные
5. **Parallel Parser** обрабатывает данные в несколько потоков
6. **Data Layer** сохраняет результаты в файлы

---

## 2. API-спецификация (OpenAPI 3.0)

### 2.1 Внешний API (suip.biz)

```yaml
openapi: 3.0.3
info:
  title: IPS UIP External API Integration
  description: Интеграция с API suip.biz для получения IP-адресов
  version: 1.0.0
  contact:
    name: IPS UIP Team
    email: support@ipsuip.com

servers:
  - url: https://suip.biz/api
    description: Основной API сервер

paths:
  /ip:
    get:
      summary: Получение IP-адресов по географическому фильтру
      description: Возвращает список IP-адресов для указанных стран или материков
      parameters:
        - name: type
          in: query
          required: true
          schema:
            type: string
            enum: [continent, country]
          description: Тип географического фильтра
        - name: code
          in: query
          required: true
          schema:
            type: string
          description: Код материка или страны
        - name: format
          in: query
          required: false
          schema:
            type: string
            enum: [cidr, range, raw]
            default: raw
          description: Формат возвращаемых данных
      responses:
        '200':
          description: Успешный ответ
          content:
            text/plain:
              schema:
                type: string
                description: Список IP-адресов в указанном формате
        '400':
          description: Неверные параметры запроса
        '500':
          description: Внутренняя ошибка сервера

components:
  schemas:
    ErrorResponse:
      type: object
      properties:
        error:
          type: string
          description: Описание ошибки
        code:
          type: integer
          description: Код ошибки
```

### 2.2 Внутренний API (C++ интерфейсы)

#### 2.2.1 Функции парсинга

```cpp
/**
 * @brief Парсинг данных с сайта suip.biz
 * @param code Код страны или материка
 * @param TYPE Тип парсинга (CONTINENT или COUNTRY)
 * @return Вектор IP-адресов
 */
std::vector<std::string> parsing_site(const std::string& code, const TYPEPARSING& TYPE);

/**
 * @brief Валидация IP-адреса
 * @param ip Строка с IP-адресом
 * @return true если валидный, иначе false
 */
bool validateIP(const std::string& ip);

/**
 * @brief Конвертация границ диапазона в CIDR
 * @param ip_start Начальный IP в числовом формате
 * @param ip_end Конечный IP в числовом формате
 * @return Вектор CIDR-нотаций
 */
std::vector<std::string> range_boundaries_to_cidr(const long int& ip_start, const long int& ip_end);
```

#### 2.2.2 HTTP клиент

```cpp
/**
 * @brief GET запрос к внешнему API
 * @param host Хост сервера
 * @param target Целевой путь
 * @return Вектор строк с ответом
 */
std::vector<std::string> get(const std::string& host, const std::string& target);
```

---

## 3. Руководство по развертыванию и настройке

### 3.1 Требования системы

#### 3.1.1 Системные требования
- **Операционная система**: Linux (рекомендуется Ubuntu 20.04+), Windows 10+, macOS 10.15+
- **Память**: минимум 4 GB RAM
- **Процессор**: x86_64 архитектура
- **Диск**: минимум 500 MB свободного места

#### 3.1.2 Программные зависимости
- **CMake**: 3.23+
- **GCC**: 12.1+
- **Boost**: 1.82
- **Qt6**: Core, Gui, Qml, Quick, QuickControls2, Widgets
- **SSL библиотеки**: OpenSSL 1.1+

### 3.2 Сборка проекта

#### 3.2.1 Linux/macOS

```bash
# Клонирование репозитория
git clone https://github.com/your-username/ipsuip.git
cd ipsuip

# Создание директории сборки
mkdir -p build && cd build

# Конфигурация CMake
cmake .. -DCMAKE_CXX_STANDARD=20

# Сборка проекта
make -j$(nproc)

# Установка (опционально)
sudo make install
```

#### 3.2.2 Windows (с использованием vcpkg)

```bash
# Клонирование репозитория
git clone https://github.com/your-username/ipsuip.git
cd ipsuip

# Установка vcpkg
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.bat

# Установка зависимостей
vcpkg install boost:x64-windows
vcpkg install qtbase:x64-windows
vcpkg install qtdeclarative:x64-windows
vcpkg install qtquickcontrols2:x64-windows

# Создание директории сборки
mkdir build && cd build

# Конфигурация CMake
cmake .. -DCMAKE_CXX_STANDARD=20 -DCMAKE_TOOLCHAIN_FILE=../vcpkg/scripts/buildsystems/vcpkg.cmake

# Сборка проекта
cmake --build . --config Release
```

### 3.3 Настройка окружения

#### 3.3.1 Конфигурационные файлы

1. **Создайте конфигурационный файл** `config.ini`:
```ini
[settings]
# Настройки подключения к suip.biz
api_host = suip.biz
api_timeout = 30
max_retries = 3

# Настройки параллельной обработки
threads_count = 0  # 0 - автоопределение
chunk_size = 25

# Настройки сохранения
output_format = cidr  # cidr, range, raw
compression = true
```

2. **Переменные окружения**:
```bash
# Linux/macOS
export IPSUIP_CONFIG_PATH=/path/to/config.ini
export IPSUIP_DATA_PATH=/path/to/data

# Windows
set IPSUIP_CONFIG_PATH=C:\path\to\config.ini
set IPSUIP_DATA_PATH=C:\path\to\data
```

#### 3.3.2 Настройка SSL сертификатов

```bash
# Копирование корневых сертификатов
cp /usr/share/ca-certificates/mozilla/*.crt /path/to/ipsuip/certs/

# Или настройка системного хранилища
update-ca-trust extract
```

### 3.4 Развертывание в продакшене

#### 3.4.1 Docker контейнер

```dockerfile
# Dockerfile
FROM ubuntu:22.04

# Установка зависимостей
RUN apt-get update && apt-get install -y \
    cmake \
    build-essential \
    qt6-base-dev \
    qt6-declarative-dev \
    libssl-dev \
    && rm -rf /var/lib/apt/lists/*

# Копирование исходного кода
COPY . /app
WORKDIR /app

# Сборка проекта
RUN mkdir -p build && cd build \
    && cmake .. -DCMAKE_CXX_STANDARD=20 \
    && make -j$(nproc)

# Запуск приложения
CMD ["./build/ipsuip"]
```

#### 3.4.2 systemd сервис

```ini
# /etc/systemd/system/ipsuip.service
[Unit]
Description=IPS UIP Application
After=network.target

[Service]
Type=simple
User=ipsuip
Group=ipsuip
WorkingDirectory=/opt/ipsuip
ExecStart=/opt/ipsuip/build/ipsuip
Restart=on-failure
RestartSec=5

[Install]
WantedBy=multi-user.target
```

#### 3.4.3 Nginx reverse proxy (опционально)

```nginx
# /etc/nginx/sites-available/ipsuip
server {
    listen 80;
    server_name your-domain.com;

    location / {
        proxy_pass http://localhost:8080;
        proxy_set_header Host $host;
        proxy_set_header X-Real-IP $remote_addr;
        proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
        proxy_set_header X-Forwarded-Proto $scheme;
    }
}
```

### 3.5 Мониторинг и логирование

#### 3.5.1 Настройка логирования

```cpp
// В коде приложения
#include <spdlog/spdlog.h>
#include <spdlog/sinks/file_sink.h>

// Инициализация логирования
auto logger = spdlog::basic_logger_mt("ipsuip", "logs/ipsuip.log");
logger->set_level(spdlog::level::debug);
```

#### 3.5.2 Мониторинг производительности

```bash
# Пример скрипта мониторинга
#!/bin/bash
while true; do
    echo "$(date): Memory usage: $(free -m | grep Mem | awk '{print $3}') MB" >> monitoring.log
    echo "$(date): CPU usage: $(top -bn1 | grep "Cpu(s)" | awk '{print $2}' | cut -d'%' -f1)%" >> monitoring.log
    sleep 60
done
```

---

## 4. Примеры использования основных функций

### 4.1 Основные сценарии использования

#### 4.1.1 Программный интерфейс (C++)

```cpp
#include "functions.h"
#include <iostream>

int main() {
    namespace ipsuip = ipsuip;
    
    // Валидация IP-адреса
    std::string ip = "192.168.1.1";
    if (ipsuip::validateIP(ip)) {
        std::cout << "IP адрес валиден: " << ip << std::endl;
    } else {
        std::cout << "Неверный IP адрес: " << ip << std::endl;
    }
    
    // Получение IP-адресов для страны
    std::string country_code = "RU";
    auto ips = ipsuip::parsing_site(country_code, ipsuip::TYPEPARSING::COUNTRY);
    
    std::cout << "Получено " << ips.size() << " IP адресов для страны " << country_code << std::endl;
    
    // Сохранение в файл
    ipsuip::save_to_file(ips, "russian_ips.txt");
    
    return 0;
}
```

#### 4.1.2 Конвертация форматов IP-адресов

```cpp
#include "functions.h"
#include <iostream>

void demonstrate_conversion() {
    namespace ipsuip = ipsuip;
    
    // Пример конвертации диапазона в CIDR
    long int ip_start = 3232235521;  // 192.168.1.1
    long int ip_end = 3232235774;    // 192.168.30.254
    
    auto cidr_blocks = ipsuip::range_boundaries_to_cidr(ip_start, ip_end);
    
    std::cout << "Диапазон: 192.168.1.1 - 192.168.30.254" << std::endl;
    std::cout << "CIDR блоки:" << std::endl;
    for (const auto& cidr : cidr_blocks) {
        std::cout << "  - " << cidr << std::endl;
    }
}
```

#### 4.1.3 Многопоточная обработка

```cpp
#include "functions.h"
#include <iostream>
#include <vector>

void demonstrate_parallel_processing() {
    namespace ipsuip = ipsuip;
    
    std::vector<std::string> raw_ips = {
        "192.168.1.1", "192.168.1.2", "192.168.1.3",
        "10.0.0.1", "10.0.0.2", "10.0.0.3",
        "172.16.0.1", "172.16.0.2", "172.16.0.3"
    };
    
    // Параллельная конвертация в CIDR
    std::vector<std::string> cidr_results;
    ipsuip::parallel_work(
        raw_ips.begin(), 
        raw_ips.end(), 
        cidr_results, 
        ipsuip::VAR::TO_CIDR_S
    );
    
    std::cout << "Результаты параллельной обработки:" << std::endl;
    for (const auto& result : cidr_results) {
        std::cout << "  " << result << std::endl;
    }
}
```

### 4.2 Примеры использования через командную строку

#### 4.2.1 Сборка IP-адресов для нескольких стран

```bash
# Пример использования через обертку (если реализовано)
./ipsuip --country RU,US,DE --output ips_list.txt --format cidr
```

#### 4.2.2 Сборка IP-адресов для материков

```bash
./ipsuip --mainland EU,AS --output mainland_ips.txt --format range
```

### 4.3 Интеграция с другими проектами

#### 4.3.1 Python интеграция

```python
import subprocess
import json

def get_ips_for_country(country_code, output_file):
    """
    Получение IP-адресов для указанной страны
    
    Args:
        country_code (str): Код страны (например, 'RU')
        output_file (str): Путь к файлу для сохранения
    """
    cmd = ['./ipsuip', '--country', country_code, '--output', output_file]
    result = subprocess.run(cmd, capture_output=True, text=True)
    
    if result.returncode == 0:
        print(f"IP-адреса для {country_code} сохранены в {output_file}")
    else:
        print(f"Ошибка: {result.stderr}")

# Пример использования
get_ips_for_country('RU', 'russian_ips.txt')
```

#### 4.3.2 Shell скрипт для массовой обработки

```bash
#!/bin/bash

# Скрипт для сбора IP-адресов для списка стран
COUNTRIES=("RU" "US" "DE" "FR" "GB")
OUTPUT_DIR="ip_data"

mkdir -p "$OUTPUT_DIR"

for country in "${COUNTRIES[@]}"; do
    echo "Обработка страны: $country"
    ./ipsuip --country "$country" --output "$OUTPUT_DIR/${country}_ips.txt"
    echo "Завершено для $country"
done

echo "Обработка завершена. Результаты в директории $OUTPUT_DIR"
```

### 4.4 Примеры использования в продакшене

#### 4.4.1 Автоматическое обновление IP-списков

```cpp
#include "functions.h"
#include <thread>
#include <chrono>

void auto_update_ips() {
    namespace ipsuip = ipsuip;
    
    std::vector<std::string> countries = {"RU", "US", "CN", "DE"};
    std::string output_dir = "/etc/nginx/ip_lists";
    
    while (true) {
        for (const auto& country : countries) {
            try {
                auto ips = ipsuip::parsing_site(country, ipsuip::TYPEPARSING::COUNTRY);
                ipsuip::save_to_file(ips, output_dir + "/" + country + ".txt");
                
                // Конвертация в формат для Nginx
                auto cidr_blocks = ipsuip::range_boundaries_to_cidr(
                    ipsuip::ip_to_long(ips[0]), 
                    ipsuip::ip_to_long(ips.back())
                );
                
                ipsuip::save_to_file(cidr_blocks, output_dir + "/" + country + ".cidr");
                
                std::cout << "Обновлен список для " << country << ": " << ips.size() << " IP адресов" << std::endl;
            } catch (const std::exception& e) {
                std::cerr << "Ошибка при обновлении для " << country << ": " << e.what() << std::endl;
            }
        }
        
        // Ожидание 24 часов
        std::this_thread::sleep_for(std::chrono::hours(24));
    }
}
```

---

## 5. Глоссарий технических терминов

### 5.1 Основные термины

- **IP адрес** (Internet Protocol address) - Уникальный идентификатор устройства в сети
- **CIDR** (Classless Inter-Domain Routing) - Метод выделения адресов в сети и их маршрутизации
- **IP диапазон** - Непрерывная последовательность IP-адресов
- **SSL/TLS** - Протоколы для безопасной передачи данных
- **REST API** (Representational State Transfer Application Programming Interface) - Архитектурный стиль для веб-сервисов

### 5.2 Географические термины

- **Материк** (Continent) - Один из семи крупных участков суши
- **Страна** (Country) - Государство с определенными границами
- **Географическая фильтрация** - Отбор данных по географическому признаку
- **Код страны** - Двухбуквенный код страны (ISO 3166-1 alpha-2)
- **Код материка** - Двухбуквенный код материка

### 5.3 Технические термины

- **QML** (Qt Modeling Language) - Декларативный язык для создания пользовательских интерфейсов
- **Qt** - Кроссплатформенный фреймворк для разработки приложений
- **CMake** - Кроссплатформенная система автоматизации сборки
- **Boost** - Набор C++ библиотек с открытым исходным кодом
- **RAII** (Resource Acquisition Is Initialization) - Идиома программирования на C++
- **STL** (Standard Template Library) - Стандартная библиотека шаблонов C++

### 5.4 Сетевые термины

- **TCP/IP** - Протокольный стек для интернета
- **UDP** (User Datagram Protocol) - Протокол транспортного уровня
- **HTTP/HTTPS** - Протоколы передачи гипертекста
- **DNS** (Domain Name System) - Система доменных имен
- **DHCP** (Dynamic Host Configuration Protocol) - Протокол динамической конфигурации хоста

### 5.5 Термины параллельной обработки

- **Многопоточность** (Multithreading) - Использование нескольких потоков выполнения
- **Параллелизм** (Concurrency) - Выполнение нескольких задач одновременно
- **Синхронизация** - Координация доступа к общим ресурсам
- **Блокировка** (Lock) - Механизм синхронизации
- **Атомарная операция** - Операция, которая выполняется целиком или не выполняется совсем

### 5.6 Термины пользовательского интерфейса

- **GUI** (Graphical User Interface) - Графический пользовательский интерфейс
- **Widget** - Элемент графического интерфейса
- **Сигналы и слоты** (Signals and Slots) - Механизм взаимодействия в Qt
- **Свойство** (Property) - Атрибут объекта с возможностью привязки данных
- **Декларативный UI** - Описание интерфейса с помощью разметки

### 5.7 Термины контроля версий

- **Git** - Распределенная система контроля версий
- **Commit** - Единица изменений в репозитории
- **Branch** - Ветвь разработки
- **Merge** - Объединение ветвей
- **Pull Request** - Запрос на слияние изменений

### 5.8 Термины безопасности

- **SSL-сертификат** - Цифровой сертификат для шифрования
- **CA** (Certificate Authority) - Центр сертификации
- **X.509** - Стандарт для цифровых сертификатов
- **Root CA** - Корневой центр сертификации
- **Self-signed certificate** - Самоподписанный сертификат

---

## 6. Заключение

Документация охватывает все ключевые аспекты проекта IPS UIP, включая архитектуру, API, развертывание, примеры использования и техническую терминологию. Эта документация предназначена для различных целевых аудиторий и должна регулярно обновляться вместе с развитием проекта.

### 6.1 Дальнейшее развитие

- Добавление поддержки дополнительных форматов вывода
- Улучшение производительности при обработке больших объемов данных
- Расширение географической базы данных
- Добавление системы автоматического обновления
- Внедрение системы тестирования и CI/CD

### 6.2 Обратная связь

Все замечания и предложения по улучшению документации приветствуются. Пожалуйста, обращайтесь через:
- Issues на GitHub
- Email: documentation@ipsuip.com
- Форум проекта

---
*Документация создана: 29 января 2026 года*
*Версия: 1.0*