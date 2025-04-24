#include "user_books_dialog.hpp"
#include "library.hpp"
#include <QVBoxLayout>
#include <QListView>
#include <QStringListModel>
#include <QPushButton>
#include <QMessageBox>

UserBooksDialog::UserBooksDialog(const std::shared_ptr<User>& user, QWidget* parent)
    : QDialog(parent), user(user) {
    setWindowTitle("Книги пользователя: " + user->getName());
    QVBoxLayout* layout = new QVBoxLayout(this);

    QStringListModel* model = new QStringListModel(this);
    QStringList books;
    for (const auto& book : user->getBooks()) {
        books << book->getTitle();
    }
    model->setStringList(books);

    QListView* listView = new QListView(this);
    listView->setModel(model);
    layout->addWidget(listView);

    QPushButton* deleteButton = new QPushButton("Удалить книгу", this);
    layout->addWidget(deleteButton);

    connect(deleteButton, &QPushButton::clicked, [=]() {
        QModelIndex index = listView->currentIndex();
        if (index.isValid()) {
            auto book = user->getBooks()[index.row()];
            user->removeBook(book);
            Library lib;
            lib.addBook(book);
            model->setStringList({});
            update();
            QDialog::accept();
        }
    });
}
