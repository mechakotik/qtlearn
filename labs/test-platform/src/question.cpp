#include "question.hpp"

void Question::addVariant(Variant* variant) {
    variants.push_back(variant);
    emit variantsChanged();
}
