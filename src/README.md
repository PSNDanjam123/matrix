# Matrix

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
