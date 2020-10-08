/* ivm64 graphical device output */

#include "gdevprn.h"


/* ivm64 device primitives */
void ivm64_new_frame(long width, long height, long rate)
{
  asm volatile("new_frame* [(load8 %[w]) (load8 %[h]) (load8 %[r])]"
               : : [w] "m" (width), [h] "m" (height), [r] "m" (rate));
}

void ivm64_set_pixel(long x, long y, long r, long g, long b) 
{
  asm volatile("set_pixel* [(load8 %[x]) (load8 %[y]) (load8 %[r]) (load8 %[g]) (load8 %[b])]"
               : : [x] "m" (x), [y] "m" (y), [r] "m" (r), [g] "m" (g), [b] "m" (b));
}

/* ------ The device descriptor ------ */

/*
 * Default X and Y resolution.
 */
#define X_DPI 72
#define Y_DPI 72

static dev_proc_print_page(ivm64_print_page);

static const gx_device_procs ivm64_procs =
  prn_color_procs(gdev_prn_open, gdev_prn_bg_output_page, gdev_prn_close,
                  gx_default_rgb_map_rgb_color, gx_default_rgb_map_color_rgb);
const gx_device_printer gs_ivm64_device =
  prn_device(ivm64_procs, "ivm64",
             DEFAULT_WIDTH_10THS, DEFAULT_HEIGHT_10THS,
             X_DPI, Y_DPI,
             0, 0, 0, 0,		/* margins */
             24, ivm64_print_page);

static int
ivm64_print_page(gx_device_printer * pdev, gp_file * file)
{
  int raster = gx_device_raster((gx_device *) pdev, true);
  byte *line = gs_alloc_bytes(pdev->memory, raster, "miff line buffer");
  int code = 0;		/* return code */

  if (line == 0)		/* can't allocate line buffer */
    return_error(gs_error_VMerror);

  ivm64_new_frame(pdev->width, pdev->height, 0);
  for (int y = 0; y < pdev->height; ++y) {
    byte *row;

    code = gdev_prn_get_bits(pdev, y, line, &row);
    if (code < 0)
      break;
    for (int x = 0; x < pdev->width; x++) {
      int i = 3 * x;
      ivm64_set_pixel(x, y, row[i], row[i + 1], row[i + 2]);
    }
  }
  gs_free_object(pdev->memory, line, "miff line buffer");

  return code;
}
