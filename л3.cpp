#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

// ��������� ��� ������������� ��������
struct Product {
    std::string name;
    double price;
    int quantity;
};

// ������� ��� ����� ���������� � ��������� � ���������� �� � ���� "products.txt"
void inputProducts(std::vector<Product>& products) {
    std::ofstream file("products.txt", std::ios::app); // ��������� ���� ��� ���������� ������

    if (!file.is_open()) {
        std::cerr << "������ �������� ����� 'products.txt'" << std::endl;
        return;
    }

    while (true) {
        Product product;
        std::cout << "������� �������� �������� (��� 'q' ��� ����������): ";
        std::cin >> product.name;

        if (product.name == "q") {
            break; // ��������� ����
        }

        std::cout << "������� ���� ��������: ";
        std::cin >> product.price;
        std::cout << "������� ���������� ��������: ";
        std::cin >> product.quantity;

        products.push_back(product); // ��������� ������� � ������

        // ���������� ������� � ����
        file << product.name << " " << product.price << " " << product.quantity << "\n";
    }

    file.close();
}

// ������� ��� ������ �������� �� �������� � ����� "products.txt"
void searchProductByName(const std::vector<Product>& products, const std::string& name) {
    for (const Product& product : products) {
        if (product.name == name) {
            std::cout << "��������: " << product.name << ", ����: " << product.price << ", ����������: " << product.quantity << "\n";
        }
    }
}

// ������� ��� ���������� ��������� � ����� �� ���� ��� ����������
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

// ������� ��� ���������� ������ �������� � ����� ����� "products.txt"
void addProduct(std::vector<Product>& products) {
    std::ofstream file("products.txt", std::ios::app); // ��������� ���� ��� ���������� ������

    if (!file.is_open()) {
        std::cerr << "������ �������� ����� 'products.txt'" << std::endl;
        return;
    }

    Product product;
    std::cout << "������� �������� ��������: ";
    std::cin >> product.name;
    std::cout << "������� ���� ��������: ";
    std::cin >> product.price;
    std::cout << "������� ���������� ��������: ";
    std::cin >> product.quantity;

    products.push_back(product); // ��������� ������� � ������

    // ���������� ������� � ����
    file << product.name << " " << product.price << " " << product.quantity << "\n";
    file.close();
}

// ������� ��� ������ ���������� � ���������, ��������������� ������������� �������
void displayProductsByCondition(const std::vector<Product>& products, double minPrice, int minQuantity) {
    for (const Product& product : products) {
        if (product.price >= minPrice && product.quantity >= minQuantity) {
            std::cout << "��������: " << product.name << ", ����: " << product.price << ", ����������: " << product.quantity << "\n";
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    std::vector<Product> products;
    std::string sortBy;

    // ���� ������ � ��������� � ���������� � ���� "products.txt"
    std::cout << "������� ���������� � ���������. ��� ���������� ������� 'q' � ���� ��������.\n";
    inputProducts(products);

    // �������������� ����
    while (true) {
        std::cout << "\n����:\n";
        std::cout << "1. ����� �������� �� ��������\n";
        std::cout << "2. ���������� ���������\n";
        std::cout << "3. ���������� ������ ��������\n";
        std::cout << "4. ����� ��������� �� �������\n";
        std::cout << "5. �����\n";

        int choice;
        std::cout << "�������� ��������: ";
        std::cin >> choice;

        if (choice == 1) {
            std::string name;
            std::cout << "������� �������� ��� ������: ";
            std::cin >> name;
            searchProductByName(products, name);
        }
        else if (choice == 2) {
            std::cout << "����������� �� ���� (price) ��� ���������� (quantity): ";
            std::cin >> sortBy;
            sortProducts(products, sortBy);
            std::cout << "�������� ������������� �� " << sortBy << "\n";
        }
        else if (choice == 3) {
            addProduct(products);
            std::cout << "������� ��������\n";
        }
        else if (choice == 4) {
            double minPrice;
            int minQuantity;
            std::cout << "����������� ����: ";
            std::cin >> minPrice;
            std::cout << "����������� ����������: ";
            std::cin >> minQuantity;
            displayProductsByCondition(products, minPrice, minQuantity);
        }
        else if (choice == 5) {
            break; // ����� �� ���������
        }
        else {
            std::cout << "������������ �����. ���������� �����.\n";
        }
    }

    // ���������� ����������� � ���� "output.txt"
    std::ofstream output("output.txt");
    if (output.is_open()) {
        for (const Product& product : products) {
            output << "��������: " << product.name << ", ����: " << product.price << ", ����������: " << product.quantity << "\n";
        }
        output.close();
    }
    else {
        std::cerr << "������ �������� �����";
        }
}