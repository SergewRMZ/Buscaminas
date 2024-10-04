#ifndef FILE_SERVICE
#define FILE_SERVICE

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;
class FileService {
  private:
    string filename_easy;
    string filename_medium;
    string filename_hard;

  public:
    FileService (const string &easy, const string &medium, const string &hard)
      : filename_easy(easy), filename_medium(medium), filename_hard(hard) {} 

    void writeRecord (string difficulty, double time);
    vector<string> getRecords(string difficulty);
};

#endif