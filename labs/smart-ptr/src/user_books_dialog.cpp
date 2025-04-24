#include "user_books_dialog.hpp"
#include <QListView>
#include <QMessageBox>
#include <QPushButton>
#include <QStringListModel>
#include <QVBoxLayout>
#include "library.hpp"

UserBooksDialog::UserBooksDialog(const std::shared_ptr<User>& user, QWidget* parent) : QDialog(parent), user(user) {
    setWindowTitle("Книги пользователя " + user->getName());
    QVBoxLayout* layout = new QVBoxLayout(this);

    model = new QStringListModel(this);
    QStringList books;
    rebuildBooksList();

    listView = new QListView(this);
    listView->setModel(model);
    layout->addWidget(listView);

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    layout->addLayout(buttonLayout);

    QPushButton* deleteButton = new QPushButton("Удалить", this);
    buttonLayout->addWidget(deleteButton);

    QPushButton* okButton = new QPushButton("ОК", this);
    buttonLayout->addWidget(okButton);

    connect(deleteButton, &QPushButton::clicked, this, &UserBooksDialog::deleteCurrentBook);
    connect(okButton, &QPushButton::clicked, this, &QDialog::accept);
}

void UserBooksDialog::deleteCurrentBook() {
    QModelIndex index = listView->currentIndex();
    if(index.isValid()) {
        auto book = user->getBookAt(index.row());
        user->removeBook(book);
        rebuildBooksList();
        update();
    }
}

void UserBooksDialog::rebuildBooksList() {
    books.clear();
    for(const auto& book : user->getBooks()) {
        books << book->getTitle() + " (" + book->getAuthor() + ", " + QString::number(book->getYear()) + ")";
    }
    model->setStringList(books);
}
