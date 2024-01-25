/* Patch to support gaps is stolen from https://codeberg.org/speedie/dwm/src/branch/main/layouts.c */
void
fibonacci(Monitor *m, int s)
{
	unsigned int i, n;
	int nx, ny, nw, nh;
	int nv, hrest = 0, wrest = 0, r = 1;
	Client *c;

	for (n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), n++);
	if (n == 0)
		return;

	nx = m->wx + gappx;
	ny = m->wy + gappx;
	nw = m->ww - 2*gappx;
	nh = m->wh - 2*gappx;

	for (i = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next)) {
		if (r) {
			if ((i % 2 && (nh - gappx) / 2 <= (bh + 2*c->bw))
			   || (!(i % 2) && (nw - gappx) / 2 <= (bh + 2*c->bw))) {
				r = 0;
			}
			if (r && i < n - 1) {
				if (i % 2) {
					nv = (nh - gappx) / 2;
					hrest = nh - 2*nv - gappx;
					nh = nv;
				} else {
					nv = (nw - gappx) / 2;
					wrest = nw - 2*nv - gappx;
					nw = nv;
				}

				if ((i % 4) == 2 && !s)
					nx += nw + gappx;
				else if ((i % 4) == 3 && !s)
					ny += nh + gappx;
			}

			if ((i % 4) == 0) {
				if (s) {
					ny += nh + gappx;
					nh += hrest;
				}
				else {
					nh -= hrest;
					ny -= nh + gappx;
				}
			}
			else if ((i % 4) == 1) {
				nx += nw + gappx;
				nw += wrest;
			}
			else if ((i % 4) == 2) {
				ny += nh + gappx;
				nh += hrest;
				if (i < n - 1)
					nw += wrest;
			}
			else if ((i % 4) == 3) {
				if (s) {
					nx += nw + gappx;
					nw -= wrest;
				} else {
					nw -= wrest;
					nx -= nw + gappx;
					nh += hrest;
				}
			}
			if (i == 0)	{
				if (n != 1) {
					nw = (m->ww - gappx - 2*gappx) - (m->ww - gappx - 2*gappx) * (1 - m->mfact);
					wrest = 0;
				}
				ny = m->wy + gappx;
			}
			else if (i == 1)
				nw = m->ww - nw - gappx - 2*gappx;
			i++;
		}

		resize(c, nx, ny, nw - (2*c->bw), nh - (2*c->bw), False);
	}
}

void
dwindle(Monitor *mon) {
	fibonacci(mon, 1);
}

void
spiral(Monitor *mon) {
	fibonacci(mon, 0);
}
