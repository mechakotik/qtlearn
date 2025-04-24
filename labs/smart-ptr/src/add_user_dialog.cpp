#include "add_user_dialog.hpp"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

AddUserDialog::AddUserDialog(QWidget* parent) : QDialog(parent) {
    setWindowTitle("Добавить пользователя");
    QVBoxLayout* layout = new QVBoxLayout(this);

    QLabel* label = new QLabel("Имя", this);
    layout->addWidget(label);

    QLineEdit* lineEdit = new QLineEdit(this);
    layout->addWidget(lineEdit);

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    QPushButton* undoButton = new QPushButton("Отмена", this);
    QPushButton* okButton = new QPushButton("ОК", this);
    buttonLayout->addWidget(undoButton);
    buttonLayout->addWidget(okButton);

    layout->addLayout(buttonLayout);
    setMinimumHeight(layout->sizeHint().height());
    setMaximumHeight(layout->sizeHint().height());

    connect(okButton, &QPushButton::clicked, this, &AddUserDialog::accept);
    connect(okButton, &QPushButton::clicked, this, &AddUserDialog::reject);
}
