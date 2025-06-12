import matplotlib
matplotlib.use('TkAgg')
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.widgets import Slider, Button
import threading
import time
from matplotlib.animation import FuncAnimation
from matplotlib.patches import Circle, Rectangle

class MandelbrotSettings:
    def __init__(self):
        self.xmin = -2.0
        self.xmax = 0.8
        self.ymin = -1.4
        self.ymax = 1.4
        self.max_iter = 300
        self.escape_radius = 2.0
        self.power = 2  # z^power + c
        self.resolution = (1920, 1080)

def mandelbrot(h, w, settings):
    y, x = np.ogrid[settings.ymin:settings.ymax:h*1j, 
                    settings.xmin:settings.xmax:w*1j]
    c = x + y*1j
    z = c
    divtime = np.zeros(z.shape, dtype=np.float64)
    
    escape_value = settings.escape_radius**2
    for i in range(settings.max_iter):
        z = z**settings.power + c
        diverge = z*np.conj(z) > escape_value
        div_now = diverge & (divtime == 0)
        divtime[div_now] = i + 1 - np.log(np.log(abs(z[div_now]))) / np.log(settings.power)
        z[diverge] = settings.escape_radius

    return divtime

class MandelbrotViewer:
    def __init__(self):
        self.settings = MandelbrotSettings()
        self.fig = plt.figure(figsize=(16, 10))
        self.update_timer = None
        self.loading_animation = None
        self.is_calculating = False
        self.zoom_rect = None
        self.zoom_factor = 0.4  # Changed for smoother zoom
        self.min_size = 1e-13  # Prevent infinite zoom
        self.setup_layout()
        self.setup_controls()
        self.setup_zoom_events()
        self.draw()

    def setup_layout(self):
        # Main plot
        self.ax = self.fig.add_axes([0.1, 0.25, 0.8, 0.7])
        # Slider axes
        self.slider_axes = {
            'iter': self.fig.add_axes([0.1, 0.15, 0.3, 0.02]),
            'power': self.fig.add_axes([0.1, 0.1, 0.3, 0.02]),
            'escape': self.fig.add_axes([0.1, 0.05, 0.3, 0.02])
        }
        # Status bar for loading animation
        self.status_ax = self.fig.add_axes([0.1, 0.01, 0.8, 0.02])
        self.status_ax.axis('off')

    def setup_controls(self):
        # Create sliders
        self.sliders = {
            'iter': Slider(self.slider_axes['iter'], 'Iterations', 50, 1000, 
                         valinit=self.settings.max_iter, valstep=50),
            'power': Slider(self.slider_axes['power'], 'Power', 2, 5, 
                          valinit=self.settings.power, valstep=1),
            'escape': Slider(self.slider_axes['escape'], 'Escape Radius', 1, 10, 
                           valinit=self.settings.escape_radius, valstep=0.5)
        }

        # Connect update events
        for slider in self.sliders.values():
            slider.on_changed(self.update_settings)

    def update_settings(self, val):
        # Cancel any existing timer
        if self.update_timer is not None:
            self.update_timer.cancel()
        
        # Start a new timer
        self.update_timer = threading.Timer(5.0, self.delayed_update)
        self.update_timer.start()
        
        # Update status text
        self.ax.set_title('Mandelbrot-Menge (Warte 5 Sekunden...)')
        self.fig.canvas.draw_idle()

    def animate_loading(self, frame):
        if not self.is_calculating:
            self.status_ax.clear()
            self.status_ax.axis('off')
            return []

        # Windows 11 style loading animation
        segments = 8
        active_segments = 3
        angle = (frame % segments) * (360 / segments)
        dots = []
        
        for i in range(segments):
            seg_angle = i * (360 / segments)
            # Calculate opacity for each segment
            distance = (seg_angle - angle) % 360
            alpha = 1.0 if distance < (360 / segments * active_segments) else 0.2
            dots.append('●' if alpha > 0.5 else '○')
        
        self.status_ax.clear()
        self.status_ax.axis('off')
        text = f"Berechne... {''.join(dots)}"
        self.status_ax.text(0.5, 0.5, text,
                          ha='center', va='center',
                          fontfamily='monospace',
                          color='#0078D7',
                          fontsize=10,
                          bbox=dict(facecolor='white',
                                  edgecolor='none',
                                  alpha=0.8))
        return [self.status_ax]

    def start_loading_animation(self):
        self.is_calculating = True
        self.loading_animation = FuncAnimation(self.fig, self.animate_loading,
                                             frames=None, interval=100, blit=True)

    def stop_loading_animation(self):
        self.is_calculating = False
        if self.loading_animation:
            self.loading_animation.event_source.stop()
            self.loading_animation = None
        self.status_ax.clear()
        self.status_ax.axis('off')
        self.fig.canvas.draw_idle()

    def delayed_update(self):
        self.start_loading_animation()
        try:
            # Update the settings and redraw
            self.settings.max_iter = int(self.sliders['iter'].val)
            self.settings.power = int(self.sliders['power'].val)
            self.settings.escape_radius = float(self.sliders['escape'].val)
            self.draw()
        finally:
            self.stop_loading_animation()

    def draw(self):
        mandel = mandelbrot(self.settings.resolution[1], 
                          self.settings.resolution[0], 
                          self.settings)
        
        colors = ['#000764', '#206BCB', '#EDFFFF', '#FFB847', '#A40000']
        custom_cmap = matplotlib.colors.LinearSegmentedColormap.from_list('custom', colors)
        
        self.ax.clear()
        self.im = self.ax.imshow(mandel, cmap=custom_cmap,
                                extent=[self.settings.xmin, self.settings.xmax, 
                                       self.settings.ymin, self.settings.ymax])
        if hasattr(self, 'colorbar'):
            self.colorbar.remove()
        self.colorbar = self.fig.colorbar(self.im, label='Escape time')
        
        self.ax.set_title(f'Mandelbrot-Menge (Power: {self.settings.power}, Iter: {self.settings.max_iter})')
        self.ax.set_xlabel('Re(c)')
        self.ax.set_ylabel('Im(c)')
        self.fig.canvas.draw_idle()

    def setup_zoom_events(self):
        self.fig.canvas.mpl_connect('button_press_event', self.on_mouse_click)
        self.fig.canvas.mpl_connect('motion_notify_event', self.on_mouse_move)
        self.fig.canvas.mpl_connect('axes_leave_event', self.on_mouse_leave)

    def update_zoom_preview(self, x, y):
        if self.zoom_rect:
            self.zoom_rect.remove()
            self.zoom_rect = None

        if x is None or y is None or not hasattr(self, 'ax'):
            return

        x_range = (self.settings.xmax - self.settings.xmin) * self.zoom_factor
        y_range = (self.settings.ymax - self.settings.ymin) * self.zoom_factor

        self.zoom_rect = Rectangle(
            (x - x_range/2, y - y_range/2),
            x_range, y_range,
            fill=False,
            color='white',
            linestyle='--',
            alpha=0.8
        )
        self.ax.add_patch(self.zoom_rect)
        self.fig.canvas.draw_idle()

    def on_mouse_move(self, event):
        if event.inaxes != self.ax:
            self.on_mouse_leave(event)
            return
        self.update_zoom_preview(event.xdata, event.ydata)

    def on_mouse_leave(self, event):
        if self.zoom_rect:
            self.zoom_rect.remove()
            self.zoom_rect = None
            self.fig.canvas.draw_idle()

    def on_mouse_click(self, event):
        if event.inaxes != self.ax:
            return

        # Remove zoom preview
        if self.zoom_rect:
            self.zoom_rect.remove()
            self.zoom_rect = None

        x, y = event.xdata, event.ydata
        x_range = self.settings.xmax - self.settings.xmin
        y_range = self.settings.ymax - self.settings.ymin

        # Calculate zoom factor
        if event.button == 1:  # Left click - zoom in
            factor = self.zoom_factor
        elif event.button == 3:  # Right click - zoom out
            factor = 1 / self.zoom_factor
            # Limit zoom out to initial view
            if x_range / factor > 3 or y_range / factor > 3:
                return
        else:
            return

        # Calculate new ranges
        new_x_range = x_range * factor
        new_y_range = y_range * factor

        # Check minimum zoom size
        if new_x_range < self.min_size or new_y_range < self.min_size:
            return

        # Update boundaries with centered zoom
        self.settings.xmin = x - new_x_range/2
        self.settings.xmax = x + new_x_range/2
        self.settings.ymin = y - new_y_range/2
        self.settings.ymax = y + new_y_range/2

        # Adjust iterations based on zoom level
        if event.button == 1:
            zoom_level = 3 / new_x_range
            self.settings.max_iter = min(2000, int(300 * np.log2(zoom_level + 1)))
            self.sliders['iter'].set_val(self.settings.max_iter)

        self.start_loading_animation()
        try:
            self.draw()
        finally:
            self.stop_loading_animation()

if __name__ == '__main__':
    viewer = MandelbrotViewer()
    plt.show()
