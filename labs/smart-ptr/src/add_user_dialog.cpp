#include "add_user_dialog.hpp"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

AddUserDialog::AddUserDialog(QWidget* parent) : QDialog(parent), lineEdit(new QLineEdit(this)) {
    setWindowTitle("Добавить пользователя");
    QVBoxLayout* layout = new QVBoxLayout(this);

    QLabel* label = new QLabel("Имя", this);
    layout->addWidget(label);
    layout->addWidget(lineEdit);

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    QPushButton* cancelButton = new QPushButton("Отмена", this);
    QPushButton* okButton = new QPushButton("ОК", this);
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addWidget(okButton);
    layout->addLayout(buttonLayout);

    connect(okButton, &QPushButton::clicked, this, &AddUserDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &AddUserDialog::reject);
}

QString AddUserDialog::getUserName() const {
    return lineEdit->text();
}
