
# Points, lines, and polylines as a tree of annotated transformations

A tree consisting of:

| # |     | Type | Descripion                   |
| - | --- | ---- | ---------------------------- |
| 1 | GCS | root | global coordinate systhem    |
| 2 | Tra | node | transformation               |
| 3 | Val | leaf | value (color, material, etc) |

can be used to represent points, lines, and polylines algebraeically.
Since a tree is a directed acyclic graph, polygons present a challenge.
A polygon can either be represented as a single polyline, or a pair of (poly)lines which meet on the far side.
Both representations could cause problems though, as the end points probably won't be exactly equal, due to the limits of numerical precision.
It is not clear to me if this construct can be extended to model shaded surfaces.
They suffer from the same shortcomings of the acyclic graph.

In this notation a connection from one transformation to another, i.e. (Tra - Tra) encodes a line.

**A point**

                GCS
                 |
                Tra
                 |
                Val

**Two points**

                GCS
               /   \
            Tra     Tra
             |       |
            Val     Val

**A line**

                GCS
                 |
                Tra
               /   \
            Val     Tra
                   /
                Val

**A polyline** (2-polyline)

                GCS
                 |
                Tra
               /   \
            Val     Tra
                   /   \
                Val     Tra
                       /
                    Val

**A polyline** (3-polyline)

                GCS
                 |
                Tra
               /   \
            Val     Tra
                   /   \
                Val     Tra
                       /   \
                    Val     Tra
                           /
                        Val

**A triangle** (line and 2-polyline)

                GCS
                 |
                Tra
              /  |  \
           Val  Tra  Tra
               /    /   \
            Val  Val     Tra
                        /
                     Val

**A four sided polygon** (2-polyline and 2-polyline)

                GCS
                 |
                Tra
              /     \
           Tra       Tra
          /  |      /  |
       Val  Tra  Val  Tra
           /         /
        Val       Val
