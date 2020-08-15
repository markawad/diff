#include "OutputHandler.h"
#include "../FileTypes/FileTypeHandler.h"
#include "Directory.h"

OutputHandler::OutputHandler(FileHandler &h) : H(h) {}

/* This method will figure out if it is comparing files or directories and adjust its output as such */
void OutputHandler::DecideOutputTypes(const string &dir1, string const &dir2) {

    // Checks if it is comparing directories
    if (H.files[0].isDirectory()) {
        Directory d1(H, dir1);
        Directory d2(H, dir2);

        auto it1 = d1.files.begin();
        auto it2 = d2.files.begin();

        // Will look if d2 has the same file as d1, if it does then we compare them
        while (it1 != d1.files.end()) {
            // Will ignore all files in d1 once files.end() reached in d2
            if (it2 == d2.files.end()) {
                cout << "File " << *it1 << " not found in: " << d2.getName() << endl;
                continue;
            }
            auto search = d2.files.find(*it1);
            // File found in d2
            if (search != d2.files.end()) {
                string s1 = d1.getName() + *it1;
                string s2 = d2.getName() + *it1;

                cout << "diff " << s1 << " " << s2 << endl;

                H.files[0].setName(s1);
                H.files[1].setName(s2);

                H.UpdateFiles();
                FileTypeHandler F(H);
                F.ChooseFileType();
                cout << "-------------------------------------------------------" << endl;
            }
            // File not found
            else {
                cout << "File " << *it1 << " not found in: " << d2.getName() << endl;
            }
            it1++;
        }
        // Will ignore all files in d2 which are not in d1 and report them to the user
        while (it2 != d2.files.end()) {
            auto search2 = d1.files.find(*it2);
            if (search2 == d1.files.end()) {
                cout << "File " << *it2 << " not found in: " << d1.getName() << endl;
            }
            it2++;
        }

        // Compare sub folders in sub folders and so on if -r was used
        if (H.isRecursive()) {
            it1 = d1.directories.begin();
            it2 = d2.directories.begin();

            while (it1 != d1.directories.end()) {
                string tmp = *it1;
                auto search3 = d2.directories.find(*it1);

                // found same directory
                if (search3 != d2.directories.end()) {
                    const string tmp1 = dir1 + *it1;
                    const string tmp2 = dir2 + *it1;
                    DecideOutputTypes(tmp1, tmp2);
                } else {
                    cout << "Directory " << *it1 << " was not found in: " << dir2 << endl;
                }
                it1++;
            }
            // Will ignore directories not found in dir1 and report them to the user
            while (it2 != d2.directories.end()) {
                auto search4 = d1.directories.find(*it2);
                if (search4 == d1.directories.end()) {
                    cout << "Directory " << *it2 << " was not found in: " << dir1 << endl;
                }
                it2++;
            }
        }
    }
    // If not a directory we will just compare the files normally
    else {
        H.UpdateFiles();
        FileTypeHandler F(H);
        F.ChooseFileType();
    }
}