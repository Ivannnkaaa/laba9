#ifndef PROCESSING_H
#define PROCESSING_H

#include <string>

struct CallRecord {
    std::string number;
    std::string date;
    std::string time;
    std::string duration;
    std::string tariff;
    double cost_per_minute;

    int duration_seconds() const;
    bool is_mobile() const;
    bool is_november_2021() const;
    bool operator>(const CallRecord& other) const;
};

// Функция обработки данных (если она нужна)
int process();

#endif // PROCESSING_H
