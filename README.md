# Matrix

## Rotation Matrices
A basic rotation in 3D space along an axis can be represented with a 3x4 matrix. I have used 4x4 matrices in my example so it is easier for me to relate these matrices to the rest of my calculations. A way I found to visualize this is by imagining the x,y and z axes in 3D space inline with a unit sphere. Each row of a 3x4 matrix represents x,y or z. For example x = [1,0,0] because it has one in the x axis but zero in the rest. Now if we modify x to equal [0,1,0] then x is now y, it has rotated 90 degrees. This is why the following rotation matrices use sin and cos, note that without the sin/cos these are identity matrices to preserve the other coords. This is because you can only rotate an object in 2 dimensions at a time:

```
x = [[       1,       0,       0,       0],
     [       0,  cos(r), -sin(r),       0],
     [       0,  sin(r),  cos(r),       0],
     [       0,       0,       0,       1]];
     
y = [[  cos(r),       0,  sin(r),       0],
     [       0,       1,       0,       0],
     [ -sin(r),       0,  cos(r),       0],
     [       0,       0,       0,       1]];
     
z = [[  cos(r),       0, -sin(r),       0],
     [       0,       1,       0,       0],
     [  sin(r),       0,  cos(r),       0],
     [       0,       0,       0,       1]];

r = angle in radians
x = a rotation about the x axis
y = a rotation about the y axis
z = a rotation about the z axis
```

## Calculating FOV
The field of view (FOV) of a camera can be determined by the distance of the viewer position away from the display surface. An example of this is the closer you sit to your screen, the more of the screen will take up your vision.

To calculate the distance needed to achieve a specific FOV you can use the following equation:
```
z = 1 / tan(f/2);

f = field of view
z = distance from display surface
```
And the inverse of this equation can be used to find the viewer position:
```
f = 2 * arctan(1/z);

f = field of view
z = distance from display surface
```
