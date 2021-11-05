//
//  RBT.cpp
//  C++ code
//


#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <limits.h>
#include <map>


class RBT;

class Rect{
    public:
        friend class RBT;
        int lowX, lowY, hiX, hiY;
        Rect(): lowX(0), lowY(0), hiX(0), hiY(0){}
        Rect(int x1, int y1, int x2, int y2): lowX(x1), lowY(y1), hiX(x2), hiY(y2){}


};


namespace std
{
    template<> struct less<Rect*>
    {
       bool operator() (const Rect* ptrKey1, const Rect* ptrKey2) const
       {
            if(ptrKey1->lowX == ptrKey2->lowX){
                if(ptrKey1->hiX == ptrKey2->hiX){
                    if(ptrKey1->lowY == ptrKey2->lowY){
                        //Same Rectangle will be stored in leftchild!!
                        if(ptrKey1->hiX == ptrKey2->hiX){
                            return true;
                        }
                        else if(ptrKey1->hiX < ptrKey2->hiX)
                            return true;
                        else
                            return false;
                    }
                    else if (ptrKey1->lowY < ptrKey2->lowY)
                        return true;
                    else
                        return false;
                }
                else if(ptrKey1->hiX < ptrKey2->hiX)
                    return true;
                else
                    return false;
            }
            else if(ptrKey1->lowX < ptrKey2->lowX)
                return true;
            else
                return false;
       }
    };


}

class RBT{
    private:
        std::map<Rect*, std::string> intervalTree;

    public:
        RBT(){};
        void InsertRBT(Rect* key, std::string str);
        void DeleteRBT(Rect* key);
        void SmallestArea(int x, int y, std::ofstream& output);
        void SearchAll(Rect* key, std::ofstream& output);
        void OverlapDetect(Rect* key, std::ofstream& output);
        bool IsOverlap(Rect* key1, Rect* key2);
        bool IsViolate(Rect* key1, Rect* key2);

        bool IsSameRect(Rect* key1, Rect* key2);
        int CalArea(Rect* key);
        bool IsSameLowLeftCorner(int x, int y, Rect* key);


};

void RBT::InsertRBT(Rect* key, std::string element){

    intervalTree.insert(std::pair<Rect*, std::string>(key, element));

}


void RBT::DeleteRBT(Rect* key) {
    for (auto it = intervalTree.cbegin(), next_it = it; it != intervalTree.cend(); it = next_it) {
        ++next_it;
        if (IsSameRect(key, it->first)) {
            intervalTree.erase(it);
        }
    }

}

bool RBT::IsOverlap(Rect* key1, Rect* key2){
    if ((key1->lowX >= key2->lowX) && 
        (key1->lowY >= key2->lowY) && 
        (key1->hiX <= key2->hiX) && 
        (key1->hiY <= key2->hiY))
        return true;
    else 
        return false;
}
bool RBT::IsViolate(Rect* key1, Rect* key2){
    if ((key1->lowX - key2->lowX)>=20 && 
        (key1->lowY - key2->lowY)>=20 && 
        (key2->hiX - key1->hiX)>=20 && 
        (key2->hiY - key1->hiY)>=20)
        return false;
    else 
        return true;

}

void RBT::OverlapDetect(Rect* key, std::ofstream& output){
    
    std::map<int, std::string> overlapMap;

    for (const auto &p : intervalTree) {
        if (IsOverlap(key, p.first)){
            if (IsViolate(key, p.first)){
                std::string parseString = p.second;
                parseString.erase(0,1);
                int id = stoi(parseString);
                overlapMap.insert(std::pair<int, std::string>(id," violate"));
            }
            else{
                std::string parseString = p.second;
                parseString.erase(0,1);
                int id = stoi(parseString);
                overlapMap.insert(std::pair<int, std::string>(id," "));
            }
        }
    }

    for (const auto &p : overlapMap){
        output << "r" << p.first;
        if(p.second != " ")
            output << p.second << std::endl;
        else{
            output << std::endl;
        }
    }
}

