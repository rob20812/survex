//
//  gla.h
//
//  Header file for the GLA abstraction layer.
//
//  Copyright (C) 2002 Mark R. Shinwell.
//  Copyright (C) 2003 Olly Betts
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
//  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//

#include "wx.h"
#include "aventypes.h"
#include "quaternion.h"

class GfxCore;

#define GLA_DEBUG 1

typedef Double glaCoord;
typedef GLuint glaList;

class GLAPoint {
    glaCoord xc, yc, zc;

public:
    GLAPoint(glaCoord x, glaCoord y, glaCoord z) : xc(x), yc(y), zc(z) {}
    ~GLAPoint() {}

    glaCoord GetX() { return xc; }
    glaCoord GetY() { return yc; }
    glaCoord GetZ() { return zc; }
};

class GLAPen {
    double m_Red;
    double m_Green;
    double m_Blue;
    double m_Alpha;
    
public:
    GLAPen();
    ~GLAPen();

    void SetColour(double red, double green, double blue); // arguments in range 0 to 1.0
    void SetAlpha(double alpha);
    void Interpolate(const GLAPen&, double how_far);

    double GetRed() const;
    double GetGreen() const;
    double GetBlue() const;
    double GetAlpha() const;
};

#ifdef AVENGL
class GLACanvas : public wxGLCanvas {
#else
class GLACanvas : public wxWindow {
#endif

#ifdef GLA_DEBUG
    int m_Vertices;
#endif

#ifdef AVENGL
    GLdouble modelview_matrix[16];
    GLdouble projection_matrix[16];
    GLint viewport[4];
#endif

    // Viewing volume extents:
    struct {
        Double left;
        Double right;
        Double front;
        Double back;
        Double bottom;
        Double top;
    } m_Volume;

    // Parameters for plotting data:
    Quaternion m_Rotation;
    Double m_Scale;
    struct {
        Double x;
        Double y;
        Double z;
    } m_Translation;

    static void* const m_Font;
    static const int m_FontSize;

    bool m_SphereCreated;
    GLuint m_SphereList;
    GLUquadric* m_Quadric;
    
    Double SetViewportAndProjection();
public:
    GLACanvas(wxWindow* parent, int id, const wxPoint& posn, wxSize size);
    ~GLACanvas();

    void FirstShow();

    void Clear();
    void StartDrawing();
    void FinishDrawing();

    void SetVolumeCoordinates(glaCoord left, glaCoord right, glaCoord front, glaCoord back,
                              glaCoord bottom, glaCoord top);
    void SetDataTransform();
    void SetIndicatorTransform();
    void SetQuaternion(Quaternion& q);
    
    glaList CreateList(GfxCore*, void (GfxCore::*generator)());
    void DeleteList(glaList l);
    void DrawList(glaList l);
    
    void SetBackgroundColour(float red, float green, float blue);
    void SetColour(const GLAPen& pen, bool set_transparency = false, double rgb_scale = 1.0);
#if 0 // Unused and won't build on MS Windows
    void SetBlendColour(const GLAPen& pen, bool set_transparency = false, double rgb_scale = 1.0);
#endif
    void SetPolygonColour(GLAPen& pen, bool front, bool set_transparency = false);
   
    void DrawText(glaCoord x, glaCoord y, glaCoord z, const wxString& str);
    void DrawIndicatorText(glaCoord x, glaCoord y, const wxString& str);
    void GetTextExtent(const wxString& str, glaCoord* x_ext, glaCoord* y_ext);
    
    void BeginQuadrilaterals();
    void EndQuadrilaterals();
    void BeginLines();
    void EndLines();
    void BeginTriangleStrip();
    void EndTriangleStrip();
    void BeginTriangles();
    void EndTriangles();
    void BeginPolyline();
    void EndPolyline();
    void BeginPolygon();
    void EndPolygon();
    
    void DrawRectangle(GLAPen& edge, GLAPen& fill, GLAPen& fill_top,
                       glaCoord x0, glaCoord y0, glaCoord w, glaCoord h, bool draw_lines = true);
    void DrawCircle(GLAPen& edge, GLAPen& fill, glaCoord cx, glaCoord cy, glaCoord radius);
    void DrawSemicircle(GLAPen& edge, GLAPen& fill, glaCoord cx, glaCoord cy, glaCoord radius, glaCoord start);
    void DrawTriangle(GLAPen& edge, GLAPen& fill, GLAPoint* vertices);
    
    void DrawSphere(GLAPen& pen, glaCoord x, glaCoord y, glaCoord z, glaCoord radius, int divisions);
    
    void PlaceVertex(glaCoord x, glaCoord y, glaCoord z);
    void PlaceIndicatorVertex(glaCoord x, glaCoord y);

    void PlaceNormal(glaCoord x, glaCoord y, glaCoord z);
    
    void EnableDashedLines();
    void DisableDashedLines();

    void EnableSmoothPolygons();
    void DisableSmoothPolygons();

    void SetRotation(Quaternion&);
    void SetScale(Double);
    void SetTranslation(Double, Double, Double);
    void AddTranslation(Double, Double, Double);
    void AddTranslationScreenCoordinates(int dx, int dy);

    void Transform(Double x, Double y, Double z, Double* x_out, Double* y_out, Double* z_out);
    void ReverseTransform(Double x, Double y, Double* x_out, Double* y_out, Double* z_out);

    int GetFontSize() const { return m_FontSize; }

    Double SurveyUnitsAcrossViewport();

    void TogglePerspective() { m_Perspective = !m_Perspective; }
    bool GetPerspective() const { return m_Perspective; }

    bool m_Perspective;
};
