# Ray
## Ray equation
$P(t) = O + tD$

Where $O$ — origin (start of the ray), $t$ — distance along the ray, $D$ — direction vector.

## Logic of the equation: 
$tD$ is multiplying a vector by a scalar, which scales the direction vector to the required distance.
Adding this result to $O$ offsets the ray origin to the target position.

# Sphere
## Sphere equation in vector form
$$(P - C) \cdot (P - C) = R^2$$

Where $P$ — point on the sphere, $C$ — center of the sphere, $R$ — radius of the sphere.

## Logic of the equation:
The radius of a sphere is the spatial diagonal formed by offsets along the $X$, $Y$, and $Z$ axes.
According to the 3D Pythagorean theorem:

$$x^2 + y^2 + z^2 = R^2$$

This equation works like two consecutive Pythagorean theorems:
1. The legs $x$ and $y$ give the square of the hypotenuse in the plane: $d^2 = x^2 + y^2$
2. The leg $d$ (the floor diagonal) and the leg $z$ (height/depth) give the square of the spatial hypotenuse: $R^2 = d^2 + z^2$

The sum $x^2 + y^2 + z^2$ is equivalent to the dot product of a vector with itself, which yields its squared length:

$$A \cdot A = |A|^2$$

So:

$$|A|^2 = A \cdot A = R^2$$

In this case, $A = P - C$.

## Derivation of Ray-Sphere Intersection:
### Algebraic solution
The ray intersects the sphere if $P(t)$ yields a point lying on the sphere surface. Substituting $P(t) = O + tD$ into the sphere equation:

$$(O + tD - C) \cdot (O + tD - C) = R^2$$

Let $V = O - C$:

$$(V + tD) \cdot (V + tD) = R^2$$

Expanding the brackets using the distributive property and moving $R^2$ to the LHS:

$$V \cdot V + V \cdot tD + tD \cdot V + tD \cdot tD - R^2 = 0$$

Using scalar product properties (associativity and commutativity):

$$V \cdot V + t(V \cdot D) + t(V \cdot D) + t^2(D \cdot D) - R^2 = 0$$

Simplifying:

$$V \cdot V + 2t(V \cdot D) + t^2(D \cdot D) - R^2 = 0$$

Grouping terms by powers of $t$ ($t^2 \to t^1 \to t^0$):
$$(D \cdot D)t^2 + 2(V \cdot D)t + (V \cdot V - R^2) = 0$$

### Conclusion
Evaluating ray-sphere intersection reduces to solving a standard quadratic equation ($a t^2 + b t + c = 0$), where:
* a = $D \cdot D$
* b = $2(V \cdot D)$
* c = $V \cdot V - R^2$

Solving via the discriminant ($\Delta$), three cases are possible:
* $\Delta < 0$: no intersection (ray misses the sphere)
* $\Delta = 0$: the ray is tangent to the sphere (one intersection point)
* $\Delta > 0$: the ray intersects the sphere at two points