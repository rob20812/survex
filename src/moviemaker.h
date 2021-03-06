//
//  moviemaker.h
//
//  Class for writing movies from Aven.
//
//  Copyright (C) 2004,2010,2011,2013 Olly Betts
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

struct AVFormatContext;
struct AVStream;
struct AVFrame;
struct AVPicture;
struct SwsContext;

class MovieMaker {
    AVFormatContext *oc;
    AVStream *video_st;
    int out_size;
    AVFrame *frame;
    unsigned char *outbuf;
    AVPicture *out;
    unsigned char *pixels;
    SwsContext *sws_ctx;
    int averrno;
 
    void release();

public:
    MovieMaker();
    bool Open(const char *fnm, int width, int height);
    unsigned char * GetBuffer() const;
    int GetWidth() const;
    int GetHeight() const;
    bool AddFrame();
    bool Close();
    ~MovieMaker();
    const char * get_error_string() const;
};
