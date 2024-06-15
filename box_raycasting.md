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

### Scene Graph
Tree structure which stores the scene.
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
- use mdspan? ;)
- use std::vector for the underlying data since my algorithms are all hard-coded to vector 
        - (changing 'drop' to std::array is non-trivial, the sizes must be known at compile-time or better yet I would have to change the implementation to a view)

Take the data from the tensor and visualize it, either by directly displaying it with OpenCV im.show() and/or writing it to an image file.

### Supporting libraries
- mdspan from STL
- some of the C++ algorithms I have recently written for std::vectors
- OpenCV to draw the image
- Eigen for the vector and matrix operations, which will make it much easier to work with homogeneous coordinates

## Alternatives

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

