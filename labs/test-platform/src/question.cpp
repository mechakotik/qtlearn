#include "question.hpp"

void Question::addVariant(Variant* variant) {
    variants.push_back(variant);
    emit variantsChanged();
    if(textOnly) {
        textOnly = false;
        emit textOnlyChanged();
    }
}

void Question::addCheckbox(Checkbox* checkbox) {
    checkboxes.push_back(checkbox);
    emit checkboxesChanged();
    if(textOnly) {
        textOnly = false;
        emit textOnlyChanged();
    }
}

void Question::addScore(int score) {
    scores.push_back(score);
    emit scoresChanged();
}
