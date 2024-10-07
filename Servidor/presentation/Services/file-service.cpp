#include "file-service.hpp"
#include <sstream>
#include <filesystem>

void FileService :: writeRecord (string difficulty, double time) {
  string filename;
  cout << "Registrando record: " << time << endl;
  if (difficulty == "easy") filename = filename_easy;
  else if (difficulty == "medium") filename = filename_medium;
  else if (difficulty == "hard") filename = filename_hard;
  vector<double> records;

  ifstream inFile(filename);
  if (inFile.is_open()) {
    string line;
    while (getline(inFile, line)) {
        double recordTime;
        istringstream iss(line);
        if (iss >> recordTime) { // Lee el tiempo del registro
            records.push_back(recordTime);
        }
    }
    inFile.close();
  }

  records.push_back(time);
  sort(records.begin(), records.end());

  ofstream outFile (filename);
  if (outFile.is_open()) {
    for (size_t i = 0; i < min(records.size(), size_t(10)); i++) {
      outFile << records[i] << "\n";
    }

    outFile.close();
  }
}

vector<string> FileService :: getRecords (string difficulty) {
  string filename;
  vector<string> records;

  if (difficulty == "easy") filename = filename_easy;
  else if (difficulty == "medium") filename = filename_medium;
  else if (difficulty == "hard") filename = filename_hard;

  if (!std::filesystem::exists(filename)) {
    cerr << "El archivo no existe: " << filename << endl;
    return records;
  }

  ifstream inFile(filename);
  if (!inFile.is_open()) {
    cerr << "Error al abrir el archivo para leer." << endl;
    return records;
  }

  string line;
  while (getline(inFile, line)) {
    records.push_back(line);
  }

  inFile.close();
  return records;
}
