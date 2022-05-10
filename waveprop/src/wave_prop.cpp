#include <iostream>
#include <math.h>
#include <thread>
#include <mutex>
#include <valarray>
using namespace std;

typedef valarray<valarray<valarray<valarray<float>>>> va4d;
typedef valarray<valarray<valarray<float>>> va3d;
typedef valarray<valarray<float>> va2d;
va4d create_buffer(float value, int n);
va4d curl_E(va4d E);
va4d curl_H(va4d H);
void curl_E_1_2_3(va4d val_array, va4d curl_E);
void curl_E_4_5_6(va4d val_array, va4d curl_E);
void curl_H_1_2_3(va4d val_array, va4d curl_H);
void curl_H_4_5_6(va4d val_array, va4d curl_H);
void print_va4d(va4d val_array);
float source(int index);

std::mutex curl_E_mutex;
std::mutex curl_H_mutex;

int main(int argc, char** argv)
{
    int index = 0;
    int n = 100;
    int source_pos[] = {33,33,50};
    float source_wave = 0.1*sin(0.1*index);

    va4d E = create_buffer(0.0, n);
    va4d H = create_buffer(0.0, n);
    for(int i = 0; i < 50; i++) {
        cout << i << endl;
        va4d curl_E  = create_buffer(0.0, n);
        va4d curl_H = create_buffer(0.0, n);
        
        std::thread t1(curl_E_1_2_3, E, curl_E);
        std::thread t2(curl_E_4_5_6, E, curl_E);
        std::thread t3(curl_H_1_2_3, H, curl_H);
        std::thread t4(curl_H_4_5_6, H, curl_H);
        t1.join();
        t2.join();
        t3.join();
        t4.join();

        E += (curl_H) ;
        E[(int)(n/3)][(int)(n/3)][(int)(n/2)][0] +=  source(i);
        H -= (curl_E) ;   
    }
    return 0;
}

void curl_E_1_2_3(va4d val_array, va4d curl_E) {
    for(int width=0; width<val_array.size(); width++){
        for(int colonne=0; colonne<val_array[width].size()-1; colonne++){
            for(int line=0; line<val_array[width][colonne].size(); line++){
                std::unique_lock<std::mutex> lk(curl_E_mutex);
                curl_E[width][colonne][line][0] += val_array[width][colonne + 1][line][2] - val_array[width][colonne][line][2];
                lk.unlock();
            }
        }
    }
    // Curl 2 de E
    for(int width=0; width<val_array.size(); width++){
        for(int colonne=0; colonne<val_array[width].size(); colonne++){
            for(int line=0; line<val_array[width][colonne].size() -1; line++){
                std::unique_lock<std::mutex> lk(curl_E_mutex);
                curl_E[width][colonne][line][0] -= val_array[width][colonne][line +  1][2] - val_array[width][colonne][line][2];
                lk.unlock();
            }
        }
    }
    // Curl 3 de E
    for(int width=0; width<val_array.size(); width++){
        for(int colonne=0; colonne<val_array[width].size(); colonne++){
            for(int line=0; line<val_array[width][colonne].size() -1; line++){
                cout << line << endl;
                std::unique_lock<std::mutex> lk(curl_E_mutex);
                curl_E[width][colonne][line][1] += val_array[width][colonne][line +  1][0] - val_array[width][colonne][line][0];
                lk.unlock();
            }
        }
    }
}

