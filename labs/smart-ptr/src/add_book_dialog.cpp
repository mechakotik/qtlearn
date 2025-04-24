#include "add_book_dialog.hpp"
#include <QIntValidator>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

AddBookDialog::AddBookDialog(QWidget* parent)
    : QDialog(parent), titleEdit(new QLineEdit(this)), authorEdit(new QLineEdit(this)), yearEdit(new QLineEdit(this)) {
    setWindowTitle("Добавить книгу");
    QVBoxLayout* layout = new QVBoxLayout(this);

    layout->addWidget(new QLabel("Название", this));
    layout->addWidget(titleEdit);
    layout->addWidget(new QLabel("Автор", this));
    layout->addWidget(authorEdit);
    layout->addWidget(new QLabel("Год", this));
    yearEdit->setValidator(new QIntValidator(1, 9999, this));
    layout->addWidget(yearEdit);

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    QPushButton* cancelButton = new QPushButton("Отмена", this);
    QPushButton* okButton = new QPushButton("ОК", this);
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addWidget(okButton);
    layout->addLayout(buttonLayout);

    connect(okButton, &QPushButton::clicked, this, &AddBookDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &AddBookDialog::reject);
}

QString AddBookDialog::getTitle() const {
    return titleEdit->text();
}

QString AddBookDialog::getAuthor() const {
    return authorEdit->text();
}

int AddBookDialog::getYear() const {
    return yearEdit->text().toInt();
}
