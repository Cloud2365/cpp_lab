#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include "Equation.h"
#include "Student.h"

void printGradeTable(const std::vector<int>& scores, const std::vector<Student*>& students) {
    std::cout << "\n========== Таблица успеваемости ==========\n";
    std::cout << std::left << std::setw(15) << "Студент"
        << std::setw(12) << "Тип"
        << "Правильно решено" << std::endl;
    std::cout << "-----------------------------------------\n";

    for (size_t i = 0; i < students.size(); i++) {
        std::string typeStr;
        switch (students[i]->getType()) {
        case StudentType::GOOD:    typeStr = "Хороший"; break;
        case StudentType::AVERAGE: typeStr = "Средний"; break;
        case StudentType::BAD:     typeStr = "Плохой";  break;
        }
        std::cout << std::left << std::setw(15) << students[i]->getName()
            << std::setw(12) << typeStr
            << scores[i] << std::endl;
    }
    std::cout << "=========================================\n";
}

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(0));

    // Чтение уравнений
    std::vector<Equation> equations = Equation::readFromFile("equations.txt");
    if (equations.empty()) {
        std::cerr << "Нет уравнений. Программа завершена." << std::endl;
        return 1;
    }
    std::cout << "Загружено уравнений: " << equations.size() << std::endl;

    // Создание студентов (полиморфизм)
    std::vector<Student*> students;
    students.push_back(new GoodStudent("Иванов"));
    students.push_back(new AverageStudent("Петров"));
    students.push_back(new BadStudent("Сидоров"));
    students.push_back(new AverageStudent("Козлов"));
    students.push_back(new GoodStudent("Смирнова"));
    std::cout << "Количество студентов: " << students.size() << std::endl;

    // Подсчёт баллов
    std::vector<int> scores(students.size(), 0);
    for (size_t i = 0; i < students.size(); ++i) {
        for (const auto& eq: equations) {
            Solution sol = students[i]->solve(eq);
            if (sol.isCorrectFor(eq)) {
                scores[i]++;
            }
        }
    }

    std::cout << "Всего проверено решений: " << students.size() * equations.size() << std::endl;
    printGradeTable(scores, students);

    // Очистка памяти
    for (auto* s : students) delete s;

    return 0;
}
