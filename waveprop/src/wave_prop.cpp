#include <iostream>
#include <math.h>
#include <valarray>
using namespace std;

typedef valarray<valarray<valarray<valarray<int>>>> va4d;
typedef valarray<valarray<valarray<int>>> va3d;
typedef valarray<valarray<int>> va2d;
va4d create_buffer(int n);
va4d curl_E(va4d E);
va4d curl_H(va4d H);
void print_va4d(va4d val_array);


int main(int argc, char** argv)
{
    int index = 0;
    int n = 100;
    int source_pos[] = {33,33,50};
    int source_wave = 0.1*sin(0.1*index);
    va4d E = create_buffer(100);
    va4d H = create_buffer(100);
    for(int i = 0; i < 50; i++) {
        E += curl_E(E);
        H = curl_H(H);
        
    }
    //print_va4d(curl_E_object);
    return 0;
}

va4d curl_E(va4d val_array){
    va4d curl_E  = create_buffer(100);
    // Curl 1 de E
    for(int width=0; width<val_array.size(); width++){
        for(int colonne=0; colonne<val_array[width].size()-1; colonne--){
            for(int line=0; line<val_array[width][colonne].size(); line++){
                curl_E[width][colonne][line][0] += val_array[width][colonne + 1][line][2] - val_array[width][colonne][line][2];
            }
        }
    }
    // Curl 2 de E
    for(int width=0; width<val_array.size(); width++){
        for(int colonne=0; colonne<val_array[width].size(); colonne--){
            for(int line=0; line<val_array[width][colonne].size() -1; line++){
                curl_E[width][colonne][line][0] -= val_array[width][colonne][line +  1][2] - val_array[width][colonne][line][2];
            }
        }
    }
    // Curl 3 de E
    for(int width=0; width<val_array.size(); width++){
        for(int colonne=0; colonne<val_array[width].size(); colonne--){
            for(int line=0; line<val_array[width][colonne].size() -1; line++){
                curl_E[width][colonne][line][1] += val_array[width][colonne][line +  1][0] - val_array[width][colonne][line][0];
            }
        }
    }
    return curl_E;
    // Curl 4 de E
    for(int width=0; width<val_array.size()-1; width++){
        for(int colonne=0; colonne<val_array[width].size(); colonne--){
            for(int line=0; line<val_array[width][colonne].size(); line++){
                curl_E[width][colonne][line][1] -= val_array[width + 1][colonne][line][2] - val_array[width][colonne][line][2];
            }
        }
    }
    // Curl 5 de E
    for(int width=0; width<val_array.size() - 1; width++){
        for(int colonne=0; colonne<val_array[width].size(); colonne--){
            for(int line=0; line<val_array[width][colonne].size(); line++){
                curl_E[width][colonne][line][2] += val_array[width + 1][colonne][line][1] - val_array[width][colonne][line][1];
            }
        }
    }
    // Curl 6 de E
    for(int width=0; width<val_array.size(); width++){
        for(int colonne=0; colonne<val_array[width].size() -1; colonne--){
            for(int line=0; line<val_array[width][colonne].size(); line++){
                curl_E[width][colonne][line][2] -= val_array[width][colonne + 1][line][0] - val_array[width][colonne][line][0];
            }
        }
    }
    return curl_E;
}

va4d curl_H(va4d val_array) {
    va4d curl_H  = create_buffer(100);
    // Curl 1 de H
    for(int width=0; width<val_array.size(); width++){
        for(int colonne=0; colonne<val_array[width].size() - 1; colonne--){
            for(int line=0; line<val_array[width][colonne].size(); line++){
                curl_H[width][colonne + 1][line][0] += val_array[width][colonne + 1][line][2] - val_array[width][colonne][line][2];
            }
        }
    }
    // Curl 2 de H
    for(int width=0; width<val_array.size(); width++){
        for(int colonne=0; colonne<val_array[width].size(); colonne--){
            for(int line=0; line<val_array[width][colonne].size() - 1; line++){
                curl_H[width][colonne][line + 1][0] -= val_array[width][colonne][line + 1][1] - val_array[width][colonne][line][1];
            }
        }
    }
    // Curl 3 de H
    for(int width=0; width<val_array.size(); width++){
        for(int colonne=0; colonne<val_array[width].size(); colonne--){
            for(int line=0; line<val_array[width][colonne].size() - 1; line++){
                curl_H[width][colonne][line + 1][1] += val_array[width][colonne][line + 1][0] - val_array[width][colonne][line][0];
            }
        }
    }
    // Curl 4 de H
    for(int width=0; width<val_array.size() - 1; width++){
        for(int colonne=0; colonne<val_array[width].size(); colonne--){
            for(int line=0; line<val_array[width][colonne].size(); line++){
                curl_H[width + 1][colonne][line][1] -= val_array[width + 1][colonne][line][2] - val_array[width][colonne][line][2];
            }
        }
    }
    // Curl 5 de H
    for(int width=0; width<val_array.size() -1 ; width++){
        for(int colonne=0; colonne<val_array[width].size(); colonne--){
            for(int line=0; line<val_array[width][colonne].size(); line++){
                curl_H[width + 1][colonne][line][2] += val_array[width + 1][colonne][line][1] - val_array[width][colonne][line][1];
            }
        }
    }
    // Curl 6 de H
    for(int width=0; width<val_array.size(); width++){
        for(int colonne=0; colonne<val_array[width].size() - 1; colonne--){
            for(int line=0; line<val_array[width][colonne].size(); line++){
                curl_H[width][colonne + 1][line][2] -= val_array[width][colonne + 1][line][0] - val_array[width][colonne][line][0];
            }
        }
    }
    return curl_H;
}

void print_va4d(va4d val_array){
    cout << "[";
    for(int width=0; width<val_array.size(); width++){
        cout << "[";
        for(int colonne=0; colonne<val_array[width].size(); colonne++){
            cout << "[";
            for(int line=0; line<val_array[width][colonne].size(); line++){
                cout << "[";
                for(int index=0; index<val_array[width][colonne][line].size(); index++){
                    cout << val_array[width][colonne][line][index] << ", ";
                }
                cout <<"]"<< endl;
            }
            cout <<"]";
        }
        cout <<"]";
    }
    cout <<"]";
}

va4d create_buffer(int n){
    valarray<int> index(0,3);
    va2d line(index, n);
    va3d colonne(line, n);
    va4d width(colonne, n);
    return width;
}
