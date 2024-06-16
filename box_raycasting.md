# Box raycasting

## Problem

Render an image of a box using raycasting.

## Background

I have time off and want to:

- learn how raycasting works
- create nice images of city-scapes
- create color and depth images to experiment with various image processing techniques
- refresh my knowledge of coordinate transforms
- learn how to formulate the raycasting equations using linear algebra
- find out common algorithms are useful for this kind of work
- see tangible results from code I have written

## Design

Simplifying assumptions for the first version:
- the sun and (fixed) ambient lighting are the only light-sources
- only one box will be rendered (no occlusion of the sun due to shadows)
- hard-code the ground plane and single box in the main method

Components
1. Input
2. Scene Graph
3. Raycaster
4. Output

### Input
Will not be implemented at the start. 
I will hard-code the ground plane and single box in the main method.

**Source interface**
- object list (geometry, transformations, color and material)
- lighting list
- camera position

### Representation of geometry
Raycasting a box is much easier if that box is axis-aligned, because then the intersection test only has to check a one-dimensional interval along each axis.
In the object coordinate system, a box is axis aligned.
Thus, I can make the intersection test for boxes and planes easier if I transform the ray into the object coordinate system.
To make this as easy as possible, I will use homogenous coordinate transforms, so I can easily switch coordinate systems from one object to the next.
Every object will need to store a transformation, relative to the origin (or some other parent object).
This forms the basis for the scene graph.

### Bag of lines

A polygon is just a collection of lines.
If I want to test a ray for intersection with the polygon, then I must test it for intersection with each of its constituent lines.
This means that all the geometric object has to be able to provide, is a collection of lines.
(Note: later on a bag of triangles datatype would allow extending this design to 3d.)

Information about surface normals for each of those lines, could be helpful as well, but may not be necessary as all objects are opaque.
If all objects are oqaque (no transparency), and the camera is always _outside_ of the objects, the closest hit is always on the outside of an object.

So how can I implement a 'bag of lines' datatype to handle these all consistently?

TODO



### Scene Graph

The scene graph is a tree structure which stores all the geometry in the scene.
The root node is the origin of the world coordinate system (identity matrix).


Tree structure which stores all the objects in the scene, together with their relative transformations.
The objects from the source need to be added to the scene graph.
Bounding volumes may have to be calculated for each object.
Inverse coordinate transformations to get from the object to origin (or the camera) may need to be calculated.

### Raycaster
Create a set of direction vectors for each pixel once on startup.

For each pixel:

1. cast the ray and check every object for intersection
    - preferably do this by transforming the ray into the object coordinate systhem to make intersection checks really easy for boxes
    - use homogeneous coordinate transforms to support arbitrary positions and orientations easily

2. for the closest hit
    - compute range-dependent haze
    - compute ambient lighting
    - create a ray toward each light-source, if it is facing outwards from the surface, raycast to that light-source
    - add all lighting components together

3. if there is no hit, compute the background value (just a color gradient from white to blue?)

Optional: I could do super-sampling / anti-aliasing to sharpen the images a bit.

### Output

**Sink interface** 
- tensor with color and depth values
- use mdspan? -- GCC does NOT have an implementation of mdspan yet... :'(
- use std::vector for the underlying data since my algorithms are all hard-coded to vector 
        - (changing 'drop' to std::array is non-trivial, the sizes must be known at compile-time or better yet I would have to change the implementation to a view)

Take the data from the tensor and visualize it, either by directly displaying it with OpenCV im.show() and/or writing it to an image file.

### Supporting libraries
- STL
- OpenCV to draw the image
- Eigen for the vector and matrix operations, which will make it much easier to work with homogeneous coordinates
- some of the C++ algorithms I have recently written for std::vectors

## Alternatives

### Adjacency matrix and list of points

Given a list of lines, an adjacency matrix can easily encode which points are connected with lines.
Polygons encoded within it, do not suffer from numerical stability issues as much, since there is a single source of truth for each point.
For a dense adjacency matrix the memory requirement lies in O(n) for the number of points, albeit it is only one boolean per cell.
If the lines don't have the direction, the matric is symmetric, cutting storage requirements in half.
The number of points would have to be in the thousands, for memory usage to be a relevant issue.

### Heterogeneous representations
N  | Object            | Tuple                              | Comments                                                              |
-- | ----------------- | ---------------------------------- | --------------------------------------------------------------------- |
1  | Coordinate system | (Transform)                        |                                                                       |
2  | Point             | (Transform)                        | Note that this definition implies that a point has an orientation.    |
3  | Ray               | (Transform)                        | Find/define a convention: the ray always travels along the X-axis (?) |
4  | Line              | (Transform, Length)                | Use the same convention as for the ray                                |
5  | Rectangle         | (Transform, Point)                 | Axis-aligned rectangle                                                |
5  | Right-Triangle    | (Transform, Point)                 | Axis-aligned right-angle triangle                                     |
6a | Triangle          | (Transform, Point, Vector)         |                                                                       |
6b | Triangle          | (Transform, Point, Length)         |                                                                       |

### Homogeneous representations
N  | Object            | Tuple                              | Comments                                                              |
-- | ----------------- | ---------------------------------- | --------------------------------------------------------------------- |
1  | Coordinate system | (Transform)                        |                                                                       |
2  | Point             | (Transform)                        | Note that this definition implies that a point has an orientation.    |
3  | Ray               | (Transform)                        | Find/define a convention: the ray always travels along the X-axis (?) |
4  | Line              | (Transform, Transform)             | Use the same convention as for the ray                                |
5  | Rectangle         | (Transform, Transform)             | Axis-aligned rectangle                                                |
5  | Right-Triangle    | (Transform, Transform)             | Axis-aligned right-angle triangle                                     |
6  | Triangle          | (Transform, Transform, Transform)  |                                                                       |

Note that color and material information needs to be annotated to every one of these nodes, except the global coordinate system (root node).

Technically every one of these objects can be represented by `(Transfrom, Color, [Point, ...,  Point])`.
However, that is still ambiguous since a line, a rectangle, and a right-angle triangle will all have two points in their list (origin, other).
Even if this was not the case, there are only three mechanisms I can think of to handle things such as intersection calculations:
- runtime polymorphism
- switch-case (over the object 'type' encoded by an enum or the size of the vector)
- std::variant

### Python implementation

Pros:
- lots of libraries which are easily accessible
    - easy visualization
    - matrix operations in Numpy
    - file IO with Pandas or Polars
- opportunity to refresh python skills

Cons:
- slow execution
- extra time spent to refresh python

### Rust or Haskell implementation
Pros:
- can be fast
- opportunity to practice a new language

Cons:
- I have to learn a new language

If I want to learn a new language, I should start with something easier. Once I have a bit of proficiency in that language I can come back and re-implement this project in that language. To see some results soon, it's better to stick to a language I already know.

### Render everything with OpenGL

Pros:
- fast and easy results

Cons:
- I don't refresh / learn linear algebra stuff
- Cannot be used directly to create depth images

### Render everything with Vulkan

Pros:
- GPU acceleration

Cons:
- complicated
- a lot of work to learn

I don't need the GPU performance for now. Only worth it if I had plans to do more with Vulkan in the future.

