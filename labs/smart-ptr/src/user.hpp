#ifndef USER_HPP
#define USER_HPP

#include <QString>
#include "book.hpp"

class User {
public:
    User(const QString& name, int id) : name(name), id(id) {}

    [[nodiscard]] QString getName() const { return name; }
    [[nodiscard]] int getId() const { return id; }
    [[nodiscard]] const std::vector<std::shared_ptr<Book>>& getBooks() const { return books; }

    void addBook(const std::shared_ptr<Book>& book) { books.push_back(book); }

    void removeBook(const std::shared_ptr<Book>& book) {
        std::vector<std::shared_ptr<Book>> newBooks;
        for(const auto& i : books) {
            if(i != book) {
                newBooks.push_back(i);
            }
        }
        books = newBooks;
    }

private:
    std::vector<std::shared_ptr<Book>> books;
    QString name;
    int id;
};

inline std::shared_ptr<User> makeUser(const QString& name, int id) {
    return std::make_shared<User>(name, id);
}

inline void printUserInfo(const std::shared_ptr<User>& user) {
    qDebug() << "Name: " << user->getName();
    qDebug() << "ID: " << user->getId();
    qDebug() << "Books:";
    for(const std::shared_ptr<Book>& book : user->getBooks()) {
        printBookInfo(book);
    }
}

#endif // USER_HPP
