#include "Binary.h"
#include <fstream>

/* This method will open the files in binary and will copy the results, byte by byte to the vectors f1 and f2 */
void Binary::parseData() {
    vector<File> files = H.getFiles();

    string f1name = files[0].getName();
    string f2name = files[1].getName();

    string temp;

    ifstream in1, in2;
    in1.open(f1name, ios::binary);
    in2.open(f2name, ios::binary);

    int i = 0;

    // Add file1 contents to f1 vector, byte by byte
    while (!in1.eof()) {
        f1.push_back(0);
        in1.read((char*)&f1[i], 1);
        if(in1.fail()){
            f1.pop_back();
            break;
        }
        i++;
    }
    i = 0;
    // Add file2 contents to f2 vector, byte by byte
    while (!in2.eof()) {
        f2.push_back(0);
        in2.read((char*)&f2[i], 1);
        if (in2.fail()) {
            f2.pop_back();
            break;
        }
        i++;
    }
}

/* Similar method Text::addElements(), will add (remaining) elements from f2 to f1 if f1 reaches eof */
void Binary::addElements(bool valueNotAdded1) {
    // Last element in f2 was not added, I need to check if it equals the remaing elements in f1 or not
    if (valueNotAdded1) {
        it1--;
    }
    for (; it2 < f2.end(); it2++) {
        // If last element was checked, I will delete the rest of the f1 elements to match f2
        if (it1 == f1.end()) {
            changes.emplace_back(make_tuple((it2 - f2.begin()) >= 1 ? it2 - f2.begin() - 1 : 0, 'a', it2 - f2.begin()));
        }
            // Last element in f2 was not checked, so I will compare it to f1 till it reached f2.end()
        else {
            if (*it1 == *it2) {
                it1++;
            } else {
                changes.emplace_back(make_tuple((it2 - f2.begin()) >= 1 ? it2 - f2.begin() - 1 : 0, 'a', it2 - f2.begin()));
            }
        }
    }
    // If the last element of f1 was not equal to f2, I will delete it from f1
    if (it1 != f1.end() && it2 == f2.end()) {
        changes.emplace_back(make_tuple(it1 - f1.begin(), 'd', f2.size() - 1));
    }
}

/* Similar method to Text::deleteElements(), will delete (remaining) elements of f1 to match f2 */
void Binary::deleteElements(bool valueNotAdded2) {
    // Last element in f2 was not added, I need to check if it equals the remaing elements in f1 or not
    if (valueNotAdded2) {
        it2--;
    }
    for (; it1 < f1.end(); it1++) {
        // If last element was checked, I will delete the rest of the f1 elements to match f2
        if (it2 == f2.end()) {
            changes.emplace_back(make_tuple(it1 - f1.begin(), 'd', f2.size() >= 1 ? f2.size() - 1 : 0));
        }
            // Last element in f2 was not checked, so I will compare it to f1 till it reached f2.end()
        else {
            if (*it1 == *it2) {
                it2++;
            } else {
                changes.emplace_back(make_tuple(it1 - f1.begin(), 'd', f2.size() >= 1 ? f2.size() - 1 : 0));
            }
        }
    }
    // If the last element of f2 was not equal to f1, I will add it to f1
    if (it1 == f1.end() && it2 != f2.end()) {
        changes.emplace_back(make_tuple(it2 - f2.begin(), 'a', it2 - f2.begin()));
    }
}

/* Similar method to Text::compare() will compare f1 to f2 in zigzag order
 * and stores the differences in changes vector */
void Binary::compare() {
    int i = 0;
    /* Counter tracks how many elements did not equal each other.
     * It is mainly used to detect a change with f1 and f2,
     * instead of deleting an element from f1 and adding an element from f2, we simply change element *it1 with *it2 */
    int counter = 0;

    parseData(); // Get the data ready

    // Iterators through the vector that contains every paragraph
    it1 = f1.begin(); it2 = f2.begin();

    // This is used to shift the pointers between f1 and f2 while comparing the paragraphs
    bool changePTR = true;

    // Used to keep track when skipping an unmatched element
    bool valueNotAdded1 = false, valueNotAdded2 = false;

    while (i < f1.size()+f2.size()-1) {
        if (it1 == f1.end() && it2 == f2.end()) {
            break;
        }
            // If f1 reached its end, then we add all of the elements in f2
        else if (it1 == f1.end()) {
            addElements(valueNotAdded1);
            break;
        }
            // If f2 reached its end, then we delete all of the elements in f1
        else if (it2 == f2.end()) {
            deleteElements(valueNotAdded2);
            break;
        }

        if (*it1 != *it2) {
            if (changePTR) {
                it1++;
                counter++;
                changePTR = false;
                valueNotAdded1 = true;
            } else {
                it2++;
                counter++;
                changePTR = true;
                valueNotAdded2 = true;
            }
        } else {
            if (counter > 0) {
                counter--;
            }
            it1++; it2++;
        }

        // If counter is 0 then I just passed one element from f1 so I have to add it
        if (counter == 0 && (valueNotAdded1 || valueNotAdded2)) {
            changes.emplace_back(make_tuple(it1 - f1.begin() - 2, 'd', it2 - f2.begin() - 1));
            valueNotAdded1 = false;
        }
            // If counter is 2 then that means I passed both elements from f1 and f2 so I just change them
        else if (counter == 2) {
            changes.emplace_back(make_tuple(it1 - f1.begin() - 1, 'c', it2 - f2.begin() - 1));
            valueNotAdded1 = false; valueNotAdded2 = false;
            counter = 0;
        }
        i++;
    }
}

/* This method will gather the information from changes vector and print the output to a file and in terminal */
void Binary::printOutput() {
    for(auto &change: changes){
        // Display the changes
        cout << get<0>(change)+1 << get<1>(change) << get<2>(change)+1 << endl;

        // Add Element
        if(get<1>(change) == 'a'){
            cout << "< " << f2[get<2>(change)+1] << endl;
        }
            // Delete Element
        else if(get<1>(change) == 'd'){
            cout << "> " << f1[get<0>(change)] << endl;
        }
            // Change Element
        else{
            cout << "< " << f2[get<2>(change)] << endl;
            cout << "> " << f1[get<0>(change)] << endl;
        }
    }
}