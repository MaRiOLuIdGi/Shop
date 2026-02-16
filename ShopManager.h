#pragma once
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include "Customer.h"
#include "Product.h"

class ShopManager {
private:
    static const int MAX_CUSTOMERS = 100;
    static const int MAX_PRODUCTS = 20;

    std::vector<Customer*> customers;
    std::vector<Product> products;
    struct Order {
        Customer* customer;
        Product* product;
        int quantity;
    };
    std::vector<Order> orders;

    ShopManager() {
        products.push_back(Product("Смартфон", 25000.0, "Электроника", 50));
        products.push_back(Product("Ноутбук", 50000.0, "Электроника", 30));
        products.push_back(Product("Наушники", 8000.0, "Электроника", 100));
        products.push_back(Product("Планшет", 12000.0, "Электроника", 40));
        products.push_back(Product("Футболка", 1500.0, "Одежда", 200));
        products.push_back(Product("Джинсы", 4000.0, "Одежда", 150));
    }

    ShopManager(const ShopManager&) = delete;
    ShopManager& operator=(const ShopManager&) = delete;

public:
    static ShopManager& getInstance() {
        static ShopManager instance;
        return instance;
    }

    ~ShopManager() {
        for (auto customer : customers) {
            delete customer;
        }
    }

    bool addCustomer(const Customer& customer) {
        if (customers.size() >= MAX_CUSTOMERS) {
            return false;
        }

        for (auto c : customers) {
            if (c->getPhoneNumber() == customer.getPhoneNumber()) {
                return false;
            }
        }

        customers.push_back(new Customer(customer));
        return true;
    }

    bool addProduct(const Product& product) {
        if (products.size() >= MAX_PRODUCTS) {
            return false;
        }
        products.push_back(product);
        return true;
    }

    bool addOrder(const std::string& lastName, const std::string& productName, int quantity = 1) {
        Customer* customer = findCustomerByLastName(lastName);
        if (!customer) {
            return false;
        }

        Product* product = nullptr;
        for (auto& p : products) {
            if (p.getName() == productName && p.getStockQuantity() >= quantity) {
                product = &p;
                p.setStockQuantity(p.getStockQuantity() - quantity);
                break;
            }
        }

        if (!product) {
            return false;
        }

        Order order;
        order.customer = customer;
        order.product = product;
        order.quantity = quantity;
        orders.push_back(order);
        return true;
    }

    Customer* findCustomerByLastName(const std::string& lastName) {
        for (auto customer : customers) {
            if (customer->getLastName() == lastName) {
                return customer;
            }
        }
        return nullptr;
    }

    std::vector<Customer*> getAllCustomers() const {
        return customers;
    }

    std::vector<Product> getAllProducts() const {
        return products;
    }

    std::vector<Order> getAllOrders() const {
        return orders;
    }

    int getCustomerCount() const { return customers.size(); }
    int getProductCount() const { return products.size(); }
    int getOrderCount() const { return orders.size(); }

    const Product& getProduct(int index) const {
        if (index >= 0 && index < products.size()) {
            return products[index];
        }
        throw std::out_of_range("Неверный индекс товара");
    }

    double calculateTotalOrdersAmount() const {
        double total = 0.0;
        for (auto& order : orders) {
            total += order.customer->calculateProductPrice(*order.product) * order.quantity;
        }
        return total;
    }

    bool removeCustomer(const std::string& lastName) {
        for (auto it = customers.begin(); it != customers.end(); ++it) {
            if ((*it)->getLastName() == lastName) {
                delete* it;
                customers.erase(it);

                // Удаляем заказы этого клиента
                auto orderIt = orders.begin();
                while (orderIt != orders.end()) {
                    if (orderIt->customer->getLastName() == lastName) {
                        orderIt = orders.erase(orderIt);
                    }
                    else {
                        ++orderIt;
                    }
                }
                return true;
            }
        }
        return false;
    }

    bool removeProduct(int index) {
        if (index >= 0 && index < products.size()) {
            // Проверяем, есть ли заказы с этим товаром
            bool hasOrders = false;
            for (auto& order : orders) {
                if (order.product == &products[index]) {
                    hasOrders = true;
                    break;
                }
            }

            if (hasOrders) {
                return false; // Нельзя удалить товар, на который есть заказы
            }

            products.erase(products.begin() + index);
            return true;
        }
        return false;
    }

    bool updateCustomer(const std::string& oldLastName, const Customer& updatedCustomer) {
        for (auto customer : customers) {
            if (customer->getLastName() == oldLastName) {
                *customer = updatedCustomer;
                return true;
            }
        }
        return false;
    }

    bool updateProduct(int index, const Product& updatedProduct) {
        if (index >= 0 && index < products.size()) {
            products[index] = updatedProduct;
            return true;
        }
        return false;
    }

    std::vector<std::string> getProductCategories() const {
        std::vector<std::string> categories;
        for (auto& product : products) {
            if (std::find(categories.begin(), categories.end(), product.getCategory()) == categories.end()) {
                categories.push_back(product.getCategory());
            }
        }
        return categories;
    }

    double calculateCustomerTotal(const std::string& lastName) const {
        double total = 0.0;
        for (auto& order : orders) {
            if (order.customer->getLastName() == lastName) {
                total += order.customer->calculateProductPrice(*order.product) * order.quantity;
            }
        }
        return total;
    }
};