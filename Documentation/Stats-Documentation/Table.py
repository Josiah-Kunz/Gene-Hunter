import matplotlib.pyplot as plt
import matplotlib.patches as patches
from matplotlib.transforms import Bbox
from PIL import Image

class Cell:
        
        xmin = 0
        xmax = 1
        ymin = 0
        ymax = 1
        color = "white"
        content = ""
        lineColor = "black"
        fontsize=12
        horizontalAlignment = "center"  # {'center', 'right', 'left'}
        verticalAlignment = "center"    # {'center', 'top', 'bottom', 'baseline', 'center_baseline'}
        contentRotation = 0
        autosizeFont = True
        
        def __init__(self, 
                     x0, x1, y0, y1, 
                     color="white", content="", lineColor="black", fontsize=12,
                     horizontalAlignment="", ha="center",
                     verticalAlignment="", va="center",
                     contentRotation=0,
                     autosizeFont = True):
            self.xmin = x0
            self.xmax = x1
            self.ymin = y0
            self.ymax = y1
            self.color = color
            self.content = content
            self.lineColor = lineColor
            self.fontsize = fontsize
            if horizontalAlignment == "":
                horizontalAlignment = ha
            self.horizontalAlignment = horizontalAlignment
            if verticalAlignment == "":
                verticalAlignment = va
            self.verticalAlignment = verticalAlignment
            self.contentRotation = contentRotation
            self.autosizeFont = autosizeFont
            
        def Overlap(self, other):
            return not (
                        self.xmax <= other.xmin
                        or self.xmin >= other.xmax
                        or self.ymax <= other.ymin
                        or self.ymin >= other.ymax
                    )
            
        def Width(self):
            return self.xmax - self.xmin
            
        def Height(self):
            return self.ymax - self.ymin
            
        def GetAnnotateAnchor(self):
            x = (self.xmin + self.xmax)/2
            y = (self.ymin + self.ymax)/2
            if self.horizontalAlignment == "left":
                x = self.xmin
            if self.horizontalAlignment == "right":
                x = self.xmax
            if self.verticalAlignment == "top":
                y = self.ymax
            if self.verticalAlignment == "bottom":
                y = self.ymin
            return (x, y)
                
        def auto_fit_fontsize(self, text, width, height, fig):
            '''Auto-decrease the fontsize of a text object.
        
            Args:
                text (matplotlib.text.Text)
                width (float): allowed width in data coordinates
                height (float): allowed height in data coordinates
            '''
            ax = fig.axes[0]
        
            # get text bounding box in figure coordinates
            renderer = fig.canvas.get_renderer()
            bbox_text = text.get_window_extent(renderer=renderer)
        
            # transform bounding box to data coordinates
            bbox_text = Bbox(ax.transData.inverted().transform(bbox_text))
        
            # evaluate fit and recursively decrease fontsize until text fits
            fits_width = bbox_text.width < width if width else True
            fits_height = bbox_text.height < height if height else True
            if not all((fits_width, fits_height)):
                text.set_fontsize(text.get_fontsize()-1)
                if text.get_fontsize() <= 0:
                    text.set_fontsize(0)
                else:
                    self.auto_fit_fontsize(text, width, height, fig)

