#include <iostream>

struct Vertex{
    float x;
    float y;
    float z;
};

void createTriangle(Vertex pointMin, Vertex pointMax){

    float p1[3] = {pointMin.x, pointMin.y, pointMin.z};
    float p2[3] = {pointMax.x, pointMax.y, pointMax.z};
    float p3[3] = {pointMax.x, pointMin.y, pointMin.z};
    float p4[3] = {pointMin.x, pointMax.y, pointMin.z};
    float p5[3] = {pointMin.x, pointMin.y, pointMax.z};
    float p6[3] = {pointMin.x, pointMax.y, pointMax.z};
    float p7[3] = {pointMax.x, pointMin.y, pointMax.z};
    float p8[3] = {pointMax.x, pointMax.y, pointMin.z};
float *** vecTriangle = new float**[12];
for (int i = 0; i < 12; i++){
    vecTriangle[i] = new float *[3];
    for (int j = 0; j < 3; j++){
        vecTriangle[i][j] = new float[3];
    }
}



//vecTriangle = {
//        {p1, p4, p8},
//        {p1, p3, p8},
//        {p1, p5, p7},
//        {p1, p3, p7},
//        {p1, p5, p6},
//        {p1, p4, p6},
//        {p5, p6, p2},
//        {p5, p7, p2},
//        {p6, p4, p8},
//        {p6, p2, p8},
//        {p3, p7, p2},
//        {p3, p8, p2}
//}

};

float* findVector(Vertex point1, Vertex point2){
    float *vector  = new float[3];
    vector[0] = point2.x - point1.x;
    vector[1] = point2.y - point1.y;
    vector[2] = point2.z - point1.z;
    return &vector[0];
}

int main() {
    //Vertex *vertex = new Vertex[sizeof(vertex)];
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
