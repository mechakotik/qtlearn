#include "find_book_dialog.hpp"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

FindBookDialog::FindBookDialog(QWidget* parent)
    : QDialog(parent), title(new QLineEdit(this)), author(new QLineEdit(this)) {
    setWindowTitle("Поиск книги");
    QVBoxLayout* layout = new QVBoxLayout(this);

    QLabel* titleLabel = new QLabel("Название", this);
    QLabel* authorLabel = new QLabel("Автор", this);
    title->setPlaceholderText("Любое");
    author->setPlaceholderText("Любой");
    layout->addWidget(titleLabel);
    layout->addWidget(title);
    layout->addWidget(authorLabel);
    layout->addWidget(author);

    QHBoxLayout* buttonLayout = new QHBoxLayout(this);
    QPushButton* cancelButton = new QPushButton("Отмена", this);
    QPushButton* findButton = new QPushButton("Найти", this);
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addWidget(findButton);
    layout->addLayout(buttonLayout);

    connect(cancelButton, &QPushButton::clicked, this, &FindBookDialog::reject);
    connect(findButton, &QPushButton::clicked, this, &FindBookDialog::accept);
}
