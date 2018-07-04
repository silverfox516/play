#include <iostream>
#include <sstream>
#include <stdexcept>
#include <cstring>
#include <cctype>

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_OUTLINE_H
#include FT_BBOX_H

using namespace std;

struct FreeTypeLibrary
{
    FreeTypeLibrary();
    ~FreeTypeLibrary();

    FT_Library m_ftLibrary;
};

inline FreeTypeLibrary::FreeTypeLibrary()
{
    FT_Error error = FT_Init_FreeType(&m_ftLibrary);

    if (error)
        throw runtime_error("Couldn't initialize the library:"
                " FT_Init_FreeType() failed");
}

inline FreeTypeLibrary::~FreeTypeLibrary()
{
    FT_Done_FreeType(m_ftLibrary);
}

struct FreeTypeFace
{
    FreeTypeFace(const FreeTypeLibrary &library,
            const char *filename);
    ~FreeTypeFace();

    FT_Face m_ftFace;
};

inline FreeTypeFace::FreeTypeFace(const FreeTypeLibrary &library,
        const char *filename)
{
    FT_Error error = FT_New_Face(library.m_ftLibrary, filename, 0, &m_ftFace);

    if (error)
        throw runtime_error("Coundn't load the font file:"
                " FT_New_Face() failed");
}

class OutlinePrinter
{
public:
    OutlinePrinter(const char *filename);
    int Run(const char *symbol);

private:
    void LoadGlyph(const char *symbol) const;
    bool OutlineExists() const;
    void FilpOutline() const;
    void ExtractOutline();
    void ComputeViewBox();
    void PrintSVG() const;

    static int MoveToFunction(const FT_Vector *to,
            void *user);
    static int LineToFunction(const FT_Vector *to,
            void *user);
    static int ConicToFunction(const FT_Vector *control,
            const FT_Vector *to,
            void *user);
    static int CubicToFunction(const FT_Vector *controlOne,
            const FT_Vector *controlTwo,
            const FT_Vector *to,
            void *user);

private:
    FreeTypeLibrary m_library;
    FreeTypeFace m_face;

    ostringstream m_path;

    FT_Pos m_xMin;
    FT_Pos m_yMin;
    FT_Pos m_width;
    FT_Pos m_height;
};

inline FreeTypeFace::~FreeTypeFace()
{
    FT_Done_Face(m_ftFace);
}

inline OutlinePrinter::OutlinePrinter(const char *filename)
    : m_face(m_library, filename),
    m_xMin(0),
    m_yMin(0),
    m_width(0),
    m_height(0)
{
}

int OutlinePrinter::Run(const char *symbol)
{
    LoadGlyph(symbol);

    bool outlineExists = OutlineExists();

    if (!outlineExists)
        throw runtime_error("Outline check failed.\n"
                "Please, inspect your font file or try another one,"
                " for exampel LiberationSerif-Bold.ttf");

    FilpOutline();

    ExtractOutline();

    ComputeViewBox();

    PrintSVG();

    return 0;
}

void OutlinePrinter::LoadGlyph(const char *symbol) const
{
    FT_ULong code = symbol[0];

    FT_UInt index = FT_Get_Char_Index(m_face.m_ftFace, code);

    FT_Error error = FT_Load_Glyph(m_face.m_ftFace, index,
            FT_LOAD_NO_SCALE || FT_LOAD_NO_BITMAP);
    if (error)
        throw runtime_error("Couldn't load the glyph: FT_Load_Glyph() failed");
}

bool OutlinePrinter::OutlineExists() const
{
    FT_Face face = m_face.m_ftFace;
    FT_GlyphSlot slot = face->glyph;
    FT_Outline &outline = slot->outline;

    if (slot->format != FT_GLYPH_FORMAT_OUTLINE)
        return false;

    if (outline.n_contours <= 0 || outline.n_points <= 0)
        return false;

    FT_Error error = FT_Outline_Check(&outline);

    return error == 0;
}

void OutlinePrinter::FilpOutline() const
{
    const FT_Fixed multiplier = 65536L;

    FT_Matrix matrix;

    matrix.xx = 1L * multiplier;
    matrix.xy = 0L * multiplier;
    matrix.yx = 0L * multiplier;
    matrix.yy = -1L * multiplier;

    FT_Face face = m_face.m_ftFace;
    FT_GlyphSlot slot = face->glyph;
    FT_Outline &outline = slot->outline;

    FT_Outline_Transform(&outline, &matrix);
}

