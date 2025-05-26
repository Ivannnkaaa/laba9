#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <stdexcept>

struct CallRecord {
    std::string number;
    std::string date;
    std::string time;
    std::string duration;
    std::string tariff;
    double cost_per_minute;

    int duration_seconds() const {
        std::istringstream ss(duration);
        int h, m, s;
        char delim1, delim2;
        ss >> h >> delim1 >> m >> delim2 >> s;
        return h * 3600 + m * 60 + s;
    }

    bool is_mobile() const {
        return tariff == "мобильный";
    }

    bool is_november_2021() const {
        return date.substr(3, 7) == "11.2021";
    }

    bool operator>(const CallRecord& other) const {
        return duration_seconds() > other.duration_seconds();
    }
};

// Функция загрузки данных из файла с обработкой ошибок
void loadRecords(const std::string& filename, std::vector<CallRecord>& records) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка: Не удалось открыть файл " << filename << "\n";
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        CallRecord record;
        ss >> record.number >> record.date >> record.time >> record.duration >> record.tariff >> record.cost_per_minute;
        records.push_back(record);
    }
}

// Фильтрация записей
void filterRecords(const std::vector<CallRecord>& records) {
    std::cout << "Телефонные разговоры на мобильные номера:\n";
    for (const auto& record : records) {
        if (record.is_mobile()) {
            std::cout << record.number << " " << record.date << " " << record.time << " " << record.duration << "\n";
        }
    }

    std::cout << "\nТелефонные разговоры в ноябре 2021 года:\n";
    for (const auto& record : records) {
        if (record.is_november_2021()) {
            std::cout << record.number << " " << record.date << " " << record.time << " " << record.duration << "\n";
        }
    }
}

// Функция пирамидальной сортировки (Heap Sort)
void heapify(std::vector<CallRecord>& records, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && records[left] > records[largest]) {
        largest = left;
    }
    if (right < n && records[right] > records[largest]) {
        largest = right;
    }

    if (largest != i) {
        std::swap(records[i], records[largest]);
        heapify(records, n, largest);
    }
}

void heapSort(std::vector<CallRecord>& records) {
    int n = records.size();
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(records, n, i);
    }
    for (int i = n - 1; i > 0; i--) {
        std::swap(records[0], records[i]);
        heapify(records, i, 0);
    }
}

// Функция быстрой сортировки (Quick Sort)
int partition(std::vector<CallRecord>& records, int low, int high) {
    CallRecord pivot = records[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (records[j].number < pivot.number ||
            (records[j].number == pivot.number && records[j].cost_per_minute > pivot.cost_per_minute)) {
            i++;
            std::swap(records[i], records[j]);
        }
    }
    std::swap(records[i + 1], records[high]);
    return i + 1;
}

void quickSort(std::vector<CallRecord>& records, int low, int high) {
    if (low < high) {
        int pi = partition(records, low, high);
        quickSort(records, low, pi - 1);
        quickSort(records, pi + 1, high);
    }
}

// Основная функция
int main() {
    setlocale(LC_ALL, "RU");
    std::vector<CallRecord> records;
    loadRecords("input.txt", records);

    filterRecords(records);

    heapSort(records);
    std::cout << "\nЗвонки после пирамидальной сортировки (по убыванию продолжительности):\n";
    for (const auto& record : records) {
        std::cout << record.number << " " << record.duration << " " << record.cost_per_minute << "\n";
    }

    quickSort(records, 0, records.size() - 1);
    std::cout << "\nЗвонки после быстрой сортировки (по возрастанию номера телефона, затем по убыванию стоимости):\n";
    for (const auto& record : records) {
        std::cout << record.number << " " << record.duration << " " << record.cost_per_minute << "\n";
    }

    return 0;
}
