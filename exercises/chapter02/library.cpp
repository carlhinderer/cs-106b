/* library.cpp
 * --------------------------------------------------------
 * Suppose that you have been assigned the task of computerizing the card catalog
 *   system for a library.  As a first step, your supervisor has asked you to develop a
 *   prototype capable of storing the following information for each of 1000 books:
 *     - The title
 *     - A list of up to five authors
 *     - The Library of Congress catalog number
 *     - A list of up to five subject headings
 *     - The publisher
 *     - The year of publication
 *     - Whether the book is circulating or noncirculating
 * 
 * Given your definition, it should be possible to write the declaration
 *   libraryT libdata;
 * 
 * Write an additional procedure SearchBySubject that takes as parameters the
 * library database and a subject string.  For each book in the library that lists the
 * subject string as one of its subject headings, SearchBySubject should display the
 * title, the name of the first author, and the Library of Congress catalog number.
 */

#include <iostream>
#include <string>
using namespace std;

/* Book Type */
struct bookT {
    string title;
    string authors[5];
    string locCatalog;
    string subjectHeaders[5];
    string publisher;
    int publicationYear;
    bool circulating;
};

struct libraryT {
    string name;
    bookT collection[1000];
    int collectionSize;
};

void TestBookType();
bookT TestBook1();

int main() {
    TestBookType();
    return 0;
}

void TestBookType() {
    bookT book = TestBook1();
    cout << book.title << " by " << book.authors[0] << endl;
    cout << "Catelog #: " << book.locCatalog << endl;
    cout << "Publisher: " << book.publisher << endl;
    cout << "(" << book.publicationYear << ")" << endl;
}

bookT TestBook1() {
    bookT book;
    book.title = "Of Mice and Men";
    book.authors[0] = "John Stenibeck";
    book.locCatalog = "ASDFGHJK987";
    book.subjectHeaders[0] = "Mice";
    book.subjectHeaders[1] = "Men";
    book.publisher = "Random House";
    book.publicationYear = 1936;
    book.circulating = true;
    return book;
}