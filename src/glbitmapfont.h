//
//  glbitmapfont.h
//
//  Draw text using glBitmap.
//
//  Copyright (C) 2011,2013 Olly Betts
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 2 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//

#ifndef GLBITMAPFONT_H_INCLUDED
#define GLBITMAPFONT_H_INCLUDED

#include "wx.h"

#ifdef HAVE_GL_GL_H
# include <GL/gl.h>
#elif defined HAVE_OPENGL_GL_H
# include <OpenGL/gl.h>
#endif

class BitmapFont {
    enum {
	// The highest character point to generate an OpenGL list for.
	//
	// We can't generate a GL list for every Unicode character, so we
	// generate them for the first BITMAPFONT_MAX_CHAR characters and then
	// use glBitmap directly to draw other characters if they are needed.
	//
	// FIXME: We could perhaps even store strings consisting of only the
	// first 256 points as ISO8859-1.
	BITMAPFONT_MAX_CHAR = 256
    };

    int gllist_base;

    mutable unsigned char ** extra_chars;

    mutable FILE * fh;

    unsigned char char_width[BITMAPFONT_MAX_CHAR];

    void write_glyph(wxChar ch) const;

  public:

    BitmapFont() : gllist_base(0), extra_chars(0), fh(0) { }

    ~BitmapFont() {
	if (gllist_base)
	    glDeleteLists(gllist_base, BITMAPFONT_MAX_CHAR);
	if (fh)
	    fclose(fh);
    }

    bool load(const wxString & font_file);

    // Hard-code for now.
    int get_font_size() const { return 16; }

    void get_text_extent(const wxChar *s, size_t len, int *width, int *height) const {
	if (width) {
	    int total_width = 0;
	    while (len--) {
		int ch = *s++;
		if (ch < BITMAPFONT_MAX_CHAR)
		    total_width += char_width[ch];
		else
		    total_width += 16; // FIXME: look up the width...
	    }
	    *width = total_width;
	}
	if (height) {
	    *height = get_font_size() + 1;
	}
    }

    void write_string(const wxChar *s, size_t len) const;
};

#endif
