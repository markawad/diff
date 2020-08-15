#include "Directory.h"

Directory::Directory(FileHandler &h, const string &name) : H(h), name(name) {
    StoreFilesAndDirectories();
}

const string &Directory::getName() const {
    return name;
}

void Directory::setName(const string &name) {
    Directory::name = name;
}


void Directory::StoreFilesAndDirectories() {
    DIR *dp;
    struct dirent *ep;

    char *cstr = &name[0u];
    dp = opendir(cstr);

    if (dp != nullptr) {
        while ((ep = readdir(dp))) {
            // Adding only the Directoris/Files without a '.'
            if (ep->d_name[0] != '.') {
                string tmpName = name + "/" + ep->d_name;
                // Check to see if it is a directory or not.
                if (H.isDirectory(tmpName)) {
                    tmpName = ep->d_name;
                    tmpName += "/";
                    directories.insert(tmpName);
                } else {
                    files.insert(ep->d_name);
                }
            }
        }
    }
    ep = nullptr;
    delete dp;
    delete ep;
}
