#ifndef DRAWING_UTILS_H
#define DRAWING_UTILS_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include "Graph.h"
#include <cairo.h>

void drawPathTSP(const std::unordered_map<int, City> &cities, const std::vector<int> &tspPath, std::string title)
{
    const int width = 2010;
    const int height = 2010;
    const int margin = 50;

    cairo_surface_t *surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
    cairo_t *cr = cairo_create(surface);

    // White background
    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_paint(cr);

    // Draw cities and paths
    cairo_set_line_width(cr, 2);

    for (size_t i = 0; i < tspPath.size(); ++i)
    {
        int currentIndex = tspPath[i];
        int nextIndex = tspPath[(i + 1) % tspPath.size()]; // loop back to the start

        const City &currentCity = cities.at(currentIndex);
        const City &nextCity = cities.at(nextIndex);

        cairo_set_source_rgb(cr, 0, 0, 0);
        cairo_move_to(cr, currentCity.x + margin, currentCity.y + margin);
        cairo_line_to(cr, nextCity.x + margin, nextCity.y + margin);
        cairo_stroke(cr);
    }

    // Draw city points
    for (const auto &pair : cities)
    {
        const City &city = pair.second;
        cairo_set_source_rgb(cr, 1, 0, 0);
        cairo_arc(cr, city.x + margin, city.y + margin, 5, 0, 2 * M_PI);
        cairo_fill(cr);
    }

    // Draw the title
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cr, 24);
    cairo_move_to(cr, width / 2 - margin, margin / 2);
    cairo_show_text(cr, title.c_str());

    // Save to PNG file
    cairo_surface_write_to_png(surface, title.append(".png").c_str());

    // Clean up
    cairo_destroy(cr);
    cairo_surface_destroy(surface);
}

#endif