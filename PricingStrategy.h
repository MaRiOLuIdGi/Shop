#pragma once
#include <string>
#include <stdexcept>

class PricingStrategy {
public:
    virtual ~PricingStrategy() = default;
    virtual double calculatePrice(double basePrice) const = 0;
    virtual std::string getStrategyName() const = 0;
    virtual std::string getDescription() const = 0;
};

class RegularPricingStrategy : public PricingStrategy {
public:
    double calculatePrice(double basePrice) const override {
        return basePrice;
    }

    std::string getStrategyName() const override {
        return "Обычная цена";
    }

    std::string getDescription() const override {
        return "Оплата полной стоимости товара";
    }
};

class DiscountPricingStrategy : public PricingStrategy {
private:
    double discountPercent;

public:
    DiscountPricingStrategy(double discount = 0.0) : discountPercent(discount) {
        if (discount < 0 || discount > 100) {
            throw std::invalid_argument("Скидка должна быть от 0 до 100%");
        }
    }

    double calculatePrice(double basePrice) const override {
        return basePrice * (1 - discountPercent / 100.0);
    }

    std::string getStrategyName() const override {
        return "Со скидкой";
    }

    std::string getDescription() const override {
        return "Оплата со скидкой " + std::to_string((int)discountPercent) + "%";
    }

    double getDiscountPercent() const { return discountPercent; }
    void setDiscountPercent(double discount) {
        if (discount >= 0 && discount <= 100) {
            discountPercent = discount;
        }
    }
};