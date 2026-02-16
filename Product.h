#pragma once
#include <string>
#include <stdexcept>

class Product {
private:
    std::string name;
    double basePrice;
    std::string category;
    int stockQuantity;

    bool validateStringLength(const std::string& str, int maxLength = 40) const {
        return str.length() <= maxLength;
    }

public:
    Product() : name("—мартфон"), basePrice(25000.0), category("Ёлектроника"), stockQuantity(10) {}

    Product(const std::string& productName, double price,
        const std::string& productCategory = "Ёлектроника", int stock = 0)
        : name(productName), basePrice(price), category(productCategory), stockQuantity(stock) {
        if (price < 0) {
            throw std::invalid_argument("÷ена товара не может быть отрицательной");
        }
        if (!validateStringLength(productName)) {
            throw std::invalid_argument("Ќазвание товара превышает допустимую длину");
        }
        if (stock < 0) {
            throw std::invalid_argument(" оличество на складе не может быть отрицательным");
        }
    }

    std::string getName() const { return name; }
    double getBasePrice() const { return basePrice; }
    std::string getCategory() const { return category; }
    int getStockQuantity() const { return stockQuantity; }

    void setName(const std::string& newName) {
        if (validateStringLength(newName)) {
            name = newName;
        }
        else {
            throw std::invalid_argument("Ќазвание товара превышает допустимую длину");
        }
    }

    void setBasePrice(double price) {
        if (price >= 0) {
            basePrice = price;
        }
        else {
            throw std::invalid_argument("÷ена товара не может быть отрицательной");
        }
    }

    void setCategory(const std::string& newCategory) {
        category = newCategory;
    }

    void setStockQuantity(int quantity) {
        if (quantity >= 0) {
            stockQuantity = quantity;
        }
        else {
            throw std::invalid_argument(" оличество на складе не может быть отрицательным");
        }
    }
};