package point

type Point struct {
	X, Y int
}

func New(x, y int) Point {
	return Point{x, y}
}

func Origin() Point {
	return New(0, 0)
}

func (point Point) Add(other Point) Point {
	return New(point.X+other.X, point.Y+other.Y)
}