void curl_E_4_5_6(va4d val_array, va4d curl_E){
    // Curl 4 de E
    for(int width=0; width<val_array.size()-1; width++){
        for(int colonne=0; colonne<val_array[width].size(); colonne++){
            for(int line=0; line<val_array[width][colonne].size(); line++){
                std::unique_lock<std::mutex> lk(curl_E_mutex);
                curl_E[width][colonne][line][1] -= val_array[width + 1][colonne][line][2] - val_array[width][colonne][line][2];
                lk.unlock();
            }
        }
    }
    // Curl 5 de E
    for(int width=0; width<val_array.size() - 1; width++){
        for(int colonne=0; colonne<val_array[width].size(); colonne++){
            for(int line=0; line<val_array[width][colonne].size(); line++){
                std::unique_lock<std::mutex> lk(curl_E_mutex);
                curl_E[width][colonne][line][2] += val_array[width + 1][colonne][line][1] - val_array[width][colonne][line][1];
                lk.unlock();
            }
        }
    }
    // Curl 6 de E
    for(int width=0; width<val_array.size(); width++){
        for(int colonne=0; colonne<val_array[width].size() -1; colonne++){
            for(int line=0; line<val_array[width][colonne].size(); line++){
                std::unique_lock<std::mutex> lk(curl_E_mutex);
                curl_E[width][colonne][line][2] -= val_array[width][colonne + 1][line][0] - val_array[width][colonne][line][0];
                lk.unlock();
            }
        }
    }
}

void curl_H_1_2_3(va4d val_array, va4d curl_H) {
    // Curl 1 de H
    for(int width=0; width<val_array.size(); width++){
        for(int colonne=0; colonne<val_array[width].size() - 1; colonne++){
            for(int line=0; line<val_array[width][colonne].size(); line++){
                std::unique_lock<std::mutex> lk(curl_H_mutex);
                curl_H[width][colonne + 1][line][0] += val_array[width][colonne + 1][line][2] - val_array[width][colonne][line][2];
                lk.unlock();
            }
        }
    }
    // Curl 2 de H
    for(int width=0; width<val_array.size(); width++){
        for(int colonne=0; colonne<val_array[width].size(); colonne++){
            for(int line=0; line<val_array[width][colonne].size() - 1; line++){
                std::unique_lock<std::mutex> lk(curl_H_mutex);
                curl_H[width][colonne][line + 1][0] -= val_array[width][colonne][line + 1][1] - val_array[width][colonne][line][1];
                lk.unlock();
            }
        }
    }
    // Curl 3 de H
    for(int width=0; width<val_array.size(); width++){
        for(int colonne=0; colonne<val_array[width].size(); colonne++){
            for(int line=0; line<val_array[width][colonne].size() - 1; line++){
                std::unique_lock<std::mutex> lk(curl_H_mutex);
                curl_H[width][colonne][line + 1][1] += val_array[width][colonne][line + 1][0] - val_array[width][colonne][line][0];
                lk.unlock();
            }
        }
    }
}

void curl_H_4_5_6(va4d val_array, va4d curl_H) {
    // Curl 4 de H
    for(int width=0; width<val_array.size() - 1; width++){
        for(int colonne=0; colonne<val_array[width].size(); colonne++){
            for(int line=0; line<val_array[width][colonne].size(); line++){
                std::unique_lock<std::mutex> lk(curl_H_mutex);
                curl_H[width + 1][colonne][line][1] -= val_array[width + 1][colonne][line][2] - val_array[width][colonne][line][2];
                lk.unlock();
            }
        }
    }
    // Curl 5 de H
    for(int width=0; width<val_array.size() -1 ; width++){
        for(int colonne=0; colonne<val_array[width].size(); colonne++){
            for(int line=0; line<val_array[width][colonne].size(); line++){
                std::unique_lock<std::mutex> lk(curl_H_mutex);
                curl_H[width + 1][colonne][line][2] += val_array[width + 1][colonne][line][1] - val_array[width][colonne][line][1];
                lk.unlock();
            }
        }
    }
    // Curl 6 de H
    for(int width=0; width<val_array.size(); width++){
        for(int colonne=0; colonne<val_array[width].size() - 1; colonne++){
            for(int line=0; line<val_array[width][colonne].size(); line++){
                std::unique_lock<std::mutex> lk(curl_H_mutex);
                curl_H[width][colonne + 1][line][2] -= val_array[width][colonne + 1][line][0] - val_array[width][colonne][line][0];
                lk.unlock();
            }
        }
    }
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
                    cout << val_array[width][colonne][line][index] << " ";
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