void OutlinePrinter::ExtractOutline()
{
    m_path << "  <path d='\n";

    FT_Outline_Funcs callbacks;

    callbacks.move_to = MoveToFunction;
    callbacks.line_to = LineToFunction;
    callbacks.conic_to = ConicToFunction;
    callbacks.cubic_to = CubicToFunction;

    callbacks.shift = 0;
    callbacks.delta = 0;

    FT_Face face = m_face.m_ftFace;
    FT_GlyphSlot slot = face->glyph;
    FT_Outline &outline = slot->outline;

    FT_Error error = FT_Outline_Decompose(&outline, &callbacks, this);
    if (error)
        throw runtime_error("Couldn't extract the outline:"
                " FT_Outline_Decompose() failed");

    m_path << "          '\n"
        "        fill='green'/>\n";
}

void OutlinePrinter::ComputeViewBox()
{
    FT_Face face = m_face.m_ftFace;
    FT_GlyphSlot slot = face->glyph;
    FT_Outline &outline = slot->outline;

    FT_BBox boundingBox;

    FT_Outline_Get_BBox(&outline, &boundingBox);

    FT_Pos xMin = boundingBox.xMin;
    FT_Pos yMin = boundingBox.yMin;
    FT_Pos xMax = boundingBox.xMax;
    FT_Pos yMax = boundingBox.yMax;

    m_xMin = xMin;
    m_yMin = yMin;
    m_width = xMax - xMin;
    m_height = yMax - yMin;
}

void OutlinePrinter::PrintSVG() const
{
    cout << "<svg xmlns='http://www.w3.org/2000/svg'\n"
        "     xmlns:xlink='http://www.w3.org/1999/xlink'\n"
        "     viewBox='"
        << m_xMin << ' ' << m_yMin << ' ' << m_width << ' ' << m_height
        << "'>\n"
        << m_path.str()
        << "</svg>"
        << endl;
}

int OutlinePrinter::MoveToFunction(const FT_Vector *to,
        void *user)
{
    OutlinePrinter *self = static_cast<OutlinePrinter *>(user);

    FT_Pos x = to->x;
    FT_Pos y = to->y;

    self->m_path << "           "
        "M " << x << ' ' << y << '\n';

    return 0;
}

int OutlinePrinter::LineToFunction(const FT_Vector *to,
        void *user)
{
    OutlinePrinter *self = static_cast<OutlinePrinter *>(user);

    FT_Pos x = to->x;
    FT_Pos y = to->y;

    self->m_path << "           "
        "L " << x << ' ' << y << '\n';

    return 0;
}

int OutlinePrinter::ConicToFunction(const FT_Vector *control,
        const FT_Vector *to,
        void *user)
{
    OutlinePrinter *self = static_cast<OutlinePrinter *>(user);

    FT_Pos controlX = control->x;
    FT_Pos controlY = control->y;

    FT_Pos x = to->x;
    FT_Pos y = to->y;

    self->m_path << "           "
        "Q " << controlX << ' ' << controlY << ", "
        << x << ' ' << y << '\n';

    return 0;
}

int OutlinePrinter::CubicToFunction(const FT_Vector *controlOne,
        const FT_Vector *controlTwo,
        const FT_Vector *to,
        void *user)
{
    OutlinePrinter *self = static_cast<OutlinePrinter *>(user);

    FT_Pos controlOneX = controlOne->x;
    FT_Pos controlOneY = controlOne->y;

    FT_Pos controlTwoX = controlTwo->x;
    FT_Pos controlTwoY = controlTwo->y;

    FT_Pos x = to->x;
    FT_Pos y = to->y;

    self->m_path << "           "
        "Q " << controlOneX << ' ' << controlOneY << ", "
        "Q " << controlTwoX << ' ' << controlTwoY << ", "
        << x << ' ' << y << '\n';

    return 0;
}

int main(int argc, char **argv)
{
    if (argc != 3) {
        const char *program = argv[0];

        cerr << "This program prints a single character's outline"
            " in the SVG format to stdout.\n"
            "Usage: " << program << " font symbol\n"
            "Example: " << program << " LiberationSerif-Bold.ttf A" << endl;

        return 1;
    }

    const char *symbol = argv[2];

    if (strlen(symbol) != 1 || isspace(*symbol)) {
        cerr << "Error: '" << symbol
            << "' is not a single printable character" << endl;

        return 2;
    }

    int status;

    try {
        const char *filename = argv[1];

        OutlinePrinter printer(filename);

        status = printer.Run(symbol);
    } catch (const exception &e) {
        cerr << "Error: " << e.what() << endl;

        status = 3;
    }

    return status;

    return 0;
}