//
//  main.cpp
//  isoLine
//
//  Created by kokofan on 10/1/19.
//  Copyright © 2019 koko Fan. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <unordered_map>
#include <math.h>
#include <numeric>


static float ioscontour = 81.5;

// Read File
std::vector<unsigned char> readFile(std::string filePath)
{
    // Open File
    std::ifstream infile(filePath, std::ios::in | std::ios::binary);
    
    // Print error if the file cannot be opened
    if(!infile)
    {
        std::cerr << "Cannot open the File: " << filePath << std::endl;
    }
    
    // Read all the data into a unsigned char buffer
    std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(infile), {});

    std::cout << "Read " << buffer.size() << " numbers" << std::endl;
    
    infile.close();
    return buffer;
}


// Compare the value with the ioscontour.
// If larger, return 1; else return 0.
int compIsocontour(int num)
{
    if(num >= ioscontour)
        return 1;
    return 0;
}


// Find the vertexs and edges based on the vertex and edge in each cell
void findVertexEdges(std::vector<std::vector<double>> &vertex, std::vector<std::vector<double>> &vertexs, std::vector<std::vector<int>> &edges)
{
    
    //std::cout << "This is a cell\n";
    // Find the edge in two vertexs.
    if(vertex.size() == 2)
    {
        // Find these two vertexs in vector vertexs
        auto it1 = std::find(vertexs.begin(), vertexs.end(), vertex[0]);
        auto it2 = std::find(vertexs.begin(), vertexs.end(), vertex[1]);
        
        //std::cout << "vertex[0]: " << vertex[0][0] << ", " << vertex[0][1] << ", " << vertex[0][2] << "\n";
        //std::cout << "vertex[1]: " << vertex[1][0] << ", " << vertex[1][1] << ", " << vertex[1][2] << "\n";
        
        // These two vertexs have existed in vector vertexs
        if (it1 != vertexs.end() && it2 != vertexs.end())
        {
            int index1 = int(it1 - vertexs.begin()) + 1;
            int index2 = int(it2 - vertexs.begin()) + 1;
            //std::cout << "edges1: " << int(it1 - vertexs.begin() + 1) << ", " << int(it2 - vertexs.begin() + 1) << "\n";
            edges.push_back({index1, index2});
        }
        
        // The first vertex existed in vector vertexs
        else if(it1 != vertexs.end())
        {
            int index = int(it1 - vertexs.begin()) + 1;
            vertexs.push_back(vertex[1]);
            //std::cout << "edges2: " << int(it1 - vertexs.begin() + 1) << ", " << int(vertexs.size()) << "\n";
            edges.push_back({index, int(vertexs.size())});
        }
        
        // The second vertex existed in vector vertexs
        else if(it2 != vertexs.end())
        {
            int index = int(it2 - vertexs.begin()) + 1;
            vertexs.push_back(vertex[0]);
            //std::cout << "edges3: " << index << ", " << int(vertexs.size()) << "\n";
            edges.push_back({int(vertexs.size()), index});
        }
        
        // No vertex existed in vector vertexs
        else
        {
            vertexs.push_back(vertex[0]);
            vertexs.push_back(vertex[1]);
            //std::cout << "edges4: " << int(vertexs.size()) - 1 << ", " << int(vertexs.size()) << "\n";
            edges.push_back({int(vertexs.size()) - 1, int(vertexs.size())});
        }
    }
    
    else
    {
         std::cerr << "The length of vertex array isn't 2" << std::endl;
    }
    
}





