#include <iostream>
#include <cstdio>
#include <array>
#include <utility>
#include <string>
#include <functional>
#include <random>
#include <ctime>
#include <cstdlib>

#define SIZE 40
#define CELL (char)42    //219, 249, 254
#define DEBUG_MODE 0
#define SPEED 50

#if DEBUG_MODE
#include <chrono>
//Timing is to time one display cycle
//one display cycle = 1 generation of cells
class Timing {
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
    std::chrono::time_point<std::chrono::high_resolution_clock> end;
    std::chrono::duration<float> duration;
public:
    Timing() {
        start = std::chrono::high_resolution_clock::now();
    }
    
    ~Timing() {
        end = std::chrono::high_resolution_clock::now();
        duration = end - start;
        std::cout << duration.count() << std::endl;
    }
};
#endif

std::pair<std::array<std::array<bool, SIZE>, SIZE>, std::array<std::array<bool, SIZE>, SIZE> > CellularAutomata;
unsigned long long generation = 0ll;

void SetGen1();
void GenInFirst();
void GenInSecond();
void display(const std::array<std::array<bool, SIZE>, SIZE>& CellularAutomata);

int main() {
    SetGen1();
    bool AutomataState = true; //true = CellularAutomata.first, false = CellularAutomata.second
    
    while(/*RUNNING*/generation <= 100) {
        
        if (AutomataState) {
            GenInFirst();
            display(CellularAutomata.second);
            AutomataState = false;
        }
        
        else {
            GenInSecond();
            display(CellularAutomata.first);
            AutomataState = true;
        }
    }
}

void SetGen1() {
    // CellularAutomata.first[2][23] = true;
    // Gosper Glider F
    // {
    CellularAutomata.first[1][25] = true;
    CellularAutomata.first[2][23] = true;
    CellularAutomata.first[2][25] = true;
    CellularAutomata.first[3][13] = true;
    CellularAutomata.first[3][14] = true;
    CellularAutomata.first[3][21] = true;
    CellularAutomata.first[3][22] = true;
    CellularAutomata.first[3][35] = true;
    CellularAutomata.first[3][36] = true;
    CellularAutomata.first[4][12] = true;
    CellularAutomata.first[4][16] = true;
    CellularAutomata.first[4][21] = true;
    CellularAutomata.first[4][22] = true;
    CellularAutomata.first[4][35] = true;
    CellularAutomata.first[4][36] = true;
    CellularAutomata.first[5][1]  = true;
    CellularAutomata.first[5][2]  = true;
    CellularAutomata.first[5][11] = true;
    CellularAutomata.first[5][17] = true;
    CellularAutomata.first[5][21] = true;
    CellularAutomata.first[5][22] = true;
    CellularAutomata.first[6][1]  = true;
    CellularAutomata.first[6][2]  = true;
    CellularAutomata.first[6][11] = true;
    CellularAutomata.first[6][15] = true;
    CellularAutomata.first[6][17] = true;
    CellularAutomata.first[6][18] = true;
    CellularAutomata.first[6][23] = true;
    CellularAutomata.first[6][25] = true;
    CellularAutomata.first[7][11] = true;
    CellularAutomata.first[7][17] = true;
    CellularAutomata.first[7][25] = true;
    CellularAutomata.first[8][12] = true;
    CellularAutomata.first[8][16] = true;
    CellularAutomata.first[9][13] = true;
    CellularAutomata.first[9][14] = true;
    // }
    
    //Spinner
    // {
    //     CellularAutomata.first[4][23] = true;
    //     CellularAutomata.first[5][23] = true;
    //     CellularAutomata.first[6][23] = true;
    // }
    
    //Random
    {
        // auto gen = std::bind(std::uniform_int_distribution<>(0, 1), std::default_random_engine());
        // for (int x = 1; x < SIZE - 1; x++) {
        //     for (int y = 1; y < SIZE - 1; y++) {
        //         if (gen())
        //             CellularAutomata.first[x][y] = true;
        //     }
        // }
        // using namespace std;
        // srand((unsigned)time(0));
        // for (int x = 1; x < SIZE - 1; x++) {
        //     for (int y = 1; y < SIZE - 1; y++) {
        //         if (rand() % 2)
        //             CellularAutomata.first[x][y] = true;
        //     }
        // }
    }
}

