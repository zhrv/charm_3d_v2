/**
 * @file
 * @brief Class for mesh model
 * @author R.V.Zhalnin
 * @date 2020-11-15
 */

#ifndef CHARM_3D_V2_MESH_H
#define CHARM_3D_V2_MESH_H
#include "global.h"
#include "Point.h"
#include "Cell.h"
#include "Face.h"

namespace charm {

    struct Patch {
        String name;
        Int id;
        Int dim;
    };



    class Mesh {
    public:
        typedef enum {
            UNKNOWN,
            GMSH_MSH,
            GMSH_INP,
            GMSH_UNV,
            OPENFOAM,
            SALOME_UNV,
            TETGEN
        } FileType;

        void calcGeom();

        Points cellGetVertices(Cell &c);
        Points cellGetVertices(Index ci);
        Points cellGetFaceVertices(Cell &c, Index fi);
        Points cellGetFaceVertices(Index ci, Index fi);
        //void decomp();

        static void cellCalcGpAtPoint(Points vertices, Point ref_p, Point &gp, Real &gj);
        static void cellCalcGp(Cell &cell);
        static Point unitCubeToReal(Array<Point> vertices, Real x, Real y, Real z);

        static FileType getfileTypeByStr(String str);

        Points        nodes;     ///< Mesh nodes.
        Array<Cell>         cells;     ///< Mesh cells.
        Array<Face>         faces;     ///< Mesh faces.
        Array<Patch>        patches;

        Index patchesCount = 0;       ///< Number of boundary patches.

        static const Index ftv[6][4];// =
//                                    {{ 0, 2, 4, 6 },
//                                     { 1, 3, 5, 7 },
//                                     { 0, 1, 4, 5 },
//                                     { 2, 3, 6, 7 },
//                                     { 0, 1, 2, 3 },
//                                     { 4, 5, 6, 7 }};
    };

}

#endif //CHARM_3D_V2_MESH_H