//Marching squeue
void marchingSqueue(std::vector<unsigned char> &buffer, int M, int N)
{
    std::vector<std::vector<double>> vertexs;
    std::vector<std::vector<int>> edges;
    //int count = 1;
    
    // M is row of image, and N is column of image
    for(int i = 0; i < M-1; i++)
    {
        for(int j = 0; j < N-1; j++)
        {
            // Cell for each i,j
            std::vector<double> cell = {double(buffer[i * N + j]), double(buffer[i * N + (j+1)]), double(buffer[(i+1) * N + (j+1)]), double(buffer[(i+1) * N + j])};
            std::vector<int> signs;
            int sum = 0;
            
            // Find signs of vertexs in the cell
            for(auto c: cell)
            {
                int sign = (c > ioscontour)? 1: 0;
                signs.push_back(sign);
                sum += sign;
            }
            
           std::vector<std::vector<double>> vertex;

            // If all the vertexs in the cell are smaller or larger than ioscontour, then skip the cell
            if(sum == 0 || sum == 4)
                continue;
            
//            std::cout << "i: " << i << " j: " << j << "\n";
//            std::cout << "cell: " << cell[0] << ", " << cell[1] << ", " << cell[2] << ", " << cell[3] << "\n";
            
            // The edge between cell[0] and cell[1] with different signs
            if(signs[0] != signs[1])
            {
                double x = (abs(cell[0] - ioscontour)*(j+1) + abs(cell[1] - ioscontour)*j)/abs(cell[0] - cell[1]);
                vertex.push_back({x, double(i), 0});
                //std::cout << "signs[0] != signs[1]: " << float(i) << " " << y << "\n";
            }
            // The edge between cell[2] and cell[3] with different signs
            if(signs[2] != signs[3])
            {
                double x = (abs(cell[2] - ioscontour)*j + abs(cell[3] - ioscontour)*(j+1))/abs(cell[2] - cell[3]);
                vertex.push_back({x, double(i+1), 0});
                //std::cout << "The value of y is: " << abs(cell[0] - ioscontour) << ", " << abs(cell[1] - ioscontour) << ", " << abs(cell[0] - cell[1]) << "\n";
                //std::cout << "signs[2] != signs[3]: " << float(i + 1) << " " << y << "\n";
            }
            // The edge between cell[0] and cell[3] with different signs
            if(signs[0] != signs[3])
            {
                double y = (abs(cell[0] - ioscontour)*(i+1) + abs(cell[3] - ioscontour)*i)/abs(cell[0] - cell[3]);
                vertex.push_back({double(j), y, 0});
                //std::cout << "signs[0] != signs[3]: " << x << " " << float(j) << "\n";
            }
            // The edge between cell[1] and cell[2] with different signs
            if(signs[1] != signs[2])
            {
                double y = (abs(cell[1] - ioscontour)*(i+1) + abs(cell[2] - ioscontour)*i)/abs(cell[1] - cell[2]);
                vertex.push_back({double(j+1), y, 0});
                //std::cout << "signs[1] != signs[2]: " << x << " " << float(j + 1) << "\n";
            }
            
            // For cells which have two vertexs.
            if(vertex.size() == 2)
            {
                findVertexEdges(vertex, vertexs, edges);
            }
            
            // For cells which have four vertexs.
            else
            {
                //std::cout << "This is for four cell\n";
                // Ambiguity solution
                float f = std::accumulate(cell.begin(), cell.end(), 0)/cell.size();
                if(f < ioscontour)
                {
                    if(signs[0] == 1 && signs[2] == 1)
                    {
                        std::vector<std::vector<double>> vertex1 = {vertex[0], vertex[2]};
                        findVertexEdges(vertex1, vertexs, edges);
                        std::vector<std::vector<double>> vertex2 = {vertex[1], vertex[3]};
                        findVertexEdges(vertex2, vertexs, edges);
                    }
                    else
                    {
                        std::vector<std::vector<double>> vertex1 = {vertex[0], vertex[3]};
                        findVertexEdges(vertex1, vertexs, edges);
                        std::vector<std::vector<double>> vertex2 = {vertex[1], vertex[2]};
                        findVertexEdges(vertex2, vertexs, edges);
                    }
                }
                else
                {
                    if(signs[0] == 1 && signs[2] == 1)
                    {
                        std::vector<std::vector<double>> vertex1 = {vertex[0], vertex[3]};
                        findVertexEdges(vertex1, vertexs, edges);
                        std::vector<std::vector<double>> vertex2 = {vertex[1], vertex[2]};
                        findVertexEdges(vertex2, vertexs, edges);
                    }
                    else
                    {
                        std::vector<std::vector<double>> vertex1 = {vertex[0], vertex[2]};
                        findVertexEdges(vertex1, vertexs, edges);
                        std::vector<std::vector<double>> vertex2 = {vertex[1], vertex[3]};
                        findVertexEdges(vertex2, vertexs, edges);
                    }
                }
            }
        }
    }
    
    for(auto v: vertexs)
    {
        std::cout << "v ";
        for (auto a: v)
        {
            std::cout << a << " ";
        }
        std::cout << "\n";
    }

    for(auto e: edges)
    {
        std::cout << "l ";
        for (auto b: e)
        {
            std::cout << b << " ";
        }
        std::cout << "\n";
    }
}




int main(int argc, const char * argv[]) {

    std::string filePath = "/Users/kokofan/Documents/Contour_Tree/brain_scan_256_256_unsigned_char.raw";

    std::vector<unsigned char> buffer = readFile(filePath);
    
    marchingSqueue(buffer, 256, 256);
    
    buffer.clear();

    return 0;
}
