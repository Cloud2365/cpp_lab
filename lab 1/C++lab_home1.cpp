#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>


// Для сравнения ответов
const double EPS = 1e-9;
// Вероятность правильного решения у среднего ученика
const double AVERAGE_PROBABILITY = 0.7;

enum class StudentType {
    GOOD, // хороший
    AVERAGE, // средний
    BAD // плохой
};
// Уравнение
struct Equation {
    double a, b, c;

    double discriminant() const {
        return b * b - 4 * a * c;
    }

    void getRoots(double& x1, double& x2) const {
        double D = discriminant();
        double sqrtD = std::sqrt(D);
        x1 = (-b - sqrtD) / (2 * a);
        x2 = (-b + sqrtD) / (2 * a);
        if (x1 > x2) std::swap(x1, x2);
    }


    bool hasRealRoots() const {
        return discriminant() >= 0;
    }
};
// Решение
struct Solution {
    double root1, root2;

    Solution() {
        root1 = 0;
        root2 = 0
    };
    Solution(double r1, double r2) {
        root1 = r1;
        root2 = r2
    }

};

// Генерация решения
Solution generateSolution(const Equation& eq, StudentType type) {
    if (type == StudentType::GOOD) {
        double x1, x2;
        eq.getRoots(x1, x2);
        return Solution(x1, x2);
    }
    else if (type == StudentType::BAD) {
        double wrongRoot1 = (rand() % 20 - 10) + (rand() % 100) / 100.0;
        double wrongRoot2 = (rand() % 20 - 10) + (rand() % 100) / 100.0;
        return Solution(wrongRoot1, wrongRoot2);
    }
    else { // AVERAGE
        if ((rand() % 100) < 70) {
            double x1, x2;
            eq.getRoots(x1, x2);
            return Solution(x1, x2);
        }
        else {
            double wrongRoot1 = (rand() % 20 - 10) + (rand() % 100) / 100.0;
            double wrongRoot2 = (rand() % 20 - 10) + (rand() % 100) / 100.0;
            return Solution(wrongRoot1, wrongRoot2);
        }
    }
}
struct StudentInfo {
    std::string name;
    StudentType type;
};

// Чтение уравнений из файла
std::vector<Equation> readEquations(const std::string& filename) {
    std::vector<Equation> equations;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл " << filename << std::endl;
        return equations;
    }

    double a, b, c;
    while (file >> a >> b >> c) {
        if (std::fabs(a) < EPS) {
            std::cerr << "Предупреждение: a = 0, пропускаем." << std::endl;
            continue;
        }
        equations.push_back({ a, b, c });
    }
    file.close();
    return equations;
}



// Проверка правильности решения
bool isSolutionCorrect(const Equation& eq, const Solution& studentSol) {
    if (!eq.hasRealRoots()) {
        return false;
    }

    double correctX1, correctX2;
    eq.getRoots(correctX1, correctX2);


    double s1 = studentSol.root1, s2 = studentSol.root2;
    if (s1 > s2) std::swap(s1, s2);
    return (std::fabs(s1 - correctX1) < EPS &&
        std::fabs(s2 - correctX2) < EPS);

}

// Поиск студента в массиве по имени 
int findStudentIndex(const std::vector<StudentInfo>& students, const std::string& name) {
    for (int i = 0; i < students.size(); i++) {
        if (students[i].name == name) {
            return i;  // вернули индекс
        }
    }
    return -1;  // не найден
}

// Вывод таблицы успеваемости
void printGradeTable(const std::vector<int>& scores,
    const std::vector<StudentInfo>& students) {
    std::cout << "\n========== Таблица успеваемости ==========\n";
    std::cout << std::left << std::setw(15) << "Студент"
        << std::setw(12) << "Тип"
        << "Правильно решено" << std::endl;
    std::cout << "-----------------------------------------\n";

    for (int i = 0; i < students.size(); i++) {
        std::string typeStr;
        if (students[i].type == StudentType::GOOD) typeStr = "Хороший";
        else if (students[i].type == StudentType::AVERAGE) typeStr = "Средний";
        else typeStr = "Плохой";

        std::cout << std::left << std::setw(15) << students[i].name
            << std::setw(12) << typeStr
            << scores[i] << std::endl;
    }
    std::cout << "=========================================\n";
}

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(0));

    // 1. Чтение уравнений
    std::string equationFile = "equations.txt";
    std::vector<Equation> equations = readEquations(equationFile);

    if (equations.empty()) {
        std::cerr << "Нет уравнений. Программа завершена." << std::endl;
        return 1;
    }

    std::cout << "Загруже уравнений: " << equations.size() << std::endl;

    // 2. Список студентов
    std::vector<StudentInfo> students = {
        {"Иванов", StudentType::GOOD},
        {"Петров", StudentType::AVERAGE},
        {"Сидоров", StudentType::BAD},
        {"Козлов", StudentType::AVERAGE},
        {"Смирнова", StudentType::GOOD}
    };
    std::cout << "Количество студентов: " << students.size() << std::endl;

    // 3. Массив для баллов 
    std::vector<int> scores(students.size(), 0);  // все нули

    // 4. Основной цикл
    for (int i = 0; i < students.size(); i++) {
        for (int j = 0; j < equations.size(); j++) {
            Solution sol = generateSolution(equations[j], students[i].type);
            if (isSolutionCorrect(equations[j], sol)) {
                scores[i]++;  // увеличиваем счётчик
            }
        }
    }

    std::cout << "Всего проверено решений " << students.size() * equations.size() << std::endl;

    // 5. Вывод результатов
    printGradeTable(scores, students);

    return 0;
}