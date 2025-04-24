#ifndef BOOK_HPP
#define BOOK_HPP

#include <QString>

class Book {
public:
    Book(const QString& title, const QString& author, int year) : title(title), author(author), year(year) {}

    [[nodiscard]] QString getTitle() const { return title; }
    [[nodiscard]] QString getAuthor() const { return author; }
    [[nodiscard]] int getYear() const { return year; }

private:
    QString title;
    QString author;
    int year;
};

inline std::shared_ptr<Book> makeBook(const QString& title, const QString& author, int year) {
    return std::make_shared<Book>(title, author, year);
}

inline void printBookInfo(const std::shared_ptr<Book>& book) {
    qDebug() << "Title: " << book->getTitle();
    qDebug() << "Author: " << book->getAuthor();
    qDebug() << "Year: " << book->getYear();
}

#endif // BOOK_HPP
