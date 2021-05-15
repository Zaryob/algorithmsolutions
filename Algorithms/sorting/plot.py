import matplotlib.pyplot as plt
import matplotlib.lines as lines
import matplotlib.patches as patches
import matplotlib.text as text
from matplotlib.animation import FuncAnimation
import sort


def plot_performance(sorts, input_sizes):
    """Create a plot of runtime for each sort with different input sizes.

Will graph each sort with each input size. Returns a matplotlib figure.
"""
    fig = plt.figure()
    ax = fig.add_subplot(1, 1, 1)

    for s in sorts:
        data = [(n, sort.count_steps(s, sort.random_list(n)))
                for n in input_sizes]
        ax.plot(*zip(*data))
    ax.legend([s.__name__ for s in sorts])
    plt.xlabel('Input Length')
    plt.ylabel('Steps')


def animated_bars(sort_func, data, interval):
    """Create a sort animation showing each list element as a vertical bar."""

    # Run the entire sort, remembering all intermediate states
    states = [list(data)]
    def save_state(*_):
        states.append(list(data))
    sort.run(sort_func, data, save_state)
    save_state()  # Final state

    fig = plt.figure()
    ax = fig.add_subplot(1, 1, 1)
    bars = ax.bar(x=range(len(data)), height=list(data))
    plt.xticks([])
    plt.yticks([])
    plt.close()

    def animate(i):
        for b, h in zip(bars, states[i]):
            b.set_height(h)
        return bars

    return FuncAnimation(fig, animate, frames=len(states), interval=interval)


def circle_plot(fig, data):
    # Artists are scaled according to aspect ratio. We'll need to undo
    # this to draw circles.
    xsize, ysize = fig.get_size_inches()
    yscale = xsize / ysize

    # This magic invisible line makes the figure show up
    fig.lines.append(lines.Line2D([0, 0], [0, 1], transform=fig.transFigure,
                                  figure=fig, color='white'))

    spacing = 1.0 / (len(data) + 1)
    radius = 0.8 * spacing
    smallest = min(*data)
    largest = max(*data)

    def scaled_radius(value):
        interp = (value - smallest) / (largest - smallest)
        return radius * (0.6 + interp * 0.4)

    for i, v in enumerate(data):
        x = (i + 0.5) * spacing
        y = 0.5
        r = scaled_radius(v)
        c = patches.Ellipse((x, y), r, yscale * r, transform=fig.transFigure,
                            figure=fig, fill=False)
        fig.patches.append(c)

        t = text.Text(x, y, str(v), transform=fig.transFigure, figure=fig,
                      verticalalignment='center', horizontalalignment='center',
                      fontsize=300 * r)
        fig.texts.append(t)


