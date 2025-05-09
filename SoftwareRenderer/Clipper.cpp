#include "pch.h"
#include "Clipper.h"
#include "Vertex.h"

static
bool	isInside(Vertex const& vertex, Vector4 const& axis) {
	float const	w = vertex.pos.w;
	float const	v = vertex.pos * axis;

	return (v <= w);
}

static
Vertex	boundary(Vertex const& a, Vertex const& b, Vector4 const& axis) {
	float const	a0 = a.pos * axis;
	float const	b0 = b.pos * axis;
	float const diff_a = a0 - a.pos.w;
	float const diff_b = b0 - b.pos.w;
	float const	t = diff_a / (diff_a - diff_b);
	return Vertex::mix(a, b, t);
}

static
void	clipPlane(std::queue<Vertex>& queue, Vector4 const& axis) {
	int const	count = static_cast<int>(queue.size());
	Vertex		curr;
	Vertex		next;

	if (count <= 2)
		return;
	next = queue.front();
	queue.pop();
	queue.push(next);
	for (int i = 0; i < count; i++) {
		curr = next;
		next = queue.front();
		queue.pop();
		Vertex intersection = boundary(curr, next, axis);
		if (isInside(next, axis)) {
			if (!isInside(curr, axis)) {
				queue.push(intersection);
			}
			queue.push(next);
		}
		else if (isInside(curr, axis)) {
			queue.push(intersection);
		}
	}
}

// z -> -1 ~ 1
void Clipper::clip(std::queue<Vertex>& out)
{
	clipPlane(out, Vector4(1, 0, 0, 0));
	clipPlane(out, Vector4(-1, 0, 0, 0));
	clipPlane(out, Vector4(0, 1, 0, 0));
	clipPlane(out, Vector4(0, -1, 0, 0));
	clipPlane(out, Vector4(0, 0, 1, 0));
	clipPlane(out, Vector4(0, 0, -1, 0));
}