void GenInFirst() {
    int neighbours;
    for (int x = 1; x < SIZE - 1; x++) {
        for (int y = 1; y < SIZE - 1; y++) {
            neighbours = 0;
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    neighbours += CellularAutomata.first[x + i][y + j];
                }
            }
            
            neighbours -= CellularAutomata.first[x][y];
            
            if (CellularAutomata.first[x][y] && neighbours > 3)    //Death By Overpopulation
                CellularAutomata.second[x][y] = false;
            else if (CellularAutomata.first[x][y] && neighbours < 2)   //Death By Loneliness
                CellularAutomata.second[x][y] = false;
            else if (!CellularAutomata.first[x][y] && neighbours == 3) //Birth
                CellularAutomata.second[x][y] = true;
            else                                                    //Stasis
                CellularAutomata.second[x][y] = CellularAutomata.first[x][y];
        }
    }
}

void GenInSecond() {
    int neighbours;
    for (int x = 1; x < SIZE - 1; x++) {
        for (int y = 1; y < SIZE - 1; y++) {
            neighbours = 0;
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    neighbours += CellularAutomata.second[x + i][y + j];
                }
            }
            
            neighbours -= CellularAutomata.second[x][y];
            
            if (CellularAutomata.second[x][y] && neighbours > 3)    //Death By Overpopulation
                CellularAutomata.first[x][y] = false;
            else if (CellularAutomata.second[x][y] && neighbours < 2)   //Death By Loneliness
                CellularAutomata.first[x][y] = false;
            else if (!CellularAutomata.second[x][y] && neighbours == 3) //Birth
                CellularAutomata.first[x][y] = true;
            else                                                    //Stasis
                CellularAutomata.first[x][y] = CellularAutomata.second[x][y];
        }
    }
}

void display(const std::array<std::array<bool, SIZE>, SIZE>& CellularAutomata) {
    
#if DEBUG_MODE
    //Timing object declared in the beginning to time the whole function
    Timing time;
#endif
    
    //    std::string output = "";
    
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", (CellularAutomata[i][j] ? CELL : 32));
            //            output += CellularAutomata[i][j] ? CELL : (char)32;
        }
        
        printf("\n");
        //        output += '\n';
    }
    
    //    std::cout << '\r' << output;
    // std::cout << generation++;
    printf("%llu\n", generation++);
}

/*
 Gosper Glider Gun
 0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40
 0   0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 1   0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  1  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 2   0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  1  0  1  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 3   0  0  0  0  0  0  0  0  0  0  0  0  0  1  1  0  0  0  0  0  0  1  1  0  0  0  0  0  0  0  0  0  0  0  0  1  1  0  0  0  0
 4   0  0  0  0  0  0  0  0  0  0  0  0  1  0  0  0  1  0  0  0  0  1  1  0  0  0  0  0  0  0  0  0  0  0  0  1  1  0  0  0  0
 5   0  1  1  0  0  0  0  0  0  0  0  1  0  0  0  0  0  1  0  0  0  1  1  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 6   0  1  1  0  0  0  0  0  0  0  0  1  0  0  0  1  0  1  1  0  0  0  0  1  0  1  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 7   0  0  0  0  0  0  0  0  0  0  0  1  0  0  0  0  0  1  0  0  0  0  0  0  0  1  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 8   0  0  0  0  0  0  0  0  0  0  0  0  1  0  0  0  1  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 9   0  0  0  0  0  0  0  0  0  0  0  0  0  1  1  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 10  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 11  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 12  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 13  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 14  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 15  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 16  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 17  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 18  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 19  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 20  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 21  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 22  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 23  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 24  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 25  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 26  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 27  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 28  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 29  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 30  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 
 
 Diehard
 17, 18
 17, 19
 18, 19
 18, 23
 18, 24
 18, 25
 16, 24
 */
