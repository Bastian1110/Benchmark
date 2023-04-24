#include <string>
#include <vector>
#include <fstream>
#include "json.hpp"
#include <iostream>
#include <unordered_map>
#include <typeinfo>
#include <chrono>

// for convenience
using json = nlohmann::json;


//Funcion que convierte un objeto carro en un string usado para describir el carro.
std::string jsontoString(json data, std::unordered_map<std::string,std::string>& check){
    //Inicializa variables necesarias para trabajar el string. El mapa es para guardar cambios a la llaves y que no se tengan
    //realizar mas de una vez.
    std::string str;
    std::string masterString;

    //Iteracion dentro de todos los elementos del objeto.
    for (auto& el : data.items()){
        str = el.key();
        std::string value = to_string(el.value());

        //Revisar si el elemento ya fue despojado de sus '_' y si no es el caso los reemplaza con ' '
        if(check.find(str) == check.end()){
            std::string str2 = str;
            std::replace(str2.begin(),str2.end(),'_',' ');
            check[str] = str2;
        }

        //Blacklist de elementos que no nos interesan, agregar elementos que no importan a este if
        if(str == "_id" || str == "precio"){

        }

        //Revisa si el dato se trata de un booleano, si es el caso revisa si es true y si es true agrega la 
        //key al masterstring, en el caso de ser false no hace nada
        else if(el.value().type() == json::value_t::boolean){
            bool val = el.value();
            if(val){
                masterString +=check[str] + " ";    
            }
        }

        //Revisa si el elemento es un number, de ser el caso agrega la key seguida del numero, para mantener
        //corelación en los datos
        else if(el.value().is_number()){
            masterString +=check[str] + value + " ";
        }

        //En caso de que no sea un numero o un bool solo agrega el valor al masterstring.
        else{
            masterString +=el.value();
            masterString +=" ";
        }
    }
    return masterString;


}



int main(){
    std::ifstream fake("fakedata.json");
    json data = json::parse(fake);

    //TIME
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    
    //std::cout<<data[0][1];

    //std::cout <<data[0]["marca"]<< '\n';
    std::vector<std::string> v1;
    std::unordered_map<std::string,std::string> check;
    for(auto& el : data.items()){
        std::string master = jsontoString(el.value(),check);
        //std::cout<<master<<"\n";
        v1.push_back(master);
    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout<< "Nanoseconds taken : " <<std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "\n";
    std::cout<<v1.size() << " Cars \n";
}

