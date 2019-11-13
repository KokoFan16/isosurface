# Contour_Tree
Extract contours in 2D and 3D image

### Marching squeue

    To find all the points that have a given height c, we have to solve the implicit equation f(x,y)=c. 
    Such a function determines the isolines or contours of f for the value c.
    
    Here is same steps:
    1. Sample f(x,y) on a regular grid yielding samples {f{ij}(x,y)}
    2. These samples can be greater than, less than, or equal to c.
    3. Consider four samples f{ij}(x,y), f{i+1,j}(x,y), f{i+1,j+1}(x,y), f{i,j+1}(x,y) 
    4. These samples correspond to the corners of a cell
    5. Color the corners by whether than exceed or are less than the contour value c
    
    There are 16 cases:
![marchingsqueue](https://github.com/KokoFan16/Contour_Tree/blob/master/image/16cases.png)
    
For machingSquere.cpp, the ```input``` file is a 2D image of .raw format, and the ```output``` file a object file.
    
    Here is an example of obj file:
    v 161.25 51 0 
    v 162 50.25 0 
    v 162.065 51 0 
    v 160.722 52 0 
    v 161 51.0625 0 
    v 162.212 52 0 
    ...
    l 1 2 
    l 3 2 
    l 4 5 
    l 1 5 
    l 3 6 
    l 4 7 
    l 6 8 
    l 9 10 
    l 11 10 
    ...

    Here is the result:
![marchingsqueue](https://github.com/KokoFan16/Contour_Tree/blob/master/image/square.png)

### Marching cube

    Marching cube is very similar with marching square. Just for 3D image, we should use faces instead of lines. That is, we should find isosurface in the image instead of isolines. 
    A face tipically is a triangle with three vertex. 
    Same with marching square, we should color the corners by whether than exceed or are less than the contour value c for each cube. 
    In total, there are 256 cases. But we can just consider 15 unique cases.
    Here are the 15 cases.
![marchingcube](https://github.com/KokoFan16/Contour_Tree/blob/master/image/cubecases.png)

    Here is an example of obj file:
    v 0.0588235 -0.176471 -0.939373 
    v 0.0535294 -0.176471 -0.937255 
    v 0.0588235 -0.180392 -0.937255 
    v 0.0634271 -0.176471 -0.937255 
    v 0.0588235 -0.170242 -0.937255 
    v 0.0666667 -0.16902 -0.937255 
    v 0.0666667 -0.168627 -0.937329 
    ...
    vn 0 0 1 
    vn 1 0 9.32466e-17 
    vn 0 1 -4.78114e-17 
    vn -1 0 4.66233e-17 
    vn 0 -1 -4.78114e-17 
    vn 0 1 4.93374e-17 
    vn 0 4.88706e-18 1 
    vn 1 0 0 
    vn -1 0 -3.21767e-17 
    vn -0.0437147 0.314427 0.948275 
    ...
    f 1 2 3 
    f 1 3 4 
    f 5 2 1 
    f 6 7 8 
    f 4 5 1 
    f 7 6 9 
    f 10 11 12 
    f 10 12 13 
    f 14 8 7 
    f 7 9 14 
    ...
    
     Here is the result:
![marchingsqueue](https://github.com/KokoFan16/Contour_Tree/blob/master/image/cube.png)




    
