# Contour_Tree
Extract contours in 2D and 3D image

### Marching squeue

    To find all the points that have a given height c, we have to solve the implicit equation f(x,y)=c. 
    Such a function determines the isosurfaces or contours of f for the isosurface value c.
    
    Here is same steps:
    1. Sample f(x,y) on a regular grid yielding samples {f{ij}(x,y)}
    2. These samples can be greater than, less than, or equal to c.
    3. Consider four samples f{ij}(x,y), f{i+1,j}(x,y), f{i+1,j+1}(x,y), f{i,j+1}(x,y) 
    4. These samples correspond to the corners of a cell
    5. Color the corners by whether than exceed or are less than the contour value t
    
    There are 16 cases:
    ![marchingsqueue]("https://www.google.com/search?q=marching+squares&rlz=1C5CHFA_enUS863US863&sxsrf=ACYBGNTqzx1SxYQdsN0s00Lv9UijRQVWWA:1573658989521&source=lnms&tbm=isch&sa=X&ved=0ahUKEwiso8XIwOflAhWrUt8KHSwsCX0Q_AUIEygC&biw=1372&bih=787#imgdii=_ptklB_Acaf1aM:&imgrc=JUEBbWqy3YKSHM:")
