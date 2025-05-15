#include "test.hpp"
#include "question.hpp"
#include "error.hpp"
#include "resource_manager.hpp"

bool Test::load(const std::filesystem::path& path) {
    toml::value* res = getTable(path / "test.toml");
    if(res == nullptr) {
        return false;
    }

    try {
        loadFromToml(*res, path);
    } catch(std::exception& e) {
        showErrorDialog(QString::fromStdString("Ошибка загрузки теста из " + path.string() + ":\n" + e.what()));
        return false;
    }

    return true;
}

void Test::loadFromToml(const toml::value& table, const std::filesystem::path& path) {
    name = QString::fromStdString(table.at("test").at("name").as_string());

    for(const toml::value& question : table.at("questions").as_array()) {
        Question* q = new Question(this);
        if(question.contains("text")) {
            q->setProperty("text", QString::fromStdString(question.at("text").as_string()));
        }
        if(question.contains("image")) {
            std::filesystem::path imagePath = path / question.at("image").as_string();
            q->setProperty("image", QString::fromStdString("file:./" + imagePath.string()));
        }
        if(question.contains("variants")) {
            int maxScore = 0;
            for(const toml::value& variant : question.at("variants").as_array()) {
                if(variant.contains("score")) {
                    maxScore = std::max(maxScore, static_cast<int>(variant.at("score").as_integer()));
                }
            }
            for(const toml::value& variant : question.at("variants").as_array()) {
                Variant* var = new Variant(this);
                var->setProperty("text", QString::fromStdString(variant.at("text").as_string()));
                if(variant.contains("score")) {
                    var->setProperty("score", static_cast<int>(variant.at("score").as_integer()));
                    if(static_cast<int>(variant.at("score").as_integer()) == maxScore) {
                        var->setProperty("correct", true);
                    }
                }
                q->addVariant(var);
            }
        }
        if(question.contains("checkboxes")) {
            for(const toml::value& checkbox : question.at("checkboxes").as_array()) {
                Checkbox* cb = new Checkbox(this);
                cb->setProperty("text", QString::fromStdString(checkbox.at("text").as_string()));
                if(checkbox.contains("need")) {
                    cb->setProperty("need", checkbox.at("need").as_boolean());
                }
                q->addCheckbox(cb);
            }
        }
        if(question.contains("scores")) {
            for(const toml::value& score : question.at("scores").as_array()) {
                q->addScore(static_cast<int>(score.as_integer()));
            }
        }
        if(question.contains("answer")) {
            q->setCorrect(QString::fromStdString(question.at("answer").as_string()));
        }
        if(question.contains("score")) {
            q->setProperty("score", static_cast<int>(question.at("score").as_integer()));
        }
        questions.push_back(q);
    }

    emit nameChanged();
    emit questionsChanged();
}
