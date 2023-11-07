#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

// Структура для представления продукта
struct Product {
    std::string name;
    double price;
    int quantity;
};

// Функция для ввода информации о продуктах и сохранения их в файл "products.txt"
void inputProducts(std::vector<Product>& products) {
    std::ofstream file("products.txt", std::ios::app); // Открываем файл для добавления данных

    if (!file.is_open()) {
        std::cerr << "Ошибка открытия файла 'products.txt'" << std::endl;
        return;
    }

    while (true) {
        Product product;
        std::cout << "Введите название продукта (или 'q' для завершения): ";
        std::cin >> product.name;

        if (product.name == "q") {
            break; // Завершаем ввод
        }

        std::cout << "Введите цену продукта: ";
        std::cin >> product.price;
        std::cout << "Введите количество продукта: ";
        std::cin >> product.quantity;

        products.push_back(product); // Добавляем продукт в вектор

        // Записываем продукт в файл
        file << product.name << " " << product.price << " " << product.quantity << "\n";
    }

    file.close();
}

// Функция для поиска продукта по названию в файле "products.txt"
void searchProductByName(const std::vector<Product>& products, const std::string& name) {
    for (const Product& product : products) {
        if (product.name == name) {
            std::cout << "Название: " << product.name << ", Цена: " << product.price << ", Количество: " << product.quantity << "\n";
        }
    }
}

// Функция для сортировки продуктов в файле по цене или количеству
void sortProducts(std::vector<Product>& products, const std::string& sortBy) {
    if (sortBy == "price") {
        std::sort(products.begin(), products.end(), [](const Product& a, const Product& b) {
            return a.price < b.price;
            });
    }
    else if (sortBy == "quantity") {
        std::sort(products.begin(), products.end(), [](const Product& a, const Product& b) {
            return a.quantity < b.quantity;
            });
    }
}

// Функция для добавления нового продукта в конец файла "products.txt"
void addProduct(std::vector<Product>& products) {
    std::ofstream file("products.txt", std::ios::app); // Открываем файл для добавления данных

    if (!file.is_open()) {
        std::cerr << "Ошибка открытия файла 'products.txt'" << std::endl;
        return;
    }

    Product product;
    std::cout << "Введите название продукта: ";
    std::cin >> product.name;
    std::cout << "Введите цену продукта: ";
    std::cin >> product.price;
    std::cout << "Введите количество продукта: ";
    std::cin >> product.quantity;

    products.push_back(product); // Добавляем продукт в вектор

    // Записываем продукт в файл
    file << product.name << " " << product.price << " " << product.quantity << "\n";
    file.close();
}

// Функция для вывода информации о продуктах, удовлетворяющих определенному условию
void displayProductsByCondition(const std::vector<Product>& products, double minPrice, int minQuantity) {
    for (const Product& product : products) {
        if (product.price >= minPrice && product.quantity >= minQuantity) {
            std::cout << "Название: " << product.name << ", Цена: " << product.price << ", Количество: " << product.quantity << "\n";
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    std::vector<Product> products;
    std::string sortBy;

    // Ввод данных о продуктах и сохранение в файл "products.txt"
    std::cout << "Введите информацию о продуктах. Для завершения введите 'q' в поле названия.\n";
    inputProducts(products);

    // Функциональное меню
    while (true) {
        std::cout << "\nМеню:\n";
        std::cout << "1. Поиск продукта по названию\n";
        std::cout << "2. Сортировка продуктов\n";
        std::cout << "3. Добавление нового продукта\n";
        std::cout << "4. Вывод продуктов по условию\n";
        std::cout << "5. Выход\n";

        int choice;
        std::cout << "Выберите действие: ";
        std::cin >> choice;

        if (choice == 1) {
            std::string name;
            std::cout << "Введите название для поиска: ";
            std::cin >> name;
            searchProductByName(products, name);
        }
        else if (choice == 2) {
            std::cout << "Сортировать по цене (price) или количеству (quantity): ";
            std::cin >> sortBy;
            sortProducts(products, sortBy);
            std::cout << "Продукты отсортированы по " << sortBy << "\n";
        }
        else if (choice == 3) {
            addProduct(products);
            std::cout << "Продукт добавлен\n";
        }
        else if (choice == 4) {
            double minPrice;
            int minQuantity;
            std::cout << "Минимальная цена: ";
            std::cin >> minPrice;
            std::cout << "Минимальное количество: ";
            std::cin >> minQuantity;
            displayProductsByCondition(products, minPrice, minQuantity);
        }
        else if (choice == 5) {
            break; // Выход из программы
        }
        else {
            std::cout << "Неправильный выбор. Попробуйте снова.\n";
        }
    }

    // Сохранение результатов в файл "output.txt"
    std::ofstream output("output.txt");
    if (output.is_open()) {
        for (const Product& product : products) {
            output << "Название: " << product.name << ", Цена: " << product.price << ", Количество: " << product.quantity << "\n";
        }
        output.close();
    }
    else {
        std::cerr << "Ошибка открытия файла";
        }
}