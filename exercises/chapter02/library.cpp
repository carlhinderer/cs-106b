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

const int NUM_AUTHORS = 5;
const int NUM_SUB_HEADERS = 5;
const int MAX_COLLECTION_SIZE = 1000;

/* Book Type */
struct bookT {
    string title;
    string authors[NUM_AUTHORS];
    string locCatalog;
    string subjectHeaders[NUM_SUB_HEADERS];
    string publisher;
    int publicationYear;
    bool circulating;
};

struct libraryT {
    string name;
    bookT collection[MAX_COLLECTION_SIZE];
    int collectionSize;
};

void SearchBySubject(libraryT library, string subject);
void TestSearchBySubject();
void TestBookType();
void TestLibraryType();
bookT Book1();
bookT Book2();
libraryT Library1();

int main() {
    TestBookType();
    TestLibraryType();
    TestSearchBySubject();
    return 0;
}

void SearchBySubject(libraryT library, string subject) {
    for (int i=0; i < library.collectionSize; i++) {
        for (int j=0; j < NUM_SUB_HEADERS; j++) {
            if (library.collection[i].subjectHeaders[j] == subject) {
                cout << library.collection[i].title
                     << " by " << library.collection[i].authors[0]
                     << " (LOC#: " << library.collection[i].locCatalog 
                     << ")" << endl;
            }
        }
    }
}

void TestSearchBySubject() {
    cout << endl << "Testing search by subject..." << endl;
    string subjects[] = {"California", "Mice", "Colorado"};
    libraryT library = Library1();
    for (int i=0; i<3; i++) {
        cout << "Searching by subject '" << subjects[i] << "'" << endl;
        SearchBySubject(library, subjects[i]);
    }
}

void TestBookType() {
    cout << "Testing book type..." << endl;
    bookT book = Book1();
    cout << book.title << " by " << book.authors[0] << endl;
    cout << "Catelog #: " << book.locCatalog << endl;
    cout << "Publisher: " << book.publisher << endl;
    cout << "(" << book.publicationYear << ")" << endl;
}

void TestLibraryType() {
    cout << endl << "Testing library type..." << endl;
    libraryT library = Library1();
    cout << "The " << library.name << " Library" << endl;
}

bookT Book1() {
    bookT book;
    book.title = "Of Mice and Men";
    book.authors[0] = "John Stenibeck";
    book.locCatalog = "ASDFGHJK987";
    book.subjectHeaders[0] = "Mice";
    book.subjectHeaders[1] = "Men";
    book.subjectHeaders[2] = "California";
    book.publisher = "Random House";
    book.publicationYear = 1936;
    book.circulating = true;
    return book;
}

bookT Book2() {
    bookT book;
    book.title = "Cannery Row";
    book.authors[0] = "John Stenibeck";
    book.subjectHeaders[0] = "Cans";
    book.subjectHeaders[1] = "California";
    book.publisher = "Penguin";
    book.publicationYear = 1933;
    book.circulating = false;
    return book;
}

libraryT Library1() {
    libraryT library;
    library.name = "Downtown Branch";
    library.collectionSize = 0;
    library.collection[library.collectionSize] = Book1();
    library.collectionSize++;
    library.collection[library.collectionSize] = Book2();
    library.collectionSize++;
    return library;
}