class Table:        
    
    dpi = 300
    cells = []
    fig = None

    def __init__(self, dpi):
        
        # Basics
        self.cells = []
        self.dpi = dpi

        # New figure
        self.fig, ax = plt.subplots(dpi=self.dpi)
        
        # Hide plot
        ax = plt.gca()
        ax.axis('off')
        ax.set_aspect("equal")

        #fig=plt.gcf()
    def AddCell(self, cell):
        if (type(cell) == Cell):
            self.cells.append(cell)
        else:
            print("Error! Trying to add", cell, "as a Cell!")
            
    def AddCells(self, *cells):
        for cell in cells:
            self.AddCell(cell)
            
    def Render(self, silent=False):
        
        # Sillyness
        if len(self.cells)==0:
            print("Attempting to render a Table without cells!")
            return

        # Draw cells
        for cell in self.cells:
            
            # Check overlap
            """
            overlap = False
            for c in self.cells:
                if c != cell:
                    overlap = cell.Overlap(c)
                if overlap:
                    break
            if overlap:
                continue
            """
            
            # Get cell size, which is in "desired inches"
            xmin = min(cell.xmin, cell.xmax)
            xmax = max(cell.xmin, cell.xmax)
            ymin = min(cell.ymin, cell.ymax)
            ymax = max(cell.ymin, cell.ymax)
            rect = [xmin, ymin, xmax, ymax]
            
            # Change inches -> px -> "axis" units
            for i in range(len(rect)):
                rect[i] = rect[i] * self.dpi    # In desired px
            
            # Draw cell fill
            ax = self.fig.axes[0]
            ax.add_patch(
                patches.Rectangle((rect[0],rect[1]), rect[2]-rect[0], rect[3]-rect[1], color=cell.color))
            
            # Draw cell border
            ax.plot(
                     [rect[0], rect[0], rect[2], rect[2], rect[0]],
                     [rect[1], rect[3], rect[3], rect[1], rect[1]],
                     color=cell.lineColor
                     )
            
        # Set size such that [self.dpi] axis units = 1 inch
        self.fig.canvas.draw()
        trans = self.fig.axes[0].transData
        pxBounds = trans.transform([
                                    (0, 0),
                                    (self.dpi, self.dpi)
                            ])
        figsize = self.fig.get_size_inches()
        self.fig.set_size_inches((
                                  self.dpi / (pxBounds[1][0] - pxBounds[0][0]) * figsize[0],
                                  self.dpi / (pxBounds[1][1] - pxBounds[0][1]) * figsize[1],
                     ))
            
        # Can only render text after all cells have been rendered (otherwise, yscale keeps changing)
        text = None
        self.fig.canvas.draw()
        for cell in self.cells:
            
            # Draw text
            anchors = cell.GetAnnotateAnchor()
            anchors = tuple(list([anchors[0] * self.dpi, anchors[1]*self.dpi]))

            text = plt.text(anchors[0], anchors[1], cell.content, 
                            fontsize=cell.fontsize,
                            va=cell.verticalAlignment,
                            ha=cell.horizontalAlignment,
                            rotation=cell.contentRotation
                        )
            # Adjust the font size if need be
            if cell.autosizeFont:
                cell.auto_fit_fontsize(text, abs(cell.Width() * self.dpi), abs(cell.Height() * self.dpi), self.fig)
            
        # Show
        if not silent:
            plt.show()
            
        
    def Save(self, filename, silent=False):
        
        # Render
        self.Render(silent=silent)
        
        # Save
        self.fig.savefig(filename, 
                         dpi=self.dpi,
                         transparent=True
                         )
        if silent:
            plt.close(self.fig)
        self.Crop(filename)
            
    def Crop(self, filename):

        # Load back image
        im = Image.open(filename)
        pixels = im.load()
        
        # Crop left
        cropLeft = 0
        for i in range(im.size[0]):
            foundColor = False
            for j in range(im.size[1]):
                if pixels[i, j][3] != 0:
                    foundColor = True
                    break
            if foundColor:
                break
            cropLeft += 1
            
        # Crop right
        cropRight = 0
        for i in reversed(range(im.size[0])):
            foundColor = False
            for j in range(im.size[1]):
                if pixels[i, j][3] != 0:
                    foundColor = True
                    break
            if foundColor:
                break
            cropRight += 1
        
        # Crop top
        cropTop = 0
        for j in range(im.size[1]):
            foundColor = False
            for i in range(im.size[0]):
                if pixels[i, j][3] != 0:
                    foundColor = True
                    break
            if foundColor:
                break
            cropTop += 1
            
        # Crop bottom
        cropBottom = 0
        for j in reversed(range(im.size[1])):
            foundColor = False
            for i in range(im.size[0]):
                if pixels[i, j][3] != 0:
                    foundColor = True
                    break
            if foundColor:
                break
            cropBottom += 1
        
        # Re-save
        im.crop((cropLeft, 
                 cropTop, 
                 im.size[0]-cropRight, 
                 im.size[1]-cropBottom)
            ).save(filename, dpi=(self.dpi, self.dpi))

        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        