bool RBT::IsSameRect(Rect* key1, Rect* key2) {
    if ((key1->lowX == key2->lowX) && 
        (key1->lowY == key2->lowY) && 
        (key1->hiX == key2->hiX) && 
        (key1->hiY == key2->hiY))
        return true;
    else 
        return false;
}

void RBT::SearchAll(Rect* key, std::ofstream& output){

    std::map<int, std::string> searchMap;

    for (const auto &p : intervalTree) {
        if (IsSameRect(key, p.first)){
            std::string parseString = p.second;
            parseString.erase(0,1);
            int id = stoi(parseString);
            searchMap.insert(std::pair<int, std::string>(id,""));
        }                                      
    }

    for (const auto &p : searchMap){
        output << "r" << p.first << std::endl;
    }


}

bool RBT::IsSameLowLeftCorner(int x, int y, Rect* key) {
    if ((x == key->lowX) && 
        (y == key->lowY))
        return true;
    else 
        return false;
}
int RBT::CalArea(Rect* key){
    return ( key->hiX - key->lowX ) * ( key->hiY - key->lowY );
}

void RBT::SmallestArea(int x, int y, std::ofstream& output){
    
    std::map<int, std::string> smallestAreaMap;
    int minArea = INT_MAX;

    for (const auto &p : intervalTree) {
        if (IsSameLowLeftCorner(x, y, p.first)){
            int area = CalArea(p.first);
            if (area <= minArea){
                if (area < minArea){
                    minArea = area;
                    smallestAreaMap.clear();
                }
                std::string parseString = p.second;
                parseString.erase(0,1);
                int id = stoi(parseString);
                smallestAreaMap.insert(std::pair<int, std::string>(id,""));
            }
        }                             
    }

    for (const auto &p : smallestAreaMap)
        output << "r" << p.first << std::endl;
}

int main(int argc, char**argv) {
    // Setting Usage
    if ( argc < 3 || argc > 3 ){
        std::cout << "Warning!!" << std::endl;
        std::cout << "[Usage]: ./Lab1 input.txt output.txt" << std::endl;
        return 1;
    }
    
    // Input Output file
    std::ifstream inputFile;
    inputFile.open(std::string(argv[1]));
    std::ofstream outputFile;
    outputFile.open(std::string(argv[2]));

    // Building Interval Tree
    RBT intervalTree;

    std::string line;
    while (std::getline(inputFile, line) ){
        std::stringstream buffer(line);
        std::string operation;
        buffer >> operation;
        
        std::string idx;
        int lowX, lowY, highX, highY;
        if (operation == "I"){
            buffer >> idx >> lowX >> lowY >> highX >> highY;
            Rect* r = new Rect(lowX, lowY, highX, highY);
            
            intervalTree.InsertRBT(r, idx);
        }
        else if (operation == "D"){
            buffer >> lowX >> lowY >> highX >> highY;
            Rect* r = new Rect(lowX, lowY, highX, highY);
            
            intervalTree.DeleteRBT(r);
        }
        else if (operation == "O"){
            buffer >> lowX >> lowY >> highX >> highY;
            Rect* r = new Rect(lowX, lowY, highX, highY);
            
            outputFile << "O" << std::endl;
            intervalTree.OverlapDetect(r, outputFile);
        }
        else if (operation == "S"){
            buffer >> lowX >> lowY >> highX >> highY;
            Rect* r = new Rect(lowX, lowY, highX, highY);
            
            outputFile << "S" << std::endl;
            intervalTree.SearchAll(r, outputFile);
        }
        else if (operation == "A"){
            buffer >> lowX >> lowY;
            
            outputFile << "A" << std::endl;
            intervalTree.SmallestArea(lowX, lowY, outputFile);
        }
    }
    outputFile.close();
    
    return 0;


}