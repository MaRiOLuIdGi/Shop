#pragma once
#include <string>
#include "PricingStrategy.h"

class Product;

class Customer {
private:
    std::string lastName;
    std::string firstName;
    std::string phoneNumber;
    std::string email;
    PricingStrategy* pricingStrategy;

    bool validateStringLength(const std::string& str, int maxLength = 40) const {
        return str.length() <= maxLength;
    }

    void validateData(const std::string& last, const std::string& first,
        const std::string& phone, const std::string& email) {
        if (last.empty() || first.empty() || phone.empty() || email.empty()) {
            throw std::invalid_argument("Все поля должны быть заполнены");
        }
        if (!validateStringLength(last)) {
            throw std::invalid_argument("Фамилия превышает допустимую длину");
        }
        if (!validateStringLength(first)) {
            throw std::invalid_argument("Имя превышает допустимую длину");
        }
        if (!validateStringLength(phone)) {
            throw std::invalid_argument("Телефон превышает допустимую длину");
        }
    }

public:
    Customer() : lastName("Иванов"), firstName("Иван"),
        phoneNumber("+7-XXX-XXX-XX-XX"), email("ivanov@example.com") {
        pricingStrategy = new RegularPricingStrategy();
    }

    Customer(const std::string& last, const std::string& first,
        const std::string& phone, const std::string& emailAddr,
        PricingStrategy* strategy)
        : lastName(last), firstName(first), phoneNumber(phone),
        email(emailAddr), pricingStrategy(strategy) {
        validateData(last, first, phone, emailAddr);
    }

    Customer(const Customer& other)
        : lastName(other.lastName), firstName(other.firstName),
        phoneNumber(other.phoneNumber), email(other.email) {
        if (dynamic_cast<RegularPricingStrategy*>(other.pricingStrategy)) {
            pricingStrategy = new RegularPricingStrategy();
        }
        else if (auto discount = dynamic_cast<DiscountPricingStrategy*>(other.pricingStrategy)) {
            pricingStrategy = new DiscountPricingStrategy(discount->getDiscountPercent());
        }
        else {
            pricingStrategy = new RegularPricingStrategy();
        }
    }

    Customer& operator=(const Customer& other) {
        if (this != &other) {
            lastName = other.lastName;
            firstName = other.firstName;
            phoneNumber = other.phoneNumber;
            email = other.email;

            delete pricingStrategy;

            if (dynamic_cast<RegularPricingStrategy*>(other.pricingStrategy)) {
                pricingStrategy = new RegularPricingStrategy();
            }
            else if (auto discount = dynamic_cast<DiscountPricingStrategy*>(other.pricingStrategy)) {
                pricingStrategy = new DiscountPricingStrategy(discount->getDiscountPercent());
            }
            else {
                pricingStrategy = new RegularPricingStrategy();
            }
        }
        return *this;
    }

    ~Customer() {
        delete pricingStrategy;
    }

    double calculateProductPrice(const Product& product) const;

    void setPricingStrategy(PricingStrategy* newStrategy) {
        if (newStrategy) {
            delete pricingStrategy;
            pricingStrategy = newStrategy;
        }
    }

    std::string getLastName() const { return lastName; }
    std::string getFirstName() const { return firstName; }
    std::string getPhoneNumber() const { return phoneNumber; }
    std::string getEmail() const { return email; }
    std::string getFullName() const { return lastName + " " + firstName; }
    const PricingStrategy* getPricingStrategy() const { return pricingStrategy; }

    bool hasDiscount() const {
        return dynamic_cast<DiscountPricingStrategy*>(pricingStrategy) != nullptr;
    }

    double getDiscountPercent() const {
        if (auto discount = dynamic_cast<DiscountPricingStrategy*>(pricingStrategy)) {
            return discount->getDiscountPercent();
        }
        return 0.0;
    }

    void setLastName(const std::string& last) {
        if (validateStringLength(last) && !last.empty()) {
            lastName = last;
        }
    }

    void setFirstName(const std::string& first) {
        if (validateStringLength(first) && !first.empty()) {
            firstName = first;
        }
    }

    void setPhoneNumber(const std::string& phone) {
        if (validateStringLength(phone) && !phone.empty()) {
            phoneNumber = phone;
        }
    }

    void setEmail(const std::string& emailAddr) {
        email = emailAddr;
    }
};