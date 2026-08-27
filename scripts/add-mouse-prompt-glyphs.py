from pathlib import Path

from fontTools.pens.ttGlyphPen import TTGlyphPen
from fontTools.pens.transformPen import TransformPen
from fontTools.ttLib import TTFont


FONT_PATH = Path(__file__).resolve().parents[1] / "assets" / "promptfont" / "promptfont.ttf"
GLYPHS = {
    0xE100: ("mouse_left", "left"),
    0xE101: ("mouse_middle", "middle"),
    0xE102: ("mouse_right", "right"),
    0xE103: ("mouse_side_1", "side_1"),
    0xE104: ("mouse_side_2", "side_2"),
}


def contour(pen, points):
    pen.moveTo(points[0])
    for point in points[1:]:
        pen.lineTo(point)
    pen.closePath()


def rectangle(pen, x0, y0, x1, y1):
    contour(pen, [(x0, y0), (x0, y1), (x1, y1), (x1, y0)])


def ring_rectangle(pen, x0, y0, x1, y1, thickness):
    rectangle(pen, x0, y0, x1, y1)
    contour(
        pen,
        [
            (x0 + thickness, y0 + thickness),
            (x1 - thickness, y0 + thickness),
            (x1 - thickness, y1 - thickness),
            (x0 + thickness, y1 - thickness),
        ],
    )


def mouse_glyph(kind):
    glyph_pen = TTGlyphPen(None)
    x_offset = 105 if kind.startswith("side_") else 150
    pen = TransformPen(glyph_pen, (1, 0, 0, 1, x_offset, -130))

    # Clockwise shell and counter-clockwise inset form the mouse outline.
    pen.moveTo((500, 80))
    pen.qCurveTo((230, 80), (155, 330))
    pen.lineTo((155, 590))
    pen.qCurveTo((155, 850), (500, 850))
    pen.qCurveTo((845, 850), (845, 590))
    pen.lineTo((845, 330))
    pen.qCurveTo((770, 80), (500, 80))
    pen.closePath()

    pen.moveTo((500, 150))
    pen.qCurveTo((755, 150), (775, 345))
    pen.lineTo((775, 575))
    pen.qCurveTo((775, 780), (500, 780))
    pen.qCurveTo((225, 780), (225, 575))
    pen.lineTo((225, 345))
    pen.qCurveTo((245, 150), (500, 150))
    pen.closePath()

    rectangle(pen, 190, 500, 810, 535)
    rectangle(pen, 482, 520, 518, 815)

    if kind == "left":
        contour(pen, [(225, 550), (482, 550), (482, 780), (330, 780), (225, 710)])
    elif kind == "right":
        contour(pen, [(518, 550), (775, 550), (775, 710), (670, 780), (518, 780)])
    elif kind == "middle":
        rectangle(pen, 445, 595, 555, 735)
    else:
        ring_rectangle(pen, 65, 405, 175, 505, 28)
        ring_rectangle(pen, 65, 275, 175, 375, 28)
        if kind == "side_1":
            rectangle(pen, 65, 405, 175, 505)
        else:
            rectangle(pen, 65, 275, 175, 375)

    return glyph_pen.glyph()


font = TTFont(FONT_PATH)
glyph_order = font.getGlyphOrder()

for codepoint, (glyph_name, kind) in GLYPHS.items():
    if glyph_name not in glyph_order:
        glyph_order.append(glyph_name)
    font["glyf"][glyph_name] = mouse_glyph(kind)
    font["hmtx"].metrics[glyph_name] = (1000, 0)
    for table in font["cmap"].tables:
        if table.isUnicode():
            table.cmap[codepoint] = glyph_name

font.setGlyphOrder(glyph_order)
font["maxp"].numGlyphs = len(glyph_order)
font["hhea"].numberOfHMetrics = len(font["hmtx"].metrics)
font.save(FONT_PATH)
