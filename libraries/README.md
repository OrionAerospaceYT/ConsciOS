# Sidekick Libraries 

## Various libraries with common robotics utility. 

<h2>
<a href = "link"> Common.h </a>
</h2>

Common.h contains functionality used across various ConsciOS files. Includes debug functionality, macros for sending serial data to the gui, and logging functionality. 

```
assert(condition,message); 
``` 
If the condition is true the terminal will print the file and line that has failed, along with a user specified message (expected string) passed in as message. This will then hang the code indefinitely to prevent any further errors. 

Example:
```
assert(denominator != 0, "Divide by 0 assert!");
```

MACROS:

```
TOP_GRAPH(name,data);
```

Plots data to the top graph of the gui. The name (expected string) of the data will be displayed on the graph. 

```
BOTTOM_GRAPH(name,data);
```

Shares the same functionality as the TOP_GRAPH and can be used exactly the same. 

```
PRINT(text);
```

Prints a line to the terminal. Each PRINT is treated like a PRINTLN, so you'll want to combine text before passing it into print for single line prints. 


<h2>
<a href = "link"> sk_math.h </a>
</h2>

Contains common and useful math functionality. Wrapped in namespace sk_math to avoid any clashes. 

```
sk_math::CLAMP(value,low,high);
```
Ensures the returned value is between the bounds. If the value is outside of these bounds it will return the nearest bound. 

Example:
```
float my_value = 42.0;
auto output = sk_math::CLAMP(my_value,-40.0,40.0);
```
Would return 40.0 to output. 

```
sk_math::ISCLOSE(value, target, error);
```
Checks if value is close to target within some error. Particularly useful for evaluating floats/doubles. Returns true or false. 

Example:
```
float my_altitude = MyGetAltitudeFunction();
if(sk_math::ISCLOSE(my_altitude,100.0,0.5)){
    PRINT("AT 100 Meters!");
}
```

```
sk_math::ISPOS(value);
```
This one is fairly self explanatory. It checks if a value is positive. Returns true or false. 

```
sk_math::SIGN(value);
```
Returns the sign of a value. Returns (-1,0,1) in the same type as value that is passed in. 

```
sk_math::LERP(start,finish,interpolation_point);
```

Returns the value that lies on the line created between start and finish at the interpolation_point. On an assumed range of [0,1]. 

Example:

```
auto output = sk_math::LERP(0,8.0,0.33);
```
Here the output would be the value that lies a third of the way along the line created by the two points [0,0] and [1,8]. 

```
sk_math::SMOOTHLERP(start,finish,interpolation_point);
```
Used exactly the same as LERP, but with a smoothing function to make the interpolation less robotic. More info can be found here: https://gamedevbeginner.com/the-right-way-to-lerp-in-unity-with-examples/

```
sk_math::QUADBEZIER2D(point1, point2, point3, step);
```
Returns the quadratic bezier value between the the 3 points at a specified step/interpolation point. 

Example:
```
Vec<float> p1 = Vec<float>(1,1);
Vec<float> p2 = Vec<float>(3,6);
Vec<float> p3 = Vec<float>(5,2);
for(float step = 0; step <= 10; step += 0.1){
    auto output = sk_math::QUADBEZIER2D(p1, p2, p3, step);
    }
```
Here the output is the quadratic bezier interpolation over 0.1 steps from 0 to 10 with the guide points of [1,1], [3,6], [5,2] 


```
sk_math::EARTHA(accel, phi, theta);
```
Returns the earth relative accelertation given the axial acceleration and the two non-axial Euler angles of the IMU.

```
sk_math::FASTINVSQ(number);
```
The fast inverse squareroot formula in C++. Calculates the inverse square root of a number.
more info: https:/www.tutorialspoint.com/fast-inverse-square-root-in-cplusplus/


<h2>
<a href = "link"> vector.h </a>
</h2>

Three dimensional template based vector. 

```
Vec<> my_vector
 

