#include "./presentation/Server.hpp"
#include <nlohmann/json.hpp>

int main () {
  Server server(5000);
  return 0;
}

// #include <iostream>
// #include <nlohmann/json.hpp>

// using namespace std;
// using json = nlohmann::json;

// int main() {
//     // Crear un objeto JSON
//     json j;
//     j["nombre"] = "Serge";
//     j["edad"] = 21;
//     j["ciudad"] = "Ciudad de México";

//     // Imprimir el objeto JSON
//     cout << "Objeto JSON: " << j.dump(4) << endl; // dump(4) para formato legible

//     // Analizar el objeto JSON
//     string jsonString = R"({"nombre":"Maria","edad":25,"ciudad":"Barcelona"})";
//     json parsedJson = json::parse(jsonString);

//     // Imprimir los valores analizados
//     cout << "Nombre: " << parsedJson["nombre"] << endl;
//     cout << "Edad: " << parsedJson["edad"] << endl;
//     cout << "Ciudad: " << parsedJson["ciudad"] << endl;

//     return 0;
// }