class CircleAnimation:
    def __init__(self, fig, sort_func, data):
        # Create the animation objects

        # Artists are scaled according to aspect ratio. We'll need to undo
        # this to draw circles.
        xsize, ysize = fig.get_size_inches()
        yscale = xsize / ysize

        # This magic invisible line makes the figure show up
        fig.lines.append(lines.Line2D([0, 0], [0, 1],
                                      transform=fig.transFigure,
                                      figure=fig, color='white'))

        self._spacing = 1.0 / (len(data) + 1)
        self._radius = 0.8 * self._spacing
        smallest = min(*data)
        largest = max(*data)

        def scaled_radius(value):
            interp = (value - smallest) / (largest - smallest)
            return self._radius * (0.6 + interp * 0.4)

        def create_artists(i, v):
            x = (i + 0.5) * self._spacing
            y = 0.5
            r = scaled_radius(v)
            c = patches.Ellipse((x, y), r, yscale * r,
                                transform=fig.transFigure,
                                figure=fig, fill=False)

            t = text.Text(x, y, str(v), transform=fig.transFigure, figure=fig,
                          verticalalignment='center',
                          horizontalalignment='center',
                          fontsize=300 * r)
            return c, t

        def create_arrow():
            return patches.Polygon(self._arrow_points(),
                                   closed=True, transform=fig.transFigure,
                                   figure=fig, visible=False)

        self._circles, self._texts = map(list,
                                         zip(*[create_artists(i, v)
                                               for i, v in enumerate(data)]))
        self._arrows = [create_arrow(), create_arrow()]

        fig.patches.extend(self._circles)
        fig.patches.extend(self._arrows)
        fig.texts.extend(self._texts)

        self._label = text.Text(0, 0.9,
                                transform=fig.transFigure, figure=fig,
                                verticalalignment='top',
                                horizontalalignment='left',
                                fontsize=200 * self._spacing)
        fig.texts.append(self._label)

        # Collect effects and generate animation frames
        effects = []
        sort.run(sort_func, data, lambda *e: effects.append(e))
        self._generate_frames(effects)
        self._focused = []

    def _arrow_points(self, x_offset=0, y_offset=0):
        width = 0.1 * self._spacing
        x_offset -= 0.5 * width                # Center horizontally
        y_offset += 0.5 + 1.5 * self._spacing  # Center vertically
        return [(x + x_offset, y + y_offset)
                for x, y in [(0, 0),
                             (width, 0),
                             (0.5 * width, -3 * width)]]

    def _generate_frames(self, effects):
        self._frames = [('init', None, None)]
        for e in effects:
            kind = e[0]
            if kind == 'swap':
                a, b = e[1:]
                self._frames.append(('pre-swap', a, b))
                self._frames.append(e)
                self._frames.append(('post-swap', a, b))
            else:
                self._frames.append(e)

    def __len__(self):
        return len(self._frames)

    def _focus(self, *val):
        for i in self._focused:
            self._circles[i].set_edgecolor('black')
        self._focused = []
        for i in val:
            if i is not None:
                self._circles[i].set_edgecolor('orange')
                self._focused.append(i)

    def _compare(self, *elements):
        if elements:
            for a, i in zip(self._arrows, elements):
                a.set_visible(True)
                a.set_xy(self._arrow_points((i + 0.5) * self._spacing))
        else:
            for a in self._arrows:
                a.set_visible(False)

    def animate(self, step):
        effect = self._frames[step]
        kind = effect[0]

        if kind == 'focus':
            self._focus(*effect[1:])
        elif kind == 'subdivide':
            a, b = effect[1:]
            self._compare()
            for c, t, i in zip(self._circles, self._texts,
                               range(len(self._circles))):
                if i in range(a, b):
                    color = 'black'
                else:
                    color = 'gray'
                c.set_edgecolor(color)
                t.set_color(color)
        elif kind == 'cmp':
            a, b = effect[1:]
            self._compare(a, b)
        elif kind == 'pre-swap':
            a, b = effect[1:]
            c = self._circles
            self._focus()
            self._compare()
            c[a].set_fill(True)
            c[b].set_fill(True)
        elif kind == 'swap':
            a, b = effect[1:]
            c = self._circles
            c[a], c[b] = c[b], c[a]
            c[a].set_center(((a + 0.5) * self._spacing, 0.5))
            c[b].set_center(((b + 0.5) * self._spacing, 0.5))

            c = self._texts
            c[a], c[b] = c[b], c[a]
            c[a].set_position(((a + 0.5) * self._spacing, 0.5))
            c[b].set_position(((b + 0.5) * self._spacing, 0.5))
        elif kind == 'post-swap':
            a, b = effect[1:]
            c = self._circles
            c[a].set_fill(False)
            c[b].set_fill(False)
        elif kind == 'label':
            self._compare()
            self._label.set_text(effect[1])


def animated_circles(fig, sort_func, data, interval):
    """Create a sort animation showing each list element as a circle.

The circles are labeled with the number they contain, and scaled based
on the size of the value."""
    anim = CircleAnimation(fig, sort_func, data)
    return FuncAnimation(fig, anim.animate, frames=len(anim),
                         interval=interval)
