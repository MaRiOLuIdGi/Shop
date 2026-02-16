#include "Customer.h"
#include "Product.h"

double Customer::calculateProductPrice(const Product& product) const {
    return pricingStrategy->calculatePrice(product.getBasePrice());
}