package day

type Day struct {
	Part1, Part2 Part
}

type Part struct {
	Expected string
	Actual   string
}

type Status int

const (
	Unknown Status = iota
	Passed
	Failed
)

func (part *Part) Passed() Status {
	if part.Expected == "" {
		return Unknown
	}

	if part.Actual == "" {
		return Unknown
	}

	if part.Expected == part.Actual {
		return Passed
	} else {
		return Failed
	}
}
