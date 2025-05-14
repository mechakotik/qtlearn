#include "question.hpp"

void Question::addVariant(Variant* variant) {
    variants.push_back(variant);
    emit variantsChanged();
}

void Question::addCheckbox(Checkbox* checkbox) {
    checkboxes.push_back(checkbox);
    emit checkboxesChanged();
}

void Question::addScore(int score) {
    scores.push_back(score);
    emit scoresChanged();
}
