#include <iostream> 
#include <string>
#include <vector>
#include <fstream>
#include <chrono>
#include <locale>
#include <algorithm>

using namespace std;

struct words{
    string text;
    int number;

    words(string t, int n = 0) : text(t), number(n) {}

    words() : text(""), number(0) {}

    void print(){
        cout << text << ": " << number << endl;
    }

    friend ostream& operator<<(ostream& out, const words& w){ 
        out << w.text << ": " << w.number;
        return out;
    }
};

void sort(vector<words>& lista){
    for(int i = 0; i < lista.size() - 1; i++){
        for(int j = 0; j < lista.size() - 1 - i; j++){
            if(lista[j].number < lista[j+1].number){
                words temp = lista[j];
                lista[j] = lista[j+1];
                lista[j+1] = temp;
            }
        }
    }
}

void print(string w1, words w2){
    cout<<w1<<", "<< w2.text<<endl;
}


bool comp(string slowo, words second){
    string second_text;
    second_text = second.text;
    if(slowo == second_text){
        return true;
    }
    else{
        return false;
    }
}

vector<words> word_count(const vector<string>& lista){
    bool is_inside=false;

    vector<words> result;

    words init(lista[0]);
    init.number=1;

    result.push_back(init);

    for(int i =1; i<lista.size(); i++){

        for(int j=0; j<result.size();j++){

            if(comp(lista[i],result[j])){
                //finding one in word_list
                result[j].number++;
                is_inside = true;
                break;
            }
            else{
                is_inside = false;
            }
        }

        if (is_inside==false){
            words temp(lista[i]);
            temp.number = 1;
            result.push_back(temp);
            is_inside = true;
        }
    }

    return result;
}

vector<string> list_prepare(const string& fileName){
    vector<string> lista;
    ifstream file;

    file.open(fileName);
    string temp;

    while(file >> temp){
        temp.erase(remove_if(temp.begin(), temp.end(),
            [](char c) { return c == ',' || c == '.' || c == '?'; }), temp.end());

        temp[0] = tolower(temp[0]);
        lista.push_back(temp);
    }

    file.close();
    return lista;
}

int main(){
    vector<std::string> lista = list_prepare("text_file.txt");
    vector<words> word_list = word_count(lista);

    ofstream plik("analiza.txt");

    sort(word_list);

    for(auto& it: word_list){
        plik << it << endl;
    }
    return 0;
}
