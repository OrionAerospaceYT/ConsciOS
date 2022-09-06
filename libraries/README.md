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

Three dimensional template based vector. Vector values are always in the order xyz. 

Constructors
```
Vec<> my_vector; //initializes a vector with 3 float values at 0,0,0
Vec<int> my_vector2(1,3,4); //initializes a vector of type int with the passed values
Vec<> my_2d_vector(-3.3,5); //automatically sets the z value to 0 and assigns the x and y values for a 2d vector 
Vec<> my_vector3(my_vector2); //a vector can be created from another vector 
```

Accessing components

```
auto vector_x = my_vector.x //using .x or .y or .z can access the component parts of a vector 

float vector_y = my_vector[1]; //works like array access 0 being x, 1 y and 2 z 

auto vector_z = my_vector.get(0); //much like arrray .get can be used too
```

Element-wise operations (all common operations *,/,+,-,*=,/= are covered)

```
Vec<> new_vector = my_vector * 10.0f;//multiplies eac element by 10.0f  

new_vector /= 10.0f; 
```

Vector to Vector 

```
auto new_vector = my_vector - my_vector2; //element wise vector to vector for +,-,/ and +=, /=
my_vector /= new_vector;

auto cross_product = new_vector * my_vector //computes and returns the cross product between two vectors 

auto dot_product = my_vector.dot(cross_product); //computes and returns the dot product of two vectors
```

to BLA Matrix or to Array

```
BLA::Matrix<3,1>A = {0,0,0};
my_vector.fromMat(A);

A = my_vector.toMat(A);

Array<float,3> B;
my_vector.fromArr(B);

B = my_vector.toArr(B);
```
Boolean operators for vector to vector exist for <,>,==, !=
```
bool my_bool = my_vector > 3.0f;//checks elemet-wise if the vector is larger or less than a value 

if(my_vector == my_vector2){
    PRINT("vectors are equal");
}
```

Misc. 

```
float magnitude = my_vector.magnitude(); //returns the magnitude of the vector 

my_vector.normalize(); //converts the vector into a unit vector 

my_vector.toDegrees();
my_vector.toRadians(); //easy access to convert a vector 
```

<h2>
<a href= 'link'>quaternion.h</a>
</h2>

4 dimensional template based quaternion. Values always in w,i,j,k order.

Constructors 
```
Quat<> my_quat; //initializes quat of type float with values 1,0,0,0
Quat<> my_quat2(0.71,0,0.71,0); 
Quat<> my_quat3(my_quat2); //a quaternion can be created from another quaternion

```
Accessing components 
```
auto real_component = my_quat.w; //usin .w, .i, .j, .k components of the quat can be accessed 

float i = my_quat[1]; // values can also be acccessed like in arrays 

auto j = my_quat.get(2);// or using .get(index)

```

Element-wise element wise for all basic type operators (*,/,+,-,*=,/=)
```
auto new_quat = my_quat * 10.0f;

new_quat /= 10.0f;
```

Quaternion to Quaternion operations

```
auto cross_product = my_quat * my_quat2; //quaternion cross product

auto div = my_quat / my_quat2; // Division is just multiplication by the multiplicative inverse 

auto new_quat = my_quat + cross_product; // quat to quat exists for +,-,+=,-=
```
Bool Operations 

bool operations exist for <,> to basic type or ==, != for quat to quat

```
bool my_bool = my_quat < -10.0f;

if(my_quat != my_quat2){
    PRINT("quats not equal");
}

```

Quaternion to vectors and Euler Angle conversions 

```
float* c_style_arr = my_quat.toEuler();//converts a quat to a array of euler angles 

my_vector = my_quat.toEulerVector(my_vector);

my_quat_rate = my_quat.fromAngularRate(my_rate_vector); // the input rate must be in rad/s

my_quat = my_quat.fromEuler(my_vector); //euler angles to quaternion 

my_quat = my_quat.fromEuler(0.15f,0.1f,0.0f); 

```
Quaternion to BLA Matrix and Array 

```
BLA::Matrix<3,1> A = {0,0,0};
my_quat = my_quat.fromMat(A);

A = my_quat.toMat(A);

Array<float,3> B;
my_quat = my_quat.fromArr(B);

B = my_quat.toArr(B);

```

Misc.

```
float magnitude = my_quat.magnitude();

auto squared = my_quat.square();

my_quat.normalize();//converts the quat to a unit quaternion 