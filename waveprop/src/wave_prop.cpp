#include <iostream>
#include <math.h>
#include <valarray>
using namespace std;

typedef valarray<valarray<valarray<valarray<float>>>> va4d;
typedef valarray<valarray<valarray<float>>> va3d;
typedef valarray<valarray<float>> va2d;
va4d create_buffer(float value, int n);
va4d curl_E(va4d E);
va4d curl_H(va4d H);
void print_va4d(va4d val_array);
float source(int index);

int main(int argc, char** argv)
{
    int index = 0;
    int n = 100;
    int source_pos[] = {33,33,50};
    int source_wave = 0.1*sin(0.1*index);
    va4d E = create_buffer(0.0, 100);
    va4d H = create_buffer(0.0, 100);
    for(int i = 0; i < 700; i++) {
        cout << i << endl;
        E += (curl_H(H)) * create_buffer(0.1, n);
        E[(int)(n/3)][(int)(n/3)][(int)(n/2)][0] +=  source(i);
        H -= (curl_E(E)) * create_buffer(0.1, n);
    }
    print_va4d(E);
    return 0;
}

va4d curl_E(va4d val_array){
    va4d curl_E  = create_buffer(0,0, 100);
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
    va4d curl_H  = create_buffer(0, 100);
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

va4d create_buffer(float value, int n){
    valarray<float> index(value,3);
    va2d line(index, n);
    va3d colonne(line, n);
    va4d width(colonne, n);
    return width;
}

float source(int index) {
    return 0.1*sin(0.1 * index